#include "AccidentHandlerThread/AccidentHandler.h"

//#include "CliThread.h"

int counter = 0;
bool counter_state = true;

static char bufCli[CLI_MSG_LEN];

uint8 cur_accident = 0x0;
uint8 prev_accident = 0x0;

uint8 detectAccident(int temp, int hum, int acc, int gyro){
    uint8 accident_type = 0x0;
    if(temp > 38) accident_type |= 0x1;
    if(hum > 80) accident_type |= 0x2;
    if(acc > 130) accident_type |= 0x4;
    if(gyro == 1) accident_type |= 0x8;
    return accident_type;
}

void vAccidentHandlerTask(void *pvParameters)
{
    
    SerialConsoleWriteString("Checking accident state...\r\n");

    while(1){

        vTaskDelay(100);

        global_temp = temp_hum_get_val(GET_TEMP_VAL);
        counter++;
        // if(counter == 15){
        //     SerialConsoleWriteString("Obtained Temperature Value: ");
        //     snprintf(bufCli, CLI_MSG_LEN - 1, "%d\r\n", global_temp);
        //     SerialConsoleWriteString(bufCli);
        //     counter = 0;
        // }
        
        global_hum = temp_hum_get_val(GET_HUM_VAL);
        // if(counter == 15){
        //     SerialConsoleWriteString("Obtained Humidity Value: ");
        //     snprintf(bufCli, CLI_MSG_LEN - 1, "%d\r\n", global_hum);
        //     SerialConsoleWriteString(bufCli);
        //     counter = 0;
        // }

        acc_ang_get_val(GET_ACC_VAL);
        // SerialConsoleWriteString("Obtained Acc Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "X %d Y %d Z %d\r\n", (int)global_acc[0], (int)global_acc[1], (int)global_acc[2]);
        // SerialConsoleWriteString(bufCli);
    
        acc_ang_get_val(GET_ANG_VAL);
        // SerialConsoleWriteString("Obtained Ang Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "X %d Y %d Z %d\r\n", (int)global_gyro[0], (int)global_gyro[1], (int)global_gyro[2]);
        // SerialConsoleWriteString(bufCli);

        //if((global_temp <= 35) && (prev_temp > 35)) {handled = false;}

        int linearAccelerationx = global_acc[1] * 6 - global_acc[2] * 5;
        int linearAccelerationy = global_acc[2] * 4 - global_acc[0] * 6;
        int linearAccelerationz = global_acc[0] * 5 - global_acc[1] * 4;
        // SerialConsoleWriteString("Obtained Acc Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "X %d Y %d Z %d\r\n", linearAccelerationx, linearAccelerationy, linearAccelerationz);
        // SerialConsoleWriteString(bufCli);

        global_acc_value = (int)round(sqrt((double)((int)linearAccelerationx * (int)linearAccelerationx + linearAccelerationy * linearAccelerationy + linearAccelerationz * linearAccelerationz)));


        if(abs(global_gyro[2]) >= 800 && global_gyro[2] < 0) global_gyro_value = 1;
        else global_gyro_value = 0;

        cur_accident = detectAccident(global_temp, global_hum, global_acc_value, global_gyro_value);
        prev_accident = detectAccident(prev_temp, prev_hum, prev_acc_value, prev_gyro_value);

        if((prev_accident != 0x0) && (cur_accident == 0x0)){
            update_pwm_duty_cycle(70, 1);
            handled = false;
        }

        prev_temp = global_temp;
        prev_hum = global_hum;
        prev_acc_value = global_acc_value;
        prev_gyro_value = global_gyro_value;

        if(cur_accident != 0x0 && (!handled)){
            //send semaphore
            xSemaphoreGiveFromISR(xAccidentDetectedSemaphore, NULL);
            SerialConsoleWriteString("Accident Detected!\r\n");
            handled = true;

            if((cur_accident & 0x1) != 0x0){
                struct AccidentDataPacket accidentvar;
                accidentvar.accident_type = (cur_accident & 0x1);
                accidentvar.scalar_val = global_temp;

                int error = WifiAccidentDataToQueue(&accidentvar);
                if (error == pdTRUE) {
                    SerialConsoleWriteString("Combust Topic Post!\r\n");
                }
            }
            if((cur_accident & 0x2) != 0x0){
                struct AccidentDataPacket accidentvar;
                accidentvar.accident_type = (cur_accident & 0x2);
                accidentvar.scalar_val = global_hum;

                int error = WifiAccidentDataToQueue(&accidentvar);
                if (error == pdTRUE) {
                    SerialConsoleWriteString("Flooded Topic Post!\r\n");
                }
            }
            if((cur_accident & 0x4) != 0x0){
                struct AccidentDataPacket accidentvar;
                accidentvar.accident_type = (cur_accident & 0x4);
                accidentvar.val_array[0] = abs(linearAccelerationx);
                accidentvar.val_array[1] = abs(linearAccelerationy);
                accidentvar.val_array[2] = abs(linearAccelerationz);

                int error = WifiAccidentDataToQueue(&accidentvar);
                if (error == pdTRUE) {
                    SerialConsoleWriteString("Collision Topic Post!\r\n");
                }
            }
            if((cur_accident & 0x8) != 0x0){
                struct AccidentDataPacket accidentvar;
                accidentvar.accident_type = (cur_accident & 0x8);
                accidentvar.val_array[0] = global_gyro[0];
                accidentvar.val_array[1] = global_gyro[1];
                accidentvar.val_array[2] = global_gyro[2];

                int error = WifiAccidentDataToQueue(&accidentvar);
                if (error == pdTRUE) {
                    SerialConsoleWriteString("Overturning Topic Post!\r\n");
                }
            }
        }
    }   
}