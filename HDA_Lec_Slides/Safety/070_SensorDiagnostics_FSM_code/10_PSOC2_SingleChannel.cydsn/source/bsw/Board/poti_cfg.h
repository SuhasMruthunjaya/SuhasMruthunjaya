/**
* \file poti_cfg.h
* \author P. Fromm
* \date 23.2.20
*
* \brief Configuration for the Joystick / Potentiometer
*
* Configuration for reading the Joystick / Potentiometer
*
* \note <notes>

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
*/


 
#ifndef POTI_CFG_H
#define POTI_CFG_H

#include "global.h"

    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

    //Max ADC values for GND and Vdd signal on pin
    #define POTI_MIN_ADC    0
    #define POTI_MAX_ADC    4095

    //Values indicating the valid range (caused by the diagnostic resistors)
    #define POTI_MIN_VALID_ADC    347
    #define POTI_MAX_VALID_ADC    3915





#endif /* POTI_CFG_H */
