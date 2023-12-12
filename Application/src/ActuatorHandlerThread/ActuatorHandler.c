#include "ActuatorHandlerThread/ActuatorHandler.h"
#include "SerialConsole.h"

void vActuatorHandlerTask(void *pvParameters)
{

    SerialConsoleWriteString("Get actuators functioning...\r\n");
     while(1){
          //try to take semaphore
          // if(xSemaphoreTake(xAccidentDetectedSemaphore, portMAX_DELAY) == pdTRUE){
          //      SerialConsoleWriteString("Try to rescue passengers!\r\n");
          // }
          vTaskDelay(500);
          //try to take semaphore
          if(xSemaphoreTake(xAccidentDetectedSemaphore, portMAX_DELAY) == pdTRUE){
               SerialConsoleWriteString("Try to rescue passengers!\r\n");
          }
     }   
	 
}