#include "AccidentHandlerThread/AccidentHandler.h"
#include "SerialConsole.h"
#include "tempHumDriver/tempHum.h"
#include "IMU/imu.h"
//#include "CliThread.h"

int counter = 0;
bool counter_state = true;

static char bufCli[CLI_MSG_LEN];


bool accidentHappened(int temp, int hum){
    if(temp > 35 || hum > 80) return true;
    else return false;
}

void vAccidentHandlerTask(void *pvParameters)
{
    
    SerialConsoleWriteString("Checking accident state...\r\n");
    while(1){

        vTaskDelay(500);

        // if(counter >= 100){
        //     counter_state = false;
        //     SerialConsoleWriteString("down\r\n");
        // }

        // if(counter <= 0){
        //     counter_state = true;
        //     SerialConsoleWriteString("up\r\n");
        // }

        // if(counter_state)   counter += 2;
        // else    counter -= 2;
        // global_temp = counter;

        global_temp = temp_hum_get_val(GET_TEMP_VAL);
       // SerialConsoleWriteString("Obtained Temperature Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "%d\r\n", global_temp);
        // SerialConsoleWriteString(bufCli);
        
        global_hum = temp_hum_get_val(GET_HUM_VAL);
        // SerialConsoleWriteString("Obtained Humidity Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "%d\r\n", global_hum);
        // SerialConsoleWriteString(bufCli);

        acc_ang_get_val(GET_ACC_VAL);
        // SerialConsoleWriteString("Obtained Acc Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "X %d Y %d Z %d\r\n", (int)global_acc[0], (int)global_acc[1], (int)global_acc[2]);
        // SerialConsoleWriteString(bufCli);
    
        acc_ang_get_val(GET_ANG_VAL);
        // SerialConsoleWriteString("Obtained Ang Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "X %d Y %d Z %d\r\n", (int)global_gyro[0], (int)global_gyro[1], (int)global_gyro[2]);
        // SerialConsoleWriteString(bufCli);
        //if((global_temp <= 39) && (prev_temp > 39)) {handled = false;}
        if(accidentHappened(global_temp, global_hum)){
            //send semaphore
            //if((global_temp <= 35) && (prev_temp > 35)) {handled = false;}
            xSemaphoreGiveFromISR(xAccidentDetectedSemaphore, NULL);
            // SerialConsoleWriteString("Accident Detected!\r\n");
        }

        //if((global_temp <= 35) && (prev_temp > 35)) {handled = false;}
        prev_temp = global_temp;
    }   
}