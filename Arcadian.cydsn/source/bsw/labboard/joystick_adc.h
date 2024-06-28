/**
* \file Joystick
* \author P. Fromm
* \date 29.8.17
*
* \brief File containing attributes and functions of lower level Joystick driver
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


 
#ifndef JOYSTICK_ADC_H
#define JOYSTICK_ADC_H

#include "global.h"

    
/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/



/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/



/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Initialisation of the Joystick
 * @return RC_SUCCESS if all ok
 */
RC_t JOYSTICK_ADC_Init();


/**
 * Read the Joystick position
 * @param sint8_t* x, sint8_t* y - OUT x and y position
 * @return RC_SUCCESS if all ok
 */
RC_t JOYSTICK_ADC_ReadPosition(sint8_t* x, sint8_t* y);


/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/



#endif /* FILE_H */
