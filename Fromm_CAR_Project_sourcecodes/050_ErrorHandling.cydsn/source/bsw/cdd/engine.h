/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
*
* detailed description what the file does
*
* \note <notes>
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


 
#ifndef ENGINE_H
#define ENGINE_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#include "global.h"
#include "engine_cfg.h"


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
 * Initialise the engine peripherals, using the configured drivers
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \return RC_SUCCESS or driver error code
 */
RC_t ENG_init(ENG_t const* me);

/**
 * Set the speed, using the selected control mode
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \param   sint16_t rpm                    : [IN] targetspeed in RPM
 * \param   ENG_mode_t mode                 : [IN] controller mode, e.g. closed or open loop
 * \return RC_SUCCESS or error message
 */
RC_t ENG_setSpeed(ENG_t * const me, sint16_t rpm, ENG_mode_t mode);

/**
 * Stop the engine
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \return RC_SUCCESS or error message
 */
RC_t ENG_stop(ENG_t * const me);

/**
 * Read the speed from the local variable. 
 * This function requires a cyclic call of ENG_updateDecoder
 * \param   ENG_t const* me                 : [IN] the engine object
 * \param   sint16_t *const speed           : [OUT] the wheel speed in RPM
 * \return RC_SUCCESS or error message
 */
RC_t ENG_getSpeed(ENG_t const * const me, sint16_t *const speed);

/**
 * Update the decoder value 
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \param   uint16_t ticktime               : [IN] cyclic ticktime in MS
 * \return RC_SUCCESS or error message
 */
RC_t ENG_updateDecoder(ENG_t *const me, uint16_t ticktime);

/**
 * Read the current I error - indicator for a blocking engine
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \param   float* err_i                    : [out] The current integral error
 * \return RC_SUCCESS or error message
 */
RC_t ENG_readError_I(ENG_t *const me, float* err_i);

/*****************************************************************************/
/* Private stuff, only visible for Together, declared static in cpp - File   */
/*****************************************************************************/


#ifdef TOGETHER

};
#endif /* Together */

#endif /* FILE_H */
