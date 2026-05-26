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

#include "rte.h"
#include "rte_signalpool.h"

#include "error.h"
#include "engine.h"
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



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

static volatile uint8_t ERROR__PIN = 1;

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Central error handler
 * At the moment only display of the error 
 */
void ERROR_centralHandler(CAR_error_t error)
{
    //Only heavy escalation in case of logic error
    //Other error are handled by PSOC 2
    if (ERROR_LOGIC == error )
    {
        ERROR__PIN = 0;
        ERROR_setSafteyPin();
        LOG_E("ERROR_centralHandler","Stopped engine");
    }
    else
    {
        //LOG_E("ERROR_centralHandler","Errorcode: %d",error);
    }
    
}

/**
 * Safety Pin Handler
 */
void ERROR_setSafteyPin()
{
    Pin_Safe_2_Write(ERROR__PIN);
}
