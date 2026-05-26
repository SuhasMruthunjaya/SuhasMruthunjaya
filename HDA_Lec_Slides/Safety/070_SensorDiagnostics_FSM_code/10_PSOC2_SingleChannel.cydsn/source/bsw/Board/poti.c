/**
* \file joystick.c
* \author P. Fromm
* \date 29.8.17
*
* \brief Joystick driver
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

#include "logging.h"

#include "project.h"
#include "poti.h"



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
 * Initialisation of the Joystick
 * @return RC_SUCCESS if all ok
 */
RC_t POTI_Init()
{
    
    ADC_SAR_Seq_Start();
    ADC_SAR_Seq_StartConvert();

    
    return RC_SUCCESS;
}

//Read and convert 12bit ADC value
sint16_t POTI__readChannel(uint8_t channel)
{
    uint16_t data = 0;
    
    //Wait for end of conversion
    ADC_SAR_Seq_IsEndConversion(ADC_SAR_Seq_SAR_WAIT_FOR_RESULT);
    
    data = ADC_SAR_Seq_GetResult16(channel);
    
    sint16_t result = (sint16_t)((data - 2048) * 100 / 2048);
    
    LOG(LOG_DEBUG, "POTI__readChannel"," %d\n",data);
    
    return result;
}



/**
 * Read the Joystick position
 * @param POTI_channel_t channel - IN channel to be read
 * @param uint8_t* pos - position of the potentiometer
 * @return RC_SUCCESS if all ok
 */
RC_t POTI_ReadPosition(POTI_channel_t channel, sint16_t* pos)
{


    //Read channel
    switch (channel)
    {
        case POTI_1 : *pos = POTI__readChannel(0); break;
        case POTI_2 : *pos = POTI__readChannel(1); break;
        case POTI_3 : *pos = POTI__readChannel(2); break;
     
        default: *pos = 0;
    }
    
    return RC_SUCCESS;
}
    

