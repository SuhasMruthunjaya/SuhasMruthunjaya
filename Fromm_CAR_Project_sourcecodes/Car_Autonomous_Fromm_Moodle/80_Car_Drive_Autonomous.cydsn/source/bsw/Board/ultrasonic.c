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
#include "logging.h"
#include "ultrasonic.h"


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
 * Init function of the Ultrasonic Sensor
 * @return RC_SUCCESS
 */
RC_t US_Init()
{
    return RC_SUCCESS;
}

/**
 * Fire function of the Ultrasonic Sensor
 * \param US_id_t   : [IN] The sensor to be fired
 * @return RC_SUCCESS
 */
RC_t US_Fire(US_id_t id)
{
    //LOG_I("US_Fire","id = %d", id);
    
    //Get the MCAL function
    US_trigger trigger = US_ports[id].m_trigger_func;
    US_echo    echo    = US_ports[id].m_echo_func;

    if (0 != trigger)
    {
        trigger(1);
        CyDelayUs(10);
        trigger(0);
    }
    else
    {
        LOG_E("US_Fire","no pin config - id = %d",id);
    }
}

/**
 * A brute force polling implementation of the driver
 * \param US_id_t id                : [IN] The sensor to be fired
 * \param uint16_t* const distance  : [OUT] Distance in cm
 * @return RC_SUCCESS
 */
RC_t US_GetDistance_poll(US_id_t id, uint16_t* const distance)
{
    //Get the MCAL function
    US_trigger trigger = US_ports[id].m_trigger_func;
    US_echo    echo    = US_ports[id].m_echo_func;
    
    if (0 != trigger && 0!= echo)
    {
        //Fire the trigger
        trigger(1);
        CyDelayUs(10);
        trigger(0);
        
        //Wait until rising edge of echo signal
        while(1)
        {
            if (1== echo()) break;
        }
        
        //wait until falling edge and count time - with an unknown precision
        uint32_t time = 0;
        while(1)
        {
            if (0== echo()) break;
            
            CyDelayUs(10);
            time += 10;
        }
        
        *distance = US_calcDistance(time);
        LOG_I("US_GetDistance_poll","Time = %d Distance = %d", time, *distance);

    }
        else
    {
        *distance = US_INVALIDDISTANCE;
        LOG_E("US_GetDistance_poll","no pin config");
    }
    
}



/**
 * A improved force polling implementation of the driver
 * \param uint16_t* const distance  : [OUT] Distance in cm
 * @return RC_SUCCESS
 */
RC_t US_ReadDistance_isr(uint16_t* const distance)
{

    return RC_ERROR;
    
}

/**
 * Translate time into distance
 * \param uint32_t time_us      : [IN] Time in ys
 * \return distance in cm
 */
uint16_t US_calcDistance(uint32_t time_us)
{
    float result = (float)time_us * 17.15 / 1000;
    return (uint16_t)result;
}