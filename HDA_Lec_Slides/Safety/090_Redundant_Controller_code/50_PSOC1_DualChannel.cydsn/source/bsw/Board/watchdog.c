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
#include "project.h"

#include "watchdog.h"
#include "logging.h"

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

static volatile uint32_t WD__checkpointPattern = 0;
static volatile uint32_t WD__checkPointsHit = 0;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Activate the Watchdog Trigger
 * \param WDT_TimeOut_t timeout     - [IN] Timeout Period
 * @return RC_SUCCESS
 */
RC_t WD_Start(WDT_TimeOut_t timeout)
{
    
    
    switch (timeout)
    {
        WD_TO_2 : CyWdtStart(CYWDT_2_TICKS, CYWDT_LPMODE_NOCHANGE); break;
        WD_TO_16 : CyWdtStart(CYWDT_16_TICKS, CYWDT_LPMODE_NOCHANGE); break;
        WD_TO_128 : CyWdtStart(CYWDT_128_TICKS, CYWDT_LPMODE_NOCHANGE); break;
        WD_TO_1024 : CyWdtStart(CYWDT_1024_TICKS, CYWDT_LPMODE_NOCHANGE); break;
        default : CyWdtStart(CYWDT_1024_TICKS, CYWDT_LPMODE_NOCHANGE); break;
    }
    

    
    return RC_SUCCESS;
}

/**
 * Configure the number of Checkpoints
 * \param uint8_t noCheckpoints     - [IN] Number of CHeckpoint - will be used to calculate reference bitpattern
 * @return RC_SUCCESS
 */
RC_t WD_ActivateCheckpoints(uint8_t noCheckpoints)
{
    if (0 == noCheckpoints)
    {
        WD__checkpointPattern = 0;
    }
    else if (noCheckpoints >= 32)
    {
        WD__checkpointPattern = 0xFFFF;
        return RC_ERROR_BAD_PARAM;
    }
    else
    {
        WD__checkpointPattern = (1<<noCheckpoints)-1;
    }
}


/**
 * Service the Watchdog Trigger
 * @return RC_SUCCESS
 */
RC_t WD_Trigger()
{
    CyWdtClear();   
    return RC_SUCCESS;
}

/**
 * Checks the watchdog bit
 * @return TRUE if reset bit was set
 */
boolean_t WD_CheckResetBit()
{
    if (CyResetStatus & (1<<3))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * Will check if all checkpoints have been hit
 * Checkpoints will be reset
 */
boolean_t WD_allCheckpointsHit()
{
    
    //LOG_I("WD_allCheckpointsHit","%x %x",WD__checkpointPattern, WD__checkPointsHit);
    
    if (WD__checkPointsHit == WD__checkpointPattern) 
    {
        WD__checkPointsHit = 0;
        return TRUE; 
    }
    else 
    {
        return FALSE;
    }
}

/**
 * Hit checkpoint
 */
RC_t WD_hitCheckpoint(uint8_t checkpoint)
{
    RC_t result = RC_SUCCESS;
    if (checkpoint >= 32)
    {
        checkpoint = 32;
        result = RC_ERROR_BAD_PARAM;
    }

    //Or corresponding bit
    WD__checkPointsHit |= (1<<checkpoint);
    
}