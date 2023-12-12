#include "AccidentHandlerThread/AccidentHandler.h"
#include "SerialConsole.h"

int counter = 0;


void vAccidentHandlerTask(void *pvParameters)
{
    
    SerialConsoleWriteString("Checking accident state...\r\n");
    while(1){
        // counter++;
        // if(counter == 100){
        //     //send semaphore
        //     xSemaphoreGiveFromISR(xAccidentDetectedSemaphore, NULL);
        //     SerialConsoleWriteString("Accident Detected!\r\n");
        // }
        vTaskDelay(500);
        counter++;
        if(counter == 1){
            //send semaphore
            xSemaphoreGiveFromISR(xAccidentDetectedSemaphore, NULL);
            SerialConsoleWriteString("Accident Detected!\r\n");
        }
    }   
}