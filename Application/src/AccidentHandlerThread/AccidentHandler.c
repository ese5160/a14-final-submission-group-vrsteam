#include "AccidentHandlerThread/AccidentHandler.h"
#include "SerialConsole.h"
#include "tempHumDriver/tempHum.h"


int counter = 0;
extern int prev_temp;

bool accidentHappened(int temp, int hum){
    if(temp > 39 || hum > 80) return true;
    else return false;
}

void vAccidentHandlerTask(void *pvParameters)
{
    
    SerialConsoleWriteString("Checking accident state...\r\n");
    while(1){
        counter++; 
        if(counter == 100)  counter = 0;

        vTaskDelay(500);

        global_temp = temp_hum_get_val(GET_TEMP_VAL);
        if(global_temp > 39 && prev_temp <= 39) handle = true;
        if(global_temp <= 39 && prev_temp > 39) handle = false;
        prev_temp = global_temp;
        // SerialConsoleWriteString("Obtained Temperature Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "%d\r\n", global_temp);
        // SerialConsoleWriteString(bufCli);
        
        global_hum = temp_hum_get_val(GET_HUM_VAL);
        // SerialConsoleWriteString("Obtained Humidity Value: ");
        // snprintf(bufCli, CLI_MSG_LEN - 1, "%d\r\n", global_hum);
        // SerialConsoleWriteString(bufCli);

        if(accidentHappened(global_temp, global_hum)){
            //send semaphore
            xSemaphoreGiveFromISR(xAccidentDetectedSemaphore, NULL);
            SerialConsoleWriteString("Accident Detected!\r\n");
        }
    }   
}