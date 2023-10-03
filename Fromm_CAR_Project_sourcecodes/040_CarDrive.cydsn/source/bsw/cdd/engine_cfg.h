/**
* \file engine_cfg.h
* \author P. Fromm
* \date 16.05.21
*
* \brief Project specific engine configuration including wrapper functions for peripheral access
*
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
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
**/


 
#ifndef ENGINE_CFG_H
#define ENGINE_CFG_H

#include "global.h"
#include "engine_type.h"

    /*
//################# Global defines
    
//Peripherals
#define ENG_MAX_PWM         0xFFFF  //16 bit
    
//Engine mechanics
#define ENG_GEARBOX_RATIO   39
#define ENG_PPR             10

//Engine open loop parameters
#define ENG_MAXRPM          250
#define ENG_PWMSTART        1100    //To overcome the holding torque
#define ENG_PWM_MAXDUTY     10000   //Max duty cycle of the PWM
    
//Engine closed loop parameters
#define ENG_CONTROL_KP      20.0     //KP factor of PID controller ==> 10000 / 200 = approx. 50 
#define ENG_CONTROL_KI      100.0    //KI factor of PID controller
#define ENG_CONTROL_KD      0.0      //KD factor of PID controller
*/
//################# Global Engine Objects 
    
extern ENG_t ENG_RR;    // Rear Right Engine
extern ENG_t ENG_RL;    // Rear Left Engine
extern ENG_t ENG_FR;    // Front Right Engine
extern ENG_t ENG_FL;    // Front Left Engine

#endif /* ENGINE_CFG_H */
