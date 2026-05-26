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
#include "led.h"


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


static LED_ONOFF_t LED__state[LED_ALL] = {LED_OFF, LED_OFF, LED_OFF, LED_OFF}; /**< On/Off State of the LED, TRUE is on */


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/**
 * Inverts the parameter
 * @param LED_ONOFF_t ledOnOff - Value to be inverted
 * @return inverted parameter
 */
static inline LED_ONOFF_t LED__toggleValue(LED_ONOFF_t ledOnOff);


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Initialises the LED's and turns them off
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_Init()
{
    RC_t result = RC_SUCCESS;
    
    for (LED_id_t i = LED_1; i < LED_ALL; i++)
    {
        LED__state[i] = LED_OFF;
        
        RC_t clearResult;
        clearResult = LED_Set(i, LED_OFF);
        
        if (clearResult != RC_SUCCESS)
        {
            //memorize error
            result = clearResult;
        }
    }
    
    return result;
}

/**
 * Sets the required LED
 * @param LED_t ledId - Identifier for the LED, ALL will change all LED's
 * @param LED_ONOFF_t ledOnOff - Trun the led on or off
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_Set(LED_id_t ledId, LED_ONOFF_t ledOnOff)
{
    //set individual LED
    switch (ledId)
    {
        case LED_1 : 
            LED_1_Write(ledOnOff); 
            LED__state[ledId] = ledOnOff; 
            break;
        
        case LED_2 : 
            LED_2_Write(ledOnOff); 
            LED__state[ledId] = ledOnOff;
            break;
            
        case LED_3 : 
            LED_3_Write(ledOnOff); 
            LED__state[ledId] = ledOnOff;
            break;
            
        case LED_4 : 
            LED_4_Write(ledOnOff); 
            LED__state[ledId] = ledOnOff;
            break;
           
        case LED_ALL : 
            for (LED_id_t i = LED_1; i < LED_ALL; i++)
            {
                LED_Set(i, ledOnOff);
            }
            break;
        default: return RC_ERROR_BAD_PARAM;
    }
    
    return RC_SUCCESS;
}



/**
 * Toggle the required LED
 * @param LED_t ledId - Identifier for the LED, ALL will change all LED's
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t LED_Toggle(LED_id_t ledId)
{
    //set individual LED
    switch (ledId)
    {
        case LED_1 : 
            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
            LED_1_Write(LED__state[ledId]);
            break;
        
        case LED_2 : 
            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
            LED_2_Write(LED__state[ledId]);
            break;
            
        case LED_3 : 
            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
            LED_3_Write(LED__state[ledId]);
            break;
     
        case LED_4 : 
            LED__state[ledId] = LED__toggleValue(LED__state[ledId]); 
            LED_4_Write(LED__state[ledId]);
            break;    
        
        case LED_ALL : 
            for (LED_id_t i = LED_1; i < LED_ALL; i++)
            {
                LED_Toggle(i);
            }
            break;
        default: return RC_ERROR_BAD_PARAM;
    }
    
    return RC_SUCCESS;
}


/**
 * Inverts the parameter
 * @param LED_ONOFF_t ledOnOff - Value to be inverted
 * @return inverted parameter
 */
static inline LED_ONOFF_t LED__toggleValue(LED_ONOFF_t ledOnOff)
{
    if (ledOnOff == LED_ON) 
    {
        return LED_OFF;
    }
    else
    {
        return LED_ON;
    }
}


