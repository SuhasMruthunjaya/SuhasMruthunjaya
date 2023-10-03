/**
* \file ultrasonic.h
* \author P. Fromm
* \date 2.7.20
*
* \brief Ultrasonic driver
*
* detailed description what the file does
*
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - 0.1; 2.7.2020; P. Fromm
*            - Initial
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


 
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/


#include "global.h"

#include "ultrasonic_type.h"
#include "ultrasonic_cfg.h"    
   

// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class Ultrasonic
{
public:
#endif /* Together */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/


/**
 * Fire a single trigger puls - mainly for testing purposes
 * \param US_t const* me      : [IN/OUT] The sensor object
 * @return RC_SUCCESS
 */
RC_t US_Fire(US_t const* me);


/**
 * ISR function getting the time and calculating the distance
 * \param US_t const* me      : [IN/OUT] The sensor object
 * \param uint32_t time_us    : [IN] The time in us
 * @return RC_SUCCESS
 */
RC_t US_SetDistance_isr(US_t const* me, uint32_t time_us);

/**
 * Reset the software timer for the ultrasnic
 **/
void US_ResetTimer();

/**
 * Increment the software timer for the ultrasnic
 **/
void US_TickTimer(uint32_t tick);

/**
 * Read the software timer for the ultrasnic
 **/
uint32_t US_GetTimer();



/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER



};
#endif /* Together */

#endif /* FILE_H */
