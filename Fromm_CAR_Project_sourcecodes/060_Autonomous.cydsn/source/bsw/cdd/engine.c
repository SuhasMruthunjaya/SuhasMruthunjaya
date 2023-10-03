/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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
#include "engine.h"
#include "engine_cfg.h"

#include "logging.h"

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

/**
 * Set the speed, using a PID closed loop control logic
 * \param   ENG_t * const me                : [IN/OUT] the engine object
 * \param   sint16_t targetspeed            : [IN] targetspeed in RPM
 * \return RC_SUCCESS or error message
 */
RC_t ENG__controlPID(ENG_t * const me, sint16_t targetspeed);

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

//################################################################ Public functions


/**
 * Initialise the engine peripherals, using the configured drivers
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \return RC_SUCCESS or driver error code
 */
RC_t ENG_init(ENG_t const* me)
{
    return me->m_config->m_init();
}

/**
 * Set the speed, using the selected control mode
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \param   sint16_t rpm                    : [IN] targetspeed in RPM
 * \param   ENG_mode_t mode                 : [IN] controller mode, e.g. closed or open loop
 * \return RC_SUCCESS or error message
 */
RC_t ENG_setSpeed(ENG_t * const me, sint16_t rpm, ENG_mode_t mode)
{
        RC_t result = RC_ERROR;
    
    switch (mode) 
    {
        case ENG_MODE_TEST  : result =  me->m_config->m_pwm(rpm); break;
        case ENG_MODE_PID   : result =  ENG__controlPID(me, rpm); break;
        
        default : result = RC_ERROR_BAD_PARAM; break;
    }
    
    return result;
    
}

/**
 * Stop the engine
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \return RC_SUCCESS or error message
 */
RC_t ENG_stop(ENG_t * const me)
{
        me->m_config->m_pwm(0);
}

/**
 * Read the speed from the local variable. 
 * This function requires a cyclic call of ENG_updateDecoder
 * \param   ENG_t const* me                 : [IN] the engine object
 * \param   sint16_t *const speed           : [OUT] the wheel speed in RPM
 * \return RC_SUCCESS or error message
 */
RC_t ENG_getSpeed(ENG_t const * const me, sint16_t *const speed)
{
    *speed = me->m_rpm;
    
    return RC_SUCCESS;
}

/**
 * Update the decoder value 
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \param   uint16_t ticktime               : [IN] cyclic ticktime in MS
 * \return RC_SUCCESS or error message
 */
RC_t ENG_updateDecoder(ENG_t * const me, uint16_t ticktime)
{
    //Get decoder value
    sint32_t decoder = 0;
    RC_t result =  me->m_config->m_decoder(&decoder);
    
    //Store ticktime for control logic
    me->m_ticktime = ticktime;
    
    if (RC_SUCCESS == result)
    {
        //Calculate RPM based on the values
        me->m_rpm = ((float32_t)decoder / (me->m_config->m_gearboxRatio * me->m_config->m_pulsesPerRotation) * 60 * 1000 / ticktime);
    }
    else
    {
        // What is a safe value? A standstill could make the control loop "escalate", because it increases the power due to the PI characteristics
        // But a very high "wrong" speed could also cause problems.
        // The user HAS to check the return value and an inconsistent controller has to be secured using a safety function,
        // Checking the estimated value against the current value. I.e. a too high I factor could force an engine stop.
        me->m_rpm = 0;
    }
    
    return result;
}

//################################################################ Local functions

/**
 * Set the speed, using a PID closed loop control logic
 * \param   ENG_t * const me                : [IN/OUT] the engine object
 * \param   sint16_t rpm                    : [IN] targetspeed in RPM
 * \return RC_SUCCESS or error message
 */
RC_t ENG__controlPID(ENG_t * const me, sint16_t targetspeed)
{
    
    sint16_t measuredspeed = 0;
    sint32_t controlspeed = 0;
    
    float32_t proportionalError = 0;
    float32_t integralError = 0;
    float32_t differentialError = 0;
    
    uint16_t ticktime = 0;
    
    RC_t result = RC_SUCCESS;
    
    //Check for a rough plausibility of the targetspeed
    //Still it will depend on battery voltage etc if this value can be reached
    //As a consequence, the error value may be overwritten
    if (targetspeed > me->m_config->m_maxRpm)
    {
        targetspeed = me->m_config->m_maxRpm;
        result = RC_ERROR_BAD_PARAM;
    }
    
    if (targetspeed < -me->m_config->m_maxRpm)
    {
        targetspeed = -me->m_config->m_maxRpm;
        result = RC_ERROR_BAD_PARAM;
    }

    //Limit low speed as controller tends to overreact 
    if (abs(targetspeed) < me->m_config->m_minRpm) 
    {
        targetspeed = 0;
        result = RC_ERROR_BAD_PARAM;
    }

    
    //Get the current speed - Important - cyclic call to updateCounter is required elsewhere
    result = ENG_getSpeed(me, &measuredspeed);
    if (RC_SUCCESS != result)  return result;
    
    //Check if ticktime is updated, i.e. the driver was called at least once
    ticktime = me->m_ticktime;
    if (0 == ticktime) return RC_ERROR_INVALID_STATE;
    
    
    //Calculate proportional, integral and differential errors
    proportionalError = targetspeed - measuredspeed;
    
    integralError = me->m_I_error + ((proportionalError * me->m_ticktime) / 1000);       
    me->m_I_error = integralError;
    
    differentialError = (float32_t)(proportionalError - me->m_D_error) * (1000/me->m_ticktime);
    me->m_D_error = proportionalError;

    //Limit I-part and report error
    //This problem e.g. can be caused if the user tries to reach a targetspeed which is not reachable (engine config, battery voltage,...
    float32_t maxIError = (float32_t)me->m_config->m_maxPwm / me->m_config->m_Ki;
    if (me->m_I_error < -maxIError) 
    {
        me->m_I_error = -maxIError; 
        result = RC_ERROR_OVERRUN;
    }
    if (me->m_I_error < -maxIError) 
    {
        me->m_I_error = -maxIError; 
        result = RC_ERROR_OVERRUN;
    }
    
    //Todo: Limit D-part
    //Hack:
    //me->m_D_error = 0;
    
    //Calculate new controlspeed
    float32_t controlspeed_f = (me->m_config->m_Kp * proportionalError + me->m_config->m_Ki * me->m_I_error + me->m_config->m_Kd * me->m_D_error);

    //LOG_I("ENG_PID","T=%d, M=%d, C=%d, eP=%d, eI=%d, eD=%d", targetspeed, measuredspeed, (int)controlspeed_f, (int)proportionalError, (int)me->m_I_error, (int)me->m_D_error);
    //LOG_I("ENG_PID","KP=%d, KI=%d, KD=%d", (int)me->m_config->m_Kp, (int)me->m_config->m_Ki, (int)me->m_config->m_Kd);
    //LOG_I("ENG_PID","KP*eI=%d, KI*eI=%d, KD*eD=%d", (int)(me->m_config->m_Kp * proportionalError), (int)(me->m_config->m_Ki  * me->m_I_error), (int)(me->m_config->m_Kd * me->m_D_error));

    
    //Check overrun
    if (controlspeed_f > me->m_config->m_maxPwm) 
    {
        controlspeed = me->m_config->m_maxPwm;
        result = RC_ERROR_RANGE;
    }else if (controlspeed < -me->m_config->m_maxPwm) 
    {
        controlspeed = -me->m_config->m_maxPwm;
        result = RC_ERROR_RANGE;
    }
    else
    {
        //all ok
        controlspeed = (sint16_t) controlspeed_f;
    }
    
    
    //Avoid beebing
    if (abs(controlspeed) < me->m_config->m_holdPwm || targetspeed == 0) 
    {
        //me->m_I_error = 0;
        controlspeed = 0;
    }
    //LOG_I("ENG_PID","Final PWM: %d",controlspeed);
    //LOG_I("ENG_PID","T=%d, M=%d, C=%d", targetspeed, measuredspeed,  controlspeed);
    

    //Returnvalue deliberately ignored, as the result value up to here contains a more relevant value
    me->m_config->m_pwm((sint16_t)controlspeed);

    return result;
}

/**
 * Read the current I error - indicator for a blocking engine
 * \param   ENG_t const* me                 : [IN/OUT] the engine object
 * \param   float* err_i                    : [out] The current integral error
 * \return RC_SUCCESS or error message
 */
RC_t ENG_readError_I(ENG_t *const me, float* err_i)
{
    *err_i = me->m_I_error;
}

