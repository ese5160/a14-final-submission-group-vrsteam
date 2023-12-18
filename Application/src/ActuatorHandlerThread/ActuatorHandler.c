#include "ActuatorHandlerThread/ActuatorHandler.h"
#include "SerialConsole.h"
#include "pwmDriver/pwm.h"

void vActuatorHandlerTask(void *pvParameters)
{

     SerialConsoleWriteString("Get actuators functioning...\r\n");
     while(1){
          vTaskDelay(100);
          //try to take semaphore
          if(xSemaphoreTake(xAccidentDetectedSemaphore, portMAX_DELAY) == pdTRUE){
               // SerialConsoleWriteString("Try to rescue passengers!\r\n");
               if((cur_accident & 0x1) != 0x0){
                    SerialConsoleWriteString("F\r\n");
                    update_pwm_duty_cycle(110, 1);

               }
               if((cur_accident & 0x2) != 0x0){
                    SerialConsoleWriteString("W\r\n");
                    update_pwm_duty_cycle(110, 1); //0 position: 72000
               }
               if((cur_accident & 0x4) != 0x0){
                    SerialConsoleWriteString("C\r\n");
                    //update_pwm_duty_cycle(110, 1);
               }
               if((cur_accident & 0x8) != 0x0){
                    SerialConsoleWriteString("O\r\n");
                    update_pwm_duty_cycle(110, 1);
               }
          }
     }   
}