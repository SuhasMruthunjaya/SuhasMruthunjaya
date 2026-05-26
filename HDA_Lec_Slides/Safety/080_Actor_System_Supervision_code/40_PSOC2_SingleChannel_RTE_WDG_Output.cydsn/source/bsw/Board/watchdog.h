/**
* \file watchdog.h
* \author P. Fromm
* \date 30.11.18
*
* \brief Watchdog API for PSOC
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
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
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Enumerations
/**
*
* The WDT timeout is between two and three programmable tap periods, based on the free-running Central Timewheel.
*/
 enum eWDTimeOuts{
    WD_TO_1024,          /**< \brief Timeout 1024 ticks, 2048 - 3072 ms */
    WD_TO_128,           /**< \brief Timeout 128 ticks, 256 - 384 ms */
    WD_TO_16,            /**< \brief Timeout 16 ticks, 32 - 48 ms */
    WD_TO_2,             /**< \brief Timeout 2 ticks, 4 - 6 ms */

} ;
typedef enum eWDTimeOuts WDT_TimeOut_t;


// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class WATCHDOG
{
public:
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Activate the Watchdog Trigger
 * \param WDT_TimeOut_t timeout     - [IN] Timeout Period
 * @return RC_SUCCESS
 */
RC_t WD_Start(WDT_TimeOut_t timeout);

/**
 * Service the Watchdog Trigger
 * @return RC_SUCCESS
 */
RC_t WD_Trigger();

/**
 * Checks the watchdog bit
 * @return TRUE if reset bit was set
 */
boolean_t WD_CheckResetBit();

/**
 * Configure the number of Checkpoints
 * \param uint8_t noCheckpoints     - [IN] Number of CHeckpoint - will be used to calculate reference bitpattern
 * @return RC_SUCCESS
 */
RC_t WD_ActivateCheckpoints(uint8_t noCheckpoints);

/**
 * Will check if all checkpoints have been hit
 * Checkpoints will be reset
 */
boolean_t WD_AllCheckpointsHit();

/**
 * Hit checkpoint
 * \param uint8_t checkpoint    - [IN] bit which will be set. First bit has index 0
 */
RC_t WD_HitCheckpoint(uint8_t checkpoint);

/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER

};
#endif /* Together */

#endif /* FILE_H */
