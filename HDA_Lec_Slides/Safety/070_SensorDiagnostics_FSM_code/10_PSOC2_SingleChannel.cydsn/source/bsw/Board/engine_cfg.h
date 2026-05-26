/**
* \file engine.h
* \author P. Fromm
* \date 11.01.20
*
* \brief A simple driver for the JGA25-370 DC engine
*
* The driver creates two PWM signals for the H-bridge (L298) and reads the decoder values
*
* \note <notes>
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 1.0; 2020.01.11; P. Fromm
*            - Initial release
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
    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

    //Engine driver parameters
    typedef enum {ENG_STOP = 0x00, ENG_BACKWARD = 0x01, ENG_FORWARD = 0x02} ENG_direction_t;
    

    
    //Decoder parameters
    #define ENG_ENGINE_RATIO    34
    #define ENG_DECODER_RATIO   10
    #define ENG_DECODER_DIR     -1      //Direction parameter for the decoder
    
    //Engine open loop parameters
    #define ENG_MAXRPM          195
    #define ENG_PWMSTART        1100    //To overcome the holding torque
    #define PWM_MAXDUTY         10000   //Max duty cycle of the PWM
    
    //Engine control parameters
    #define ENG_CONTROL_KP      5      //KP factor of PID controller ==> 10000 / 195 = approx. 50 
    #define ENG_CONTROL_KI      2      //KI factor of PID controller
    #define ENG_CONTROL_KD      0      //KD factor of PID controller
   

#endif /* ENGINE_H */
