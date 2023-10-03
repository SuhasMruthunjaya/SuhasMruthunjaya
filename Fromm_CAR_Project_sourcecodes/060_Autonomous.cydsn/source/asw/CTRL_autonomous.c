/**
* \file CTRL_autonomous.c
* \author P. Fromm
* \date 4.6.21
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

#include "CTRL_autonomous.h"
#include "logging.h"

#include "sp_common.h"
#include "ultrasonic_type.h"
#include "carconfig.h"

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
 * Autonomous driving
 * Will read in ultrasonic values and calculate driving parameters
 */
void CTRL_obstacleAvoidance_run()
{
        
    SC_ULTRASONICARRAY_data_t us = RTE_SC_ULTRASONICARRAY_get(&SO_ULTRASONIC_signal);
    SC_CARSPEED_data_t targetspeed = SC_CARSPEED_INIT_DATA;
    
    //We will try to drive forward until we detect an obstacle
    //Then we check if left or right is better by checking the side sensors
    //Problem - this very simply approach will make the car get stuck in corners...
    
    const uint16_t drive_distance = 60;
    
    if (us.m_distance_front.m_distance > drive_distance)
    {
        targetspeed.m_vy = CONFIG_CAR_MAXSPEED / 2;
        targetspeed.m_vphi = 0;
    }
    else if (us.m_distance_right.m_distance > drive_distance)
    {
        targetspeed.m_vy = 0;
        targetspeed.m_vphi = -CONFIG_CAR_MAXROTATION;
    }
    else if (us.m_distance_left.m_distance > drive_distance)
    {
        targetspeed.m_vy = 0;
        targetspeed.m_vphi = CONFIG_CAR_MAXROTATION;
    }
    else if (us.m_distance_rear.m_distance > drive_distance)
    {
        targetspeed.m_vy = -CONFIG_CAR_MAXSPEED / 2;
        targetspeed.m_vphi = 0;
    }
    else
    {
        //give up
        targetspeed.m_vy = 0;
        targetspeed.m_vphi = 0;
    }

    //Send calculated speed to RTE
    RTE_SC_CARSPEED_set(&SO_TARGETSPEED_signal, targetspeed);

}

