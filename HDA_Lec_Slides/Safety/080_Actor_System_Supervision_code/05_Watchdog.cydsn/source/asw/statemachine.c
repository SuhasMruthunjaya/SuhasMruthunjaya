/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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

#include "statemachine.h"
#include "watchdog.h"
#include "gpio.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/




/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/







/*****************************************************************************/
/* Local function prototypes ('static') / Guards                             */
/*****************************************************************************/

/**
 * Check Timeout Watchdog Window
 * timeout value will be read from configuration based on Time switches on the board
 * /return true if currentTime > timeout, otherwise false
 */
static boolean_t STATE__Alive_Timeout_NOK();

/**
 * Check Timeout Watchdog Window
 * timeout value will be read from configuration based on Time switches on the board
 * /return true if currentTime < timeout, otherwise false
 */
static boolean_t STATE__Alive_Timeout_OK();

/**
 * Check Window Watchdog Window
 * Will be called if the ev_trigger is fired
 * timeout value will be read from configuration based on Time switches on the board
 * /return true if currentTime is in window, otherwise false
 */
static boolean_t STATE__Window_checkWindow();

/**
 * Check Window Watchdog Window - only timeout
 * This function is required to check if the ev_tick in case no trigger is coming
 * /return true if currentTime is in window, otherwise false
 */
static boolean_t STATE__Window_checkTimeout();

/*****************************************************************************/
/* Local function prototypes ('static') / Actions                            */
/*****************************************************************************/

/**
 * Set power on / Enable WDA pin
 **/
static void STATE__PowerOn();

/**
 * Set power off / Disable WDA pin
 **/
static void STATE__PowerOff();

/**
 * Reset Timer of Watchdog
 **/
static void STATE__resetTimer();

/*****************************************************************************/
/* Local function prototypes ('static') / Helper                             */
/*****************************************************************************/


/**
 * Get the index of the state in the table
 */
sint16_t STATE__getIndexOfState(STATE_stateOuterTransitionTable_t const * const  transitionTable,
                                uint16_t transitionTableSize,
                                STATE_state_t state);

/*****************************************************************************/
/* State Machine Table Declarations                                          */
/*****************************************************************************/

//==================================================== ALIVE WATCHDOG =======================================

/**  ===== state_ok ====   */
const STATE_stateInnerTransitionTable_t STATE_Alive_state_ok_Transitions = {
/*    Event         ToState         Guard                       Action                  */
    { ev_tick,      state_error,    STATE__Alive_Timeout_NOK,   STATE__PowerOff         },  //Power off called twice, once as transition, once as state entry
    { ev_trigger,   state_ok,       STATE__Alive_Timeout_OK,    STATE__resetTimer       },
    { ev_restart,   state_ok,       0,                          STATE__resetTimer       },
};

/**  ===== state_warn - not used for alive watchdog ====   */
    
/**  ===== state_error ====   */
const STATE_stateInnerTransitionTable_t STATE_Alive_state_error_Transitions = {
/*    Event         ToState         Guard                       Action                  */
    { ev_restart,   state_ok,       0,                          STATE__resetTimer       },
};

const STATE_stateOuterTransitionTable_t STATE_Alive_Transitions = {
/*    fromState          Pointer to table                       Size of table [Elements]    */
    { state_ok,         &STATE_Alive_state_ok_Transitions,    sizeof(STATE_Alive_state_ok_Transitions)/sizeof(STATE_stateInnerTransition_t)    },
    { state_warn,       0,                                    0    },
    { state_error,      &STATE_Alive_state_error_Transitions, sizeof(STATE_Alive_state_error_Transitions)/sizeof(STATE_stateInnerTransition_t) },
};
const uint16_t STATE_Alive_Transitions_Size = sizeof(STATE_Alive_Transitions) / sizeof (STATE_stateOuterTransition_t);


const STATE_stateInnerActionTable_t STATE_Alive_InnerStateActions = {
      /* State              Entry                       Exit */
    { state_ok,             STATE__PowerOn,             0 },
    { state_error,          STATE__PowerOff,            0 },
};

const STATE_stateOuterAction_t STATE_Alive_OuterStateActions = {
    &STATE_Alive_InnerStateActions,
    sizeof(STATE_Alive_InnerStateActions) / sizeof(STATE_stateInnerAction_t)
};
    

//==================================================== WINDOW WATCHDOG ======================================


//==================================================== Q/A WATCHDOG =========================================



/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Initialise the state machine, especially the internal object
 * \return RC_SUCCESS;
 */
RC_t STATE_init()
{

}

/**
 * Add the tick in ms to the timer variable
 */
void STATE_tick()
{
    WATCHDOG_IncrementTimer( WATCHDOG_TICKTIME );
}





/**
 * Set power in / Enable WDA pin
 **/
static void STATE__PowerOn()
{
    GPIO_setPowerOff(1);
}

/**
 * Set power off / Disable WDA pin
 **/
static void STATE__PowerOff()
{
    GPIO_setPowerOff(0);
}

/**
 * Reset Timer of Watchdog
 **/
static void STATE__resetTimer()
{
    WATCHDOG_ResetTimer();
}


/**
 * Check Timeout Watchdog Timeout Window
 * timeout value will be read from configuration based on Time switches on the board
 * /param uint16_t currentTime      - IN: CurrenTickTime
 * /return true if currentTime > timeout, otherwise flase
 */
static boolean_t STATE__Alive_Timeout_NOK()
{
    WATCHDOG_time_t currentTime = WATCHDOG_GetTime();
    WATCHDOG_time_t timeout = WATCHDOG_getEndTime();
    
    if (currentTime > timeout)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * Check Timeout Watchdog Timeout Window
 * timeout value will be read from configuration based on Time switches on the board
 * /param uint16_t currentTime      - IN: CurrenTickTime
 * /return true if currentTime < timeout, otherwise flase
 */
static boolean_t STATE__Alive_Timeout_OK()
{
    WATCHDOG_time_t currentTime = WATCHDOG_GetTime();
    WATCHDOG_time_t timeout = WATCHDOG_getEndTime();
    
    
    
    if (currentTime < timeout)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * Check Window Watchdog Window
 * timeout value will be read from configuration based on Time switches on the board
 * /param uint16_t currentTime      - IN: CurrenTickTime
 * /return true if currentTime is in window, otherwise flase
 */
static boolean_t STATE__Window_checkWindow()
{
    WATCHDOG_time_t currentTime = WATCHDOG_GetTime();
    WATCHDOG_time_t starttime = WATCHDOG_getStartTime();
    WATCHDOG_time_t endtime = WATCHDOG_getEndTime();

        
    if (starttime < currentTime && currentTime < endtime)
    {
        WATCHDOG_SetPrevWindow(TRUE);
        //WATCHDOG_object.m_prevWindowValid = TRUE;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * Check Window Watchdog Window - only timeout
 * This function is required to check if the ev_tick in case no trigger is coming
 * /param uint16_t currentTime      - IN: CurrenTickTime
 * /return true if currentTime is in window, otherwise flase
 */
static boolean_t STATE__Window_checkTimeout()
{
    WATCHDOG_time_t currentTime = WATCHDOG_GetTime();
    WATCHDOG_time_t endtime = WATCHDOG_getEndTime();
        
    
    if (currentTime < endtime)
    {
        return TRUE;
    }
    else
    {
        if (TRUE == WATCHDOG_GetPrevWindow())
        {
            WATCHDOG_SetTime(WATCHDOG_GetTime() % endtime);
            //WATCHDOG_object.m_timer %= endtime;
            WATCHDOG_SetPrevWindow(FALSE);
            //WATCHDOG_object.m_prevWindowValid = FALSE;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}



/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

#define STATE_INVALIDINDEX -1
sint16_t STATE__getIndexOfState(STATE_stateOuterTransitionTable_t const * const  transitionTable,
                                uint16_t transitionTableSize,
                                STATE_state_t state)
{
    sint16_t result = STATE_INVALIDINDEX; //error
    
    for (uint16_t i = 0; i < transitionTableSize; i++)
    {
        if ((*transitionTable)[i].fromState == state)
        {
            return i;
        }
    }
    
    return STATE_INVALIDINDEX; 
}

/**
 * This function will process the event with the defined state machine
 * The state machine is implemented as a singleton object, only the configuration may differ
 * \param STATE_stateTransitionTable_t const * const transitionTable    : IN - Pointer to the transition table
 * \param uint16_t transitionTableSize                                  : IN - Size of the transition table
 * \param STATE_stateActionTable_t const * const actionTable            : IN - Pointer to the action table
 * \param STATE_event_t ev                                              : IN - Event to be processed
 * \param  STATE_state_t* state                                         : IN/OUT - New State
 * \return RC_SUCCESS or error
 */
RC_t STATE_processEvent(STATE_stateOuterTransitionTable_t const * const  transitionTable,
                        uint16_t transitionTableSize,
                        STATE_stateOuterAction_t const* const actionTable, 
                        STATE_event_t ev,
                        STATE_state_t* state)
{
    
    STATE_GuardPtr_t guard = 0;
    STATE_ActionPtr_t acTransition = 0;
    STATE_ActionPtr_t acEntry = 0;
    STATE_ActionPtr_t acExit = 0;
    
    
    //Read the state from the watchdog object;
    STATE_state_t currentState = *state;
    STATE_state_t toState = currentState; //Just in case
    
    //Calculate the table index of the outer table
    sint16_t index = STATE__getIndexOfState(transitionTable, transitionTableSize, currentState);
    
    //This should never happen
    if (STATE_INVALIDINDEX == index)
    {
        return RC_ERROR_RANGE;
    }
    
    STATE_stateInnerTransitionTable_t const* const pInnerTable = (*transitionTable)[index].pInnerTransitionTable;
    
    uint16_t innerTableSize = 0;
    if (0 != pInnerTable)
	{
		innerTableSize = (*transitionTable)[index].size;
	}
    
    if (0 == pInnerTable || 0 == innerTableSize)
    {
        //No transitions in this state
        return RC_ERROR_INVALID_STATE;
    }
    
    //Iterate through the inner table and find correct transition
    for (uint16_t i = 0; i < innerTableSize; i++)
    {
        if ((*pInnerTable)[i].event == ev)
        {
            //Transition found, let's check the guard
            guard = (*pInnerTable)[i].guard;
            if (0 == guard || TRUE == guard())
            {
                //Transition is valid
                acTransition = (*pInnerTable)[i].actionTransition;
                toState = (*pInnerTable)[i].toState;
                
                //Now lets find the entry and exit actions
                uint16_t actionTableSize = actionTable->size;
                for (uint16_t j = 0; j < actionTableSize; j++)
                {
                    if (currentState == (*actionTable->pInnerStateTable)[j].state)
                    {
                        acExit = (*actionTable->pInnerStateTable)[j].actionExit;
                    }
                    if (toState == (*actionTable->pInnerStateTable)[j].state)
                    {
                        acEntry = (*actionTable->pInnerStateTable)[j].actionEntry;
                    }
                }

                //Lets call the actions
                if (0 != acExit) acExit();
                if (0 != acTransition) acTransition();
                if (0 != acEntry) acEntry();
                

                
                //If we want to fire only one transition, the break must be actiavted
                //Note: More than one transition only make sense, if the taregt states are identical
                //This must be ensured by the user
                //break;
            }
        }
    }
    
    //Copy local toState to external State Variable
    *state = toState;
    
 
    return RC_SUCCESS;
}


