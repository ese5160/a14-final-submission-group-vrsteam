 /**************************************************************************//**
 * @file      UiHandlerThread.h
 * @brief     File that contains the task code and supporting code for the UI Thread for ESE516 Spring (Online) Edition
 * @author    You! :)
 * @date      2020-04-09

 ******************************************************************************/

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
* Includes
******************************************************************************/
#define UI_TASK_SIZE			256//<Size of stack to assign to the UI thread. In words
#define UI_TASK_PRIORITY		(configMAX_PRIORITIES - 2)
/******************************************************************************
* Defines
******************************************************************************/
typedef enum uiStateMachine_state
{
	UI_STATE_HANDLE_BUTTONS = 0, ///<State used to handle buttons
	UI_STATE_IGNORE_PRESSES, ///<State to ignore button presses
	UI_STATE_SHOW_MOVES, ///<State to show opponent's moves
	UI_STATE_MAX_STATES	///<Max number of states

}uiStateMachine_state;
/******************************************************************************
* Structures and Enumerations
******************************************************************************/



/******************************************************************************
* Global Function Declaration
******************************************************************************/
void vUiHandlerTask( void *pvParameters );

#ifdef __cplusplus
}
#endif