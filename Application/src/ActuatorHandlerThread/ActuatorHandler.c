#include "ActuatorHandlerThread/ActuatorHandler.h"
#include "SerialConsole.h"
#include "pwmDriver/pwm.h"
//extern int prev_temp;
 
extern bool handled;

void vActuatorHandlerTask(void *pvParameters)
{

     SerialConsoleWriteString("Get actuators functioning...\r\n");
     while(1){
          vTaskDelay(50);
          //try to take semaphore
          if(xSemaphoreTake(xAccidentDetectedSemaphore, portMAX_DELAY) == pdTRUE){
               // SerialConsoleWriteString("Try to rescue passengers!\r\n");
               if(global_gyro_value == 1){
                    SerialConsoleWriteString("O\r\n");
               }
               if(global_acc_value > 130){
                    SerialConsoleWriteString("C\r\n");
               }
               if(global_hum > 80){
                    SerialConsoleWriteString("W\r\n");
                    update_pwm_duty_cycle(94, 1); //0 position: 72000
               }
               if(global_temp > 39 /*&& (!handled)*/){
                    SerialConsoleWriteString("F\r\n");
                    update_pwm_duty_cycle(94, 1);
               }
          }
     }   
	 
}