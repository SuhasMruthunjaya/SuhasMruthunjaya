/**
* \file CTRL_manual.c
* \author P. Fromm
* \date 4.6.21
*
* \brief Manual driving functions
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

#include "sp_common.h"
#include "carconfig.h"

#include "CTRL_manual.h"



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
 * Manual driving
 * Will read in joystick values and calculate driving parameters
 */
void CTRL_manual_run()
{
    //Read the joystick data from the RTE
    SC_JOYSTICK_data_t joystick = RTE_SC_JOYSTICK_get(&SO_JOYSTICK_signal);
    
    //Calculate the requested target speed
    SC_CARSPEED_data_t targetSpeed = SC_CARSPEED_INIT_DATA;
    
    //The joystick y-value represents the forward speed
    //The joystick x-value represents the car rotation
    targetSpeed.m_vy = CONFIG_CAR_MAXSPEED * (float)joystick.m_y / CONFIG_CAR_MAXJOYSTICK;
    targetSpeed.m_vphi = CONFIG_CAR_MAXROTATION * (float)joystick.m_x / CONFIG_CAR_MAXJOYSTICK;
    
    //LOG_I("CONTROL_calculateTargetspeed_run","vy = %d vphi = %d", (sint32_t)(targetSpeed.m_vy*100), (sint32_t)(targetSpeed.m_vphi*100));
    
    //Send the target speed requested signal to the limitSpeed runnable
    RTE_SC_CARSPEED_set(&SO_TARGETSPEED_signal, targetSpeed);
}
