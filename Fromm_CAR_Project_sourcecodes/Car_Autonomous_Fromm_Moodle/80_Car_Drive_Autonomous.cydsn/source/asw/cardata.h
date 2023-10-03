/* ========================================
 *
 * Copyright HDA, 2020
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef CARDATA_H
#define CARDATA_H

#include "engine_cfg.h"
    
#define CAR_MAXSPEED        0.7         /**< \brief in m/s */
#define CAR_MAXROTATION     1           /**< \brief in deg/s */
#define CAR_MAXJOYSTICK     128         /**< \brief in percent */
    
#define K_VY2RPM (ENG_MAXRPM*1.42)      /**< \brief translate m/s into RPM */
#define K_VPHI2RPM ENG_MAXRPM

    
    
#endif

