#include "AccidentHandlerThread/AccidentHandler.h"
#include "SerialConsole.h"
#include "tempHumDriver/tempHum.h"

int counter = 0;

bool accidentHappened(int temp, int hum){
    if(temp > 30 || hum > 80) return true;
    else return false;
}

void vAccidentHandlerTask(void *pvParameters)
{
    
    SerialConsoleWriteString("Checking accident state...\r\n");
    while(1){
        vTaskDelay(500);

        global_temp = temp_hum_get_val(GET_TEMP_VAL);
        global_hum = temp_hum_get_val(GET_HUM_VAL);

        if(accidentHappened(global_temp, global_hum)){
            //send semaphore
            xSemaphoreGiveFromISR(xAccidentDetectedSemaphore, NULL);
            SerialConsoleWriteString("Accident Detected!\r\n");
        }
    }   
}