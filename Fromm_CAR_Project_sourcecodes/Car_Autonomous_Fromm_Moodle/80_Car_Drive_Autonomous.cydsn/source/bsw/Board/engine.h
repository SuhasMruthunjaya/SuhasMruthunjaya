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


 
#ifndef ENGINE_H
#define ENGINE_H

#include "global.h"
#include "engine_type.h"
#include "engine_cfg.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/



// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class ENGINE
{
public:
#endif /* Together */


/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Initialises the engine
 * \return RC_SUCCESS
 */
RC_t ENG_Init();

/**
 * Set's the engine speed PWM signal
 * \param ENG_id_t id       : IN - The engine identifier (use ENG_ALL) for all engines simultaniously
 * \param sint16_t dutycycle: IN - The PWM duty cycle in [0.01 % duty cycle] -10000...10000
 * \return RC_SUCCESS
 */
RC_t ENG_SetPWM(ENG_id_t id, sint16_t dutycycle);

/**
 * Read the PWM duty cycle
 * \param ENG_id_t id        : IN - The engine identifier (use ENG_ALL) for all engines simultaniously
 * \param sint16_t* dutycycle: OUT - The PWM duty cycle in [0.01 % duty cycle] -10000...10000
 * \return RC_SUCCESS
 */
RC_t ENG_GetPWM(ENG_id_t id, sint16_t* dutycycle);

/**
 * Set's the engine speed as [RPM] using a callibration curve and no-load
 * \param ENG_id_t id       : IN - The engine identifier (use ENG_ALL) for all engines simultaniously
 * \param sint16_t targetspeed : IN - The engine targetspeed [RPM]
 * \param sint16_t controlspeed : OUT - The engine control speed [% duty cycle]
 * \return RC_SUCCESS
 */
RC_t ENG_SetEngineOpenLoop(ENG_id_t id, sint16_t targetspeed, sint16_t* controlspeed);

/**
 * Set's the engine speed as [RPM] using a P-Controller
 * \param ENG_id_t id       : IN - The engine identifier (use ENG_ALL) for all engines simultaniously
 * \param uint16_t ticktime : IN - The ticktime in [ms]
 * \param sint16_t targetspeed : IN - The engine targetspeed [RPM]
 * \param sint16_t measuredspeed : OUT - The engine measured speed [RPM]
 * \param sint16_t controlspeed : OUT - The engine control speed [% duty cycle]
 * \return RC_SUCCESS
 */
RC_t ENG_SetEngineClosedLoopPID(ENG_id_t id, uint16_t ticktime, sint16_t targetspeed, sint16_t* measuredspeed, sint16_t* controlspeed);

/**
 * Get's the engine speed from the decoder
 * \param ENG_id_t id       : IN - The engine identifier (use ENG_ALL) for all engines simultaniously
 * \param uint16_t ticktime : IN - The ticktime in [ms]
 * \param sint16_t speed    : OUT - The engine speed -max...max [rpm]
 * \return RC_SUCCESS
 */
RC_t ENG_GetSpeed(ENG_id_t id, uint16_t ticktime, sint16_t *const currentSpeed);

/**
 * Reset the internal decoder values
 * \param ENG_id_t id       : IN - The engine identifier (use ENG_ALL) for all engines simultaniously
 * \return RC_SUCCESS
 */
RC_t ENG_ResetDecoder(ENG_id_t id);

/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER

};
#endif /* Together */

#endif /* ENGINE_H */
