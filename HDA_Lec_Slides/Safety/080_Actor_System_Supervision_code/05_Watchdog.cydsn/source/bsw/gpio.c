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
#include "gpio.h"

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


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/




/**
 * Sets the WDA Pin to low (FailSafe)
 * /param none
 * /return RC_SUCCESS 
 */
RC_t GPIO_setPowerOff(uint8_t value)
{
    RC_t result = RC_SUCCESS;
    
    //Explicitly check for the parameter value
    if (1 == value) 
    {
        WDA_Write(1);
    }
    else if (0 == value)
    {
        WDA_Write(0);
    }
    else 
    {
        WDA_Write(0);
        result = RC_ERROR_BAD_PARAM;
    }
    
    return result;
}


/**
 * Set/Reset the GP1 warn pin
 */
RC_t GPIO_setWarn(uint8_t value)
{
    
    RC_t result = RC_SUCCESS;
    
    //Explicitly check for the parameter value
    if (1 == value) 
    {
        GP1_Write(1);
    }
    else if (0 == value)
    {
        GP1_Write(0);
    }
    else 
    {
        GP1_Write(0);
        result = RC_ERROR_BAD_PARAM;
    }
    
    return result;
 
}

/**
 * Set/Reset the GP2 error pin
 */
RC_t GPIO_setError(uint8_t value)
{
    
    RC_t result = RC_SUCCESS;
    
    //Explicitly check for the parameter value
    if (1 == value) 
    {
        GP2_Write(1);
    }
    else if (0 == value)
    {
        GP2_Write(0);
    }
    else 
    {
        GP2_Write(0);
        result = RC_ERROR_BAD_PARAM;
    }
    
    return result;
    
}

/**
 * Toggle the GP1 warn pin
 */
RC_t GPIO_toggleWarn()
{
    static uint8_t toggleWarn = 0;
    
    toggleWarn = (toggleWarn + 1) % 2;
    
    GP1_Write(toggleWarn);
}

/**
 * Toggle the GP2 error pin
 */
RC_t GPIO_toggleError()
{
    static uint8_t toggleError = 0;
    
    toggleError = (toggleError + 1) % 2;
    
    GP2_Write(toggleError);
}

