#include "ActuatorHandlerThread/ActuatorHandler.h"
#include "SerialConsole.h"

void vActuatorHandlerTask(void *pvParameters)
{

    SerialConsoleWriteString("Get actuators functioning...\r\n");
     while(1){
//break;
vTaskDelay(500);
     }   
	 
}