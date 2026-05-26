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

#include "ex_wdg.h"

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

static struct 
{
    EXWDG_id_t  m_type;
} EXWDG__object;


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/**
 * Watchdog initialisation
 * \param EXWDG_id_t id     - [IN] Type of selected Watchdog Function
 * \return RC_SUCCESS or error code
 */
RC_t EXWDG_Init(EXWDG_id_t id)
{
    EXWDG__object.m_type = id;
    
    //Toggle Reset Pin of atchdog once to activate it
    Pin_WdgReset_Write(0);
    CyDelay(1);
    Pin_WdgReset_Write(1);
    CyDelay(1);
    Pin_WdgReset_Write(0);
    
    
}

/**
 * Watchdog Trigger
 * \return RC_SUCCESS or error code
 */
RC_t EXWDG_Trigger()
{
    static uint8_t toggle = 0;
    
    if (EXWDG_Alive == EXWDG__object.m_type)
    {
        if (toggle == 0) toggle = 1; else toggle = 0;
        Pin_Safe_1_Write(toggle);
    }
}