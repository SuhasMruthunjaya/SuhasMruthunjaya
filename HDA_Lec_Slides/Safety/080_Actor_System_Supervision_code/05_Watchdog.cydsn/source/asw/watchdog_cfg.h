/**
* \file watchdog_cfg.h
* \author Peter Fromm
* \date 8.3.20
*
* \brief configuration for PSOC4 watchdog trigger
*
* detailed description what the file does
*
* \note <notes>
*
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


 
#ifndef WATCHDOG_CFG_H
#define WATCHDOG_CFG_H

#include "global.h"
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#define WATCHDOG_TICKTIME       10      /**< /brief Ticktime of the state machine */

/*****************************************************************************/
/* Global type definitions ('typedef')                                       */
/*****************************************************************************/

/**
  * Type for timer tick data
  */
typedef uint32_t WATCHDOG_time_t;
    
/**
 * Record containing timeout and reset time in [ms]
 */
typedef struct
    {
        WATCHDOG_time_t m_timeout;     /**< \brief Open of trigger window */
        WATCHDOG_time_t m_reset;       /**< \brief Minimum time for reset (to avoid permanet reset) */
    } WATCHDOG_Alive_t;    
    
/**
 * Record containing start and endtime of window in [ms]
 */
typedef struct
    {
        WATCHDOG_time_t m_start;       /**< \brief Open of trigger window */
        WATCHDOG_time_t m_end;         /**< \brief Close of trigger window */
        WATCHDOG_time_t m_reset;       /**< \brief Minimum time for reset (to avoid permanet reset) */
    } WATCHDOG_Window_t;
    
//Todo: define own type
typedef WATCHDOG_Alive_t WATCHDOG_QA_t;


/*****************************************************************************/
/* Global function definitions                                               */
/*****************************************************************************/

/**
 * Getters to read out the configuration tables
 * Based on the time configuration
 */
WATCHDOG_time_t WATCHDOG_getStartTime();
WATCHDOG_time_t WATCHDOG_getEndTime();
WATCHDOG_time_t WATCHDOG_getMinResetTime();


#endif /* WATCHDOG_CFG_H */
