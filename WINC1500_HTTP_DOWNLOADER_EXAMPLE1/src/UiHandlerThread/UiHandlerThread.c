 /**************************************************************************//**
* @file      UiHandlerThread.c
* @brief     File that contains the task code and supporting code for the UI Thread for ESE516 Spring (Online) Edition
* @author    You! :)
* @date      2020-04-09 

******************************************************************************/


/******************************************************************************
* Includes
******************************************************************************/
#include <errno.h>
#include "asf.h"
#include "UiHandlerThread/UiHandlerThread.h"
#include "SeesawDriver/Seesaw.h"
#include "SerialConsole.h"
#include "main.h"

/******************************************************************************
* Defines
******************************************************************************/

/******************************************************************************
* Variables
******************************************************************************/
uiStateMachine_state uiState;
/******************************************************************************
* Forward Declarations
******************************************************************************/

/******************************************************************************
* Callback Functions
******************************************************************************/


/******************************************************************************
* Task Function
******************************************************************************/

/**************************************************************************//**
* @fn		void vUiHandlerTask( void *pvParameters )
* @brief	STUDENT TO FILL THIS
* @details 	student to fill this
                				
* @param[in]	Parameters passed when task is initialized. In this case we can ignore them!
* @return		Should not return! This is a task defining function.
* @note         
*****************************************************************************/
void vUiHandlerTask( void *pvParameters )
{
//Do initialization code here
SerialConsoleWriteString("UI Task Started!\n");
uiState = UI_STATE_HANDLE_BUTTONS;

//Here we start the loop for the UI State Machine
while(1)
{
	delay_ms(500);
	port_pin_set_output_level(LED_0_PIN, LED_0_ACTIVE);
	delay_ms(500);
	port_pin_set_output_level(LED_0_PIN, !LED_0_ACTIVE);

	switch(uiState)
	{
		case(UI_STATE_HANDLE_BUTTONS):
		{
		//Do the handle buttons code here!
		/* NOTE:
		Do not call SeesawReadKeypad(uint8_t *buffer, uint8_t count) with the argument count being zero. 
		There seems to be a bug with ASF when this is called (i2c_master_read_packet_job).
		The following guard can be used:

		if(count != 0)		{
			SeesawReadKeypad(buffer, count);
		}
		
		*/
			uint8_t num_events = SeesawGetKeypadCount();
			if(num_events == 0) break;

			//get led status buffer
			uint8_t *buffer = (uint8_t*)malloc(sizeof(uint8_t) * num_events);
			int32_t error = SeesawReadKeypad(buffer, num_events);

			for(int i = 0; i < num_events; i++){
				//decode the message
				uint8_t ledNumber = (buffer[i] >> 2) & 0x3F;
				ledNumber = NEO_TRELLIS_SEESAW_KEY(ledNumber);
				uint8_t action = buffer[i] & 0x03;

				if(action == 0x02){
					SeesawSetLed(ledNumber, 0, 0, 0);
					SeesawOrderLedUpdate();

				}
				else{
					SeesawSetLed(ledNumber, 255, 255, 255);
					SeesawOrderLedUpdate();
				}
			}
			free(buffer);
			break;
		}

		case(UI_STATE_IGNORE_PRESSES):
		{
		//Ignore me for now
			break;
		}

		case(UI_STATE_SHOW_MOVES):
		{
		//Ignore me as well
			break;
		}

		default: //In case of unforseen error, it is always good to sent state machine to an initial state.
			uiState = UI_STATE_HANDLE_BUTTONS;
		break;
	}

	//After execution, you can put a thread to sleep for some time.
	vTaskDelay(50);
}



}




/******************************************************************************
* Functions
******************************************************************************/