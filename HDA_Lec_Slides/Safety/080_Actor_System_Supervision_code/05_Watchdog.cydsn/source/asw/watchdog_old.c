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
#include "statemachine_cfg.h"

#include "gpio.h"
#include "dip.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/



struct sWatchdog
{
    STATE_state_t    m_state;           /**< /brief Current Watchdog State */
    WATCHDOG_time_t  m_timer;           /**< /brief Current Watchdog Timer */
    boolean_t        m_prevWindowValid; /**< /brief flag to show that the previous window has been valid */
};
typedef struct sWatchdog WATCHDOG_t;

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

volatile static WATCHDOG_t WATCHDOG_object = {state_ok, 0, TRUE};

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

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


/**
 * Check Timeout Watchdog Window
 * timeout value will be read from configuration based on Time switches on the board
 * /return true if currentTime < timeout, otherwise false
 */
static boolean_t WATCHDOG__Alive_checkTimeout();

/**
 * Check Window Watchdog Window
 * Will be called if the ev_trigger is fired
 * timeout value will be read from configuration based on Time switches on the board
 * /return true if currentTime is in window, otherwise false
 */
static boolean_t WATCHDOG__Window_checkWindow();

/**
 * Check Window Watchdog Window - only timeout
 * This function is required to check if the ev_tick in case no trigger is coming
 * /return true if currentTime is in window, otherwise false
 */
static boolean_t WATCHDOG__Window_checkTimeout();

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
    
    result = GPIO_SetPowerOff(1);
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
    WATCHDOG_mode_t mode = WATCHDOG_readConfigMode();
 
    switch (mode)
    {
        //Watchdog turned off
        case WATCHDOG_mode_off: result = WATCHDOG__ProcessTrigger_Off(ev); break;

        //Timeout Watchdog
        case WATCHDOG_mode_alive: result = WATCHDOG__ProcessTrigger_Alive(ev); break;

        //Timeout Watchdog
        case WATCHDOG_mode_window: result = WATCHDOG__ProcessTrigger_Window(ev); break;
        
        //Q/A Watchdog - to be added
        
        default: result = RC_ERROR_INVALID_STATE;
    }

    return result;
    
}

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

/** --------------- These functions are normally only called via the statemachine ------------------------ **/



/**
 * Check Timeout Watchdog Timeout Window
 * timeout value will be read from configuration based on Time switches on the board
 * /param uint16_t currentTime      - IN: CurrenTickTime
 * /return true if currentTime < timeout, otherwise flase
 */
static boolean_t WATCHDOG__Alive_checkTimeout()
{
    WATCHDOG_time_t currentTime = WATCHDOG_object.m_timer;
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
static boolean_t WATCHDOG__Window_checkWindow()
{
    WATCHDOG_time_t currentTime = WATCHDOG_object.m_timer;
    WATCHDOG_time_t starttime = WATCHDOG_getStartTime();
    WATCHDOG_time_t endtime = WATCHDOG_getEndTime();

        
    if (starttime < currentTime && currentTime < endtime)
    {
        WATCHDOG_object.m_prevWindowValid = TRUE;
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
static boolean_t WATCHDOG__Window_checkTimeout()
{
    WATCHDOG_time_t currentTime = WATCHDOG_object.m_timer;
    WATCHDOG_time_t endtime = WATCHDOG_getEndTime();
        
    
    if (currentTime < endtime)
    {
        return TRUE;
    }
    else
    {
        if (TRUE == WATCHDOG_object.m_prevWindowValid)
        {
            WATCHDOG_object.m_timer %= endtime;
            WATCHDOG_object.m_prevWindowValid = FALSE;
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

/** -------------------------------- Helper Functions / GPIO --------------------------------------------- **/



