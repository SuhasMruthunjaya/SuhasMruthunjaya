/**
 * \file <filename>
 * \author <author-name>
 * \date <date>
 *
 * \brief File containing attributes and functions of Game Class
 *
 * \copyright Copyright ©2016
 * Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
 * Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
 * (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
 * this paragraph and the following paragraph appear in all copies, modifications, and distributions.
 * Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
 *
 * \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
 * The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
 * This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
 */

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "project.h"
#include "game.h"
#include "menu.h"
#include "statemachine.h"
#include "game_cfg.h"
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static GAME_t GAME_object;
STATE_state_t Game_state;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/* Action */
static void GAME_StateMachineInit();
static void GAME_DeInit();
static void GAME_Cyclic();

/* Guard*/


/*****************************************************************************/
/* Local const table ('static')                                      */
/*****************************************************************************/

/** -------------------------------2 Layer Look up Table approach Game State Machine Transitions ---------------------------------------- **/

//!**  ===== GAME_IS_SELECTING ====   */
static const STATE_stateInnerTransitionTable_t GAME_IS_SELECTING_Transitions = {
		/*    Event                      ToState                 Guard               Action                       */
		{ GAME_EV_BUTTON_UP,         GAME_IS_SELECTING,       0,                 MENU_prevgame},
		{ GAME_EV_BUTTON_DOWN,       GAME_IS_SELECTING,       0,                 MENU_nextgame},
		{ GAME_EV_BUTTON_START,      GAME_IS_SELECTEDGAME,    0,                 GAME_StateMachineInit},
};

//!**  ===== GAME_IS_SELECTEDGAME ====   */
static const STATE_stateInnerTransitionTable_t GAME_IS_SELECTEDGAME_Transitions = {
		/*    Event                      ToState                  Guard               Action                       */
		{ GAME_EV_TICK,              GAME_IS_SELECTEDGAME,    0,                  GAME_Cyclic},
		{ GAME_EV_BUTTON_STOP,       GAME_IS_SELECTING,       0,                  GAME_DeInit},
};


static const STATE_stateOuterTransitionTable_t GameStateMachine_Transitions = {
		/*    fromState             Pointer to table                    Size of table [Elements]    */
		{ GAME_IS_SELECTING,    &GAME_IS_SELECTING_Transitions,     sizeof(GAME_IS_SELECTING_Transitions)/sizeof(STATE_stateInnerTransition_t)    },
		{ GAME_IS_SELECTEDGAME,     &GAME_IS_SELECTEDGAME_Transitions,      sizeof(GAME_IS_SELECTEDGAME_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
};
static const uint16_t GameStateMachine_Transitions_size = sizeof(GameStateMachine_Transitions)/sizeof(STATE_stateOuterTransition_t);

//!** ---------------------------------- Action ------------------------------------------- **/

static const STATE_stateActionTable_t GameStateMachine_StateActions = {
		/*  fromState               Entry                    Exit    */
		{ GAME_IS_SELECTING,      MENU_ShowMenu,            0   },
		{ GAME_IS_SELECTEDGAME,      0,                     0   },
};
static const uint16_t GameStateMachine_StateActions_size = sizeof(GameStateMachine_StateActions)/sizeof(STATE_stateAction_t);


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/*!
 * Initialise the statemachine of respective Game based on which game is selected in the Game State Machine
 * @param none
 * @return none
 */
static void GAME_StateMachineInit()
{
	GAME_table[MENU_GetIndex()].Init();
}

/*!
 * De-Initialise the statemachine of respective Game based on which game is selected in the Game State Machine
 * @param none
 * @return none
 */
static void GAME_DeInit()
{
	GAME_table[MENU_GetIndex()].DeInit();
}

/*!
 * Call the Cyclic function of respective Game based on which game is selected in the Game State Machine
 * @param none
 * @return none
 */
static void GAME_Cyclic()
{
	GAME_table[MENU_GetIndex()].Game_cyclic();
}


/*!
 * Set the events which are needed for the Game state machine
 * @param GAME_event_t ev - IN Event to be set
 * @return RC_SUCCESS when all okay
 */
RC_t GAME_set_event(GAME_event_t ev)
{
	GAME_object.ev = ev;
	SetEvent(tsk_game, ev_newGameEvent);
	return RC_SUCCESS;
}

/*!
 * Get the event names from the Game object
 * @param none
 * @return GAME_event_t - Event name is returned
 */
GAME_event_t GAME_get_event()
{
	return GAME_object.ev;


}

/*!
 * Initialisation of the Game state machine
 * @param none
 * @return GAME_event_t - Event name is returned
 */
RC_t GAME_InitState()
{
	MENU_init();
	RC_t ret = STATE_initState( GameStateMachine_StateActions ,
			GameStateMachine_StateActions_size,
			&Game_state, GameStateMachine_INIT_DATA);
    if(ret != RC_SUCCESS)
    {
    	UART_LOG_PutString(" Error in the State machine init, inside GAME_InitState Function");
    	return RC_ERROR;
    }
	return RC_SUCCESS;

}

/*!
 * Process the events obtained inside the Game state machine
 * @param STATE_event_t ev - IN Events to be processed inside the state machine
 * @return GAME_event_t - Event name is returned
 */
RC_t GAME_process_event(STATE_event_t ev)
{
	RC_t ret = STATE_processEvent(GameStateMachine_Transitions,
			GameStateMachine_Transitions_size,
			GameStateMachine_StateActions,
			GameStateMachine_StateActions_size,
			ev,
			&Game_state);
    if(ret != RC_SUCCESS)
    {
    	UART_LOG_PutString(" Error in the Game State machine, inside GAME_process_event Function");
    	return RC_ERROR;
    }
	return RC_SUCCESS;
}
