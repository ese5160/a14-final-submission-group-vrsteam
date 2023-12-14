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
                    //actuate servo to open the window (PA25)
                    SerialConsoleWriteString("W\r\n");
                    update_pwm_duty_cycle(48000, 3); //0 position: 72000
                    // SerialConsoleWriteString("Window position is changed!\r\n");
               }
               // //actuate servo to open the window (PA25)
               // update_pwm_duty_cycle(48000, 3); //0 position: 72000
          
               // SerialConsoleWriteString("Window position is changed!\r\n");
          
               //actuate motor driver to open water pump (PA24)
               //if((global_temp <= 35) && (prev_temp > 35)) {handled = false;}
               if(global_temp > 35 /*&& (!handled)*/){
                    SerialConsoleWriteString("F\r\n");
                    update_pwm_duty_cycle(48000, 2);
                    // SerialConsoleWriteString("Water pump is opened!\r\n");
                    //handled = true;
               }
               else SerialConsoleWriteString("Safe!\r\n");
          }
     }   
	 
}