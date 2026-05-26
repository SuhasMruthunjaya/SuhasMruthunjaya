/**
* \file watchdog.c
* \author P. Fromm
* \date 22.3.20
*
* \brief Watchdog Statemachine
*
* \copyright Copyright ©2020
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

#include "watchdog.h"
#include "watchdog_cfg.h"
#include "statemachine.h"


#include "gpio.h"
#include "dip.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

WATCHDOG_t WATCHDOG_Alive_object = {state_ok, 0, TRUE};

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/





/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
#if 0
/**
 * State machine Logic for Watchdog Off
 * In this mode, the alive pin will always be high, event is ignored
 * /param WDT_trigger_t ev      - IN : Event to be processed
 * /return RC_SUCCESS or error code 
 */
RC_t WATCHDOG__ProcessTrigger_Off(STATE_event_t ev);

/**
 * State machine Logic for Alive Watchdog
 * In this mode, the alive pin will be high, unless the ticktime is beyond the Alive Time parameter
 * /param WDT_trigger_t ev      - IN : Event to be processed
 * /return RC_SUCCESS or error code 
 */
RC_t WATCHDOG__ProcessTrigger_Alive(STATE_event_t ev);

/**
 * State machine Logic for Window Watchdog
 * In this mode, the alive pin will be high, unless the ticktime is out of the window timeline
 * /param WDT_trigger_t ev      - IN : Event to be processed
 * /return RC_SUCCESS or error code 
 */
RC_t WATCHDOG__ProcessTrigger_Window(STATE_event_t ev);

/**
 * State machine Logic for QA Watchdog
 * In this mode, the alive pin will be high, unless the answer is received beyound the Alive time OR the answer is wrong
 * /param WDT_trigger_t ev      - IN : Event to be processed
 * /return RC_SUCCESS or error code 
 */
RC_t WATCHDOG__ProcessTrigger_QA(STATE_event_t ev);

#endif


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Init Function for the Watchdog
 * /param none
 * /return RC_SUCCESS 
 */
RC_t WATCHDOG_Init()
{
    RC_t result = RC_ERROR;
    
    WATCHDOG_Alive_object.m_state = state_ok;
    WATCHDOG_Alive_object.m_timer = 0;
    WATCHDOG_Alive_object.m_prevWindowValid = TRUE;
    
    result = GPIO_setPowerOff(1);
    result = GPIO_setError(0);
    result = GPIO_setWarn(0);
    
    return result;
}

/**
 * Main Function of the Watchdog, contains the internal state machine
 * /param WDT_trigger_t ev : IN - Event to be processed by the state machine
 * /return RC_SUCCESS 
 */
RC_t WATCHDOG_ProcessTrigger(STATE_event_t ev)
{
    RC_t result = RC_ERROR;
    
    //Check the mode configuration
    DIP_mode_t mode = DIP_readMode();
 
    switch (mode)
    {
        //Watchdog turned off
        case DIP_mode_off: 
            STATE_init();
            result = GPIO_setPowerOff(1); 
            break;

        //Timeout Watchdog
        case DIP_mode_alive: 
            result = STATE_processEvent(&STATE_Alive_Transitions, STATE_Alive_Transitions_Size, &STATE_Alive_OuterStateActions, 
                                        ev, &WATCHDOG_Alive_object.m_state);  
            break;

        //Timeout Watchdog
        case DIP_mode_window: break;
        
        //Q/A Watchdog - to be added
        
        default: result = RC_ERROR_INVALID_STATE;
    }

    return result;
    
}



/**
 * Function must be called in ISR when alive trigger is received
 * /param none
 * /return RC_SUCCESS 
 */
RC_t WATCHDOG_Trigger_isr()
{
    RC_t result = RC_ERROR;
    
    result = WATCHDOG_ProcessTrigger(ev_trigger);
    
    return result;
}

/**
 * Increments the time of the watchdog object 
 * \param uint16_t ms           : IN - time in ms
 * \return RC_SUCCESS
 */
RC_t WATCHDOG_IncrementTimer(uint16_t ms)
{
    RC_t result = RC_ERROR;
    
    //Check the mode configuration
    DIP_mode_t mode = DIP_readMode();
 
    switch (mode)
    {
        //Watchdog turned off
        case DIP_mode_off: 
            WATCHDOG_Init();
            break;

        //Timeout Watchdog
        case DIP_mode_alive: WATCHDOG_Alive_object.m_timer += ms;  break;

        //Timeout Watchdog
        case DIP_mode_window: break;
        
        //Q/A Watchdog - to be added
        
        default: result = RC_ERROR_INVALID_STATE;
    }

    return result;
}

/**
 * Reset the time of the watchdog object 
 * \return RC_SUCCESS
 */
RC_t WATCHDOG_ResetTimer()
{
    return WATCHDOG_SetTime(0);
}

/**
 * Read the current time of the watchdog object 
 * \return current time
 */
RC_t WATCHDOG_SetTime(WATCHDOG_time_t time)
{
        RC_t result = RC_ERROR;
    
    //Check the mode configuration
    DIP_mode_t mode = DIP_readMode();
 
    switch (mode)
    {
        //Watchdog turned off
        case DIP_mode_off: 
            WATCHDOG_Alive_object.m_timer = time;
            break;

        //Timeout Watchdog
        case DIP_mode_alive: 
            WATCHDOG_Alive_object.m_timer = time;  
            break;

        //Timeout Watchdog
        case DIP_mode_window: break;
        
        //Q/A Watchdog - to be added
        
        default: result = RC_ERROR_INVALID_STATE;
    }

    return result;
}

/**
 * Read the current time of the watchdog object 
 * \return current time
 */
WATCHDOG_time_t WATCHDOG_GetTime()
{

    WATCHDOG_time_t currTime = 0;
    
    //Check the mode configuration
    DIP_mode_t mode = DIP_readMode();
 
    switch (mode)
    {
        //Watchdog turned off
        case DIP_mode_off: 
            currTime = 0;
            break;

        //Timeout Watchdog
        case DIP_mode_alive: 
            currTime = WATCHDOG_Alive_object.m_timer;  
            break;

        //Timeout Watchdog
        case DIP_mode_window: break;
        
        //Q/A Watchdog - to be added
        
        default: break;
    }

    return currTime;
}

/**
 * Set the previous window state
 * \return RC_SUCCESS
 */
RC_t WATCHDOG_SetPrevWindow(boolean_t preWindow)
{

    RC_t result = RC_ERROR;
    
    //Check the mode configuration
    DIP_mode_t mode = DIP_readMode();
 
    switch (mode)
    {
        //Watchdog turned off
        case DIP_mode_off: 
            WATCHDOG_Alive_object.m_prevWindowValid = preWindow;
            break;

        //Timeout Watchdog
        case DIP_mode_alive: 
            WATCHDOG_Alive_object.m_prevWindowValid = preWindow;
            break;

        //Timeout Watchdog
        case DIP_mode_window: break;
        
        //Q/A Watchdog - to be added
        
        default: result = RC_ERROR_INVALID_STATE; break;
    }

    return result;
}

/**
 * Set the previous window state
 * \return RC_SUCCESS
 */
boolean_t WATCHDOG_GetPrevWindow()
{


    boolean_t prevWin = FALSE;
    
    //Check the mode configuration
    DIP_mode_t mode = DIP_readMode();
 
    switch (mode)
    {
        //Watchdog turned off
        case DIP_mode_off: 
            prevWin = TRUE;;
            break;

        //Timeout Watchdog
        case DIP_mode_alive: 
            prevWin = WATCHDOG_Alive_object.m_prevWindowValid;
            break;

        //Timeout Watchdog
        case DIP_mode_window: break;
        
        //Q/A Watchdog - to be added
        
        default: break;
    }

    return prevWin;
}


/** --------------- old switch case implementations ------------------------ **/
#if 0
/**
 * State machine Logic for Watchdog Off
 * In this mode, the alive pin will always be high, event is ignored
 * /param WDT_trigger_t ev      - IN : Event to be processed
 * /return RC_SUCCESS or error code 
 */
RC_t WATCHDOG__ProcessTrigger_Off(STATE_event_t ev)
{
    RC_t result = RC_SUCCESS;
    
    //Reset Watchdog object
    WATCHDOG_object.m_state = state_ok;
    WATCHDOG_object.m_timer = 0;
    
    //Set Alive pin high
    result = WATCHDOG_SetAlive();
    
    return result;
}
    
//State machine Logic for Alive Watchdog
RC_t WATCHDOG__ProcessTrigger_Alive(STATE_event_t ev)
{
    RC_t result = RC_ERROR;
    
    switch (WATCHDOG_object.m_state)
    {
        case state_ok:
            if (ev_tick == ev)
            {
                if (TRUE == WATCHDOG__Alive_checkTimeout())
                {
                    WATCHDOG_object.m_timer += WATCHDOG_TICKTIME;
                }
                else
                {
                    WATCHDOG_object.m_timer += WATCHDOG_TICKTIME;
                    WATCHDOG_object.m_state = state_error;
                    result = WATCHDOG_SetFailsafe();
                }
            }
            else if (ev_trigger == ev)
            {
                //Alive Watchdog - simply set time to 0
                WATCHDOG_object.m_timer = 0;
            }
            else if (ev_triggerNotOk == ev)
            {
                //Should not happen for ALive mode, but just in case
                WATCHDOG_object.m_timer = 0;
                WATCHDOG_object.m_state = state_error;
                result = WATCHDOG_SetFailsafe();
            }
            else if (ev_restart == ev)
            {
                //Simply reset timer
                WATCHDOG_object.m_timer = 0;
            }
            else
            {
                return RC_ERROR_BAD_PARAM;
            }
        
            break;

        case state_warn:
        // This state will be added later
        
            break;

        case state_error:
            if (ev_tick == ev)
            {
                result = WATCHDOG_SetFailsafe();
            }
            else if (ev_trigger == ev)
            {
                result = WATCHDOG_SetFailsafe();
            }
            else if (ev_triggerNotOk == ev)
            {
                result = WATCHDOG_SetFailsafe();
            }
            else if (ev_restart == ev)
            {
                //Reset timer
                WATCHDOG_object.m_timer = 0;
                WATCHDOG_object.m_state = state_ok;
           } 
            else
            {
                return RC_ERROR_BAD_PARAM;
            }

            break;
     
        default: return RC_ERROR;
    }
    return RC_SUCCESS;
}


//State machine Logic for Window Watchdog
RC_t WATCHDOG__ProcessTrigger_Window(STATE_event_t ev)
{
    RC_t result = RC_ERROR;
    switch (WATCHDOG_object.m_state)
    {
        case state_ok:
        
        //Debug - Visualising the window ====================================================================================================================
        #if 0
        if (WATCHDOG_object.m_timer == WATCHDOG_getStartTime() || WATCHDOG_object.m_timer == WATCHDOG_getEndTime())
        {
            WATCHDOG_toggleError();
        }
        #endif
        
            if (ev_tick == ev)
            {

                if (FALSE == WATCHDOG__Window_checkTimeout())
                {
                    WATCHDOG_object.m_timer += WATCHDOG_TICKTIME;
                    WATCHDOG_object.m_state = state_error;
                    result = WATCHDOG_SetFailsafe();
                }
                else
                {
                    WATCHDOG_object.m_timer += WATCHDOG_TICKTIME;
                }

            }
            else if (ev_trigger == ev)
            {


                
                //This is the piece of extra safety as compared to the alive watchdog
                //We check the correct timing of the trigger event
                if (TRUE == WATCHDOG__Window_checkWindow())
                {
                    //Trigger fired in the open window
                    //As it is a window watchdog, we cannot simply set it to 0
                    //Instead, we bring it back into the first frame
                    WATCHDOG_object.m_timer %= WATCHDOG_getEndTime();
                    
                }
                else
                {
                    //Trigger fired out of the open window
                    WATCHDOG_object.m_state = state_error;
                    result = WATCHDOG_SetFailsafe();
                }
                    
                
            }
            else if (ev_triggerNotOk == ev)
            {
                WATCHDOG_object.m_timer = 0;
                WATCHDOG_object.m_state = state_error;
                result = WATCHDOG_SetFailsafe();
            }
            else if (ev_restart == ev)
            {
                //Do nothing
            }
            else
            {
                return RC_ERROR_BAD_PARAM;
            }
        
            break;

        case state_warn:
        // This state will be added later
        
            break;

        case state_error:
            if (ev_tick == ev)
            {
                result = WATCHDOG_SetFailsafe();
            }
            else if (ev_trigger == ev)
            {
                result = WATCHDOG_SetFailsafe();
            }
            else if (ev_triggerNotOk == ev)
            {
                result = WATCHDOG_SetFailsafe();
            }
            else if (ev_restart == ev)
            {
                //Reset timer
                WATCHDOG_object.m_timer = 0;
                WATCHDOG_object.m_state = state_ok;
            }
            else
            {
                return RC_ERROR_BAD_PARAM;
            }
        
            break;
     
        default: return RC_ERROR;
    }
    return RC_SUCCESS;
}

#endif

/** -------------------------------- Helper Functions / GPIO --------------------------------------------- **/



