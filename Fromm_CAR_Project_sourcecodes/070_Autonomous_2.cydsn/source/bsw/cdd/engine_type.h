/**
* \file engine_type.h
* \author P. Fromm
* \date 16.05.2021
*
* \brief global engine type definitions
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


 
#ifndef ENGINE_TYPE_H
#define ENGINE_TYPE_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#include "global.h"

//####################### Enumerators
enum e_ENG_mode { 
    ENG_MODE_OL_LI,         /**< \brief Open loop mode using linear approximation */
    ENG_MODE_OL_LL,         /**< \brief Open loop mode using lookup table */
    ENG_MODE_PID,           /**< \brief Closed Loop PID controller */
    ENG_MODE_TEST           /**< \brief Test mode, passing the parameter directly to the PWM register */
};
typedef enum e_ENG_mode ENG_mode_t;
    

    
//####################### Function Pointer
    
/** 
 * Note, that we use wrapper functions to support multichannel peripherals if needed
 **/

/**
 * Function pointer used for init peripheral function
 * \return RC_SUCCESS or error code
 */
typedef RC_t (*INIT_driver)();
    
/**
 * Function pointer used for decoder function. 
 * \param uint32_t* decoder_value   : [OUT] current value of the decoder peripheral
 * \return RC_SUCCESS or error code
 */
typedef RC_t (*DECODER_driver)(sint32_t* decoder_value);

/**
 * Function pointer used for pwm function. 
 * Note, that the function includes any GPIA mode setting
 * depending on the direction
 * \param sint32_t* pwm_value   : [IN] value for the pwm peripheral
 * \return RC_SUCCESS or error code
 */
typedef RC_t (*PWM_driver)(sint32_t pwm_value);

//####################### Object Structures

/**
* \brief Engine configuration parameters
*/
struct sENG_cfg {
    INIT_driver         m_init;                 /**< \brief Pointer to the init function */
    DECODER_driver      m_decoder;              /**< \brief Pointer to the decoder function */
    PWM_driver          m_pwm;                  /**< \brief Pointer to the pwm function */

    uint16_t            m_pulsesPerRotation;    /**< \brief decoder pulses per rotation */
    uint16_t            m_gearboxRatio;         /**< \brief gearbox ratio */
    
    uint16_t            m_maxPwm;               /**< \brief max PWM value for the peripheral */
    uint16_t            m_holdPwm;              /**< \brief holding torque / PWM ration of engine */
    
    sint16_t            m_maxRpm;               /**< \brief max wheel rotation */
    sint16_t            m_minRpm;               /**< \brief min wheel rotation */
    
    float32_t           m_Kp;                   /**< \brief Kp factor of PID control loop */
    float32_t           m_Ki;                   /**< \brief Ki factor of PID control loop */
    float32_t           m_Kd;                   /**< \brief Kd factor of PID control loop */
    
};
typedef struct sENG_cfg ENG_cfg_t;




/**
* \brief The engine object containing the configuration as well as the buffers for the controller logic
*/
struct sENG {
    ENG_cfg_t const*    m_config;           /**< \brief Pointer to engine configuration */
    sint32_t            m_rpm;              /**< \brief Current rpm value */
    float               m_I_error;          /**< \brief integration error from PID controller */
    float               m_D_error;          /**< \brief differential error from PID controller */
    uint16_t            m_ticktime;         /**< \brief last ticktime, written bei updateCounter */
    sint16_t            m_deltaDecoder;     /**< \brief Used for dead reckoning */
};
typedef struct sENG ENG_t;


#endif /* ENGINETYPE_H */
