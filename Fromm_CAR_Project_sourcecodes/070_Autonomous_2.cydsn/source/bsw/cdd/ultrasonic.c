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

static uint32_t US_TickTime = 0; /*!< Time in us */

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/**
 * Translate time into distance
 * \param uint32_t time_us      : [IN] Time in ys
 * \return distance in cm
 */
uint16_t US__calcDistance(uint32_t time_us);


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/


/**
 * Fire a single trigger puls - mainly for testing purposes
 * \param US_t const* me      : [IN/OUT] The sensor object
 * @return RC_SUCCESS
 */
RC_t US_Fire(US_t const* me)
{
    //LOG_I("US_Fire","id = %d", id);
    
    //Get the MCAL function
    US_trigger trigger = me->m_trigger_func;

    if (0 != trigger)
    {
        //Set Distance value to pending
        me->m_distance->m_state = US_FIRING;
        
        trigger(1);
        CyDelayUs(10); //Not too elegant, but a 10us delay is acceptable
        trigger(0);
    }
    else
    {
        LOG_E("US_Fire","no pin config - id");
    }
}




/**
 * A improved force polling implementation of the driver
 * \param US_t const* me      : [IN/OUT] The sensor object
 * \param uint32_t time_us    : [IN] The time in us
 * @return RC_SUCCESS
 */
RC_t US_SetDistance_isr(US_t const* me, uint32_t time_us)
{

    uint16_t distance = US__calcDistance(time_us);
    
    me->m_distance->m_state = US_VALID;
    me->m_distance->m_distance = distance;
    
    return RC_SUCCESS;
    
}

/**
 * Translate time into distance
 * \param uint32_t time_us      : [IN] Time in ys
 * \return distance in cm
 */
uint16_t US__calcDistance(uint32_t time_us)
{
    float result = (float)time_us * 17.15 / 1000;
    return (uint16_t)result;
}

/**
 * Reset the software timer for the ultrasnic
 **/
void US_ResetTimer()
{
    US_TickTime = 0;
}

/**
 * Read the software timer for the ultrasnic
 **/
uint32_t US_GetTimer()
{
    return US_TickTime;
}

/**
 * Increment the software timer for the ultrasnic
 **/
void US_TickTimer(uint32_t tick)
{
    US_TickTime += tick;
}
