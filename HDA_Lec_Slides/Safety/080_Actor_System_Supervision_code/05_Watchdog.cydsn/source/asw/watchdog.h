/**
* \file watchdog.h
* \author P. Fromm
* \date 8.3.2020
*
* \brief Watchdog driver for PSOC4
*
* Provides elementary watchdog functions
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 0.01; 08.03.2020; P. Fromm
*            - Initial creation, simple timout watchdog function
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
**/


 
#ifndef WATCHDOG_H
#define WATCHDOG_H
    
#include "global.h"
#include "watchdog_cfg.h"
#include "statemachine.h"
    
/*****************************************************************************/
/* Global Type Definitions                                                   */
/*****************************************************************************/


struct sWatchdog
{
    STATE_state_t    m_state;           /**< /brief Current Watchdog State */
    WATCHDOG_time_t  m_timer;           /**< /brief Current Watchdog Timer */
    boolean_t        m_prevWindowValid; /**< /brief flag to show that the previous window has been valid */
};
typedef struct sWatchdog WATCHDOG_t;
  


// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class Watchdog
{
public:
#endif /* Together */

/*****************************************************************************/
/* Globals                                                                   */
/*****************************************************************************/

extern WATCHDOG_t WATCHDOG_Alive_object;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Init Function for the Watchdog
 * \param none
 * \return RC_SUCCESS 
 */
RC_t WATCHDOG_Init();

/**
 * Main Function of the Watchdog, contains the internal state machine
 * \param WDT_trigger_t ev : IN - Event to be processed by the state machine
 * \return RC_SUCCESS 
 */
RC_t WATCHDOG_ProcessTrigger(STATE_event_t ev);

/**
 * Function must be called in ISR when alive trigger is received
 * \param none
 * \return RC_SUCCESS 
 */
RC_t WATCHDOG_Trigger_isr();

/**
 * Increments the time of the watchdog object 
 * \param uint16_t ms           : IN - time in ms
 * \return RC_SUCCESS
 */
RC_t WATCHDOG_IncrementTimer(uint16_t ms);

/**
 * Reset the time of the watchdog object 
 * \return RC_SUCCESS
 */
RC_t WATCHDOG_ResetTimer();


/**
 * Read the current time of the watchdog object 
 * \return current time
 */
RC_t WATCHDOG_SetTime(WATCHDOG_time_t time);

/**
 * Read the current time of the watchdog object 
 * \return current time
 */
WATCHDOG_time_t WATCHDOG_GetTime();

/**
 * Set the previous window state
 * \return RC_SUCCESS
 */
RC_t WATCHDOG_SetPrevWindow(boolean_t preWindow);

/**
 * Set the previous window state
 * \return RC_SUCCESS
 */
boolean_t WATCHDOG_GetPrevWindow();

/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER
//Not visible for compiler, only used for document generation
private:

};
#endif /* Together */

#endif /* WATCHDOG_H */
