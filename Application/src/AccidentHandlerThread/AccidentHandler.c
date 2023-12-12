#include "AccidentHandlerThread/AccidentHandler.h"
#include "SerialConsole.h"

void vAccidentHandlerTask(void *pvParameters)
{
    
    SerialConsoleWriteString("Checking accident state...\r\n");
    while(1){
        counter++;
        if(counter == 100){
            //send semaphore
            xSemaphoreGiveFromISR(xAccidentDetectedSemaphore, NULL);
            SerialConsoleWriteString("Accident Detected!\r\n");
        }
        vTaskDelay(500);
    }   
}