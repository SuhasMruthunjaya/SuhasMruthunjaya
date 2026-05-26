/**
* \file engine.c
* \author P. Fromm
* \date 11.1.20
*
* \brief Simple Engine Driver
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
#include "project.h"
#include "engine.h"
#include "engine_cfg.h"


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


static volatile sint32_t ENGINE_decoder = 0;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Initialises the engine
 * \return RC_SUCCESS
 */
RC_t ENG_Init()
{
    ENGINE_PWM_Start();
    ENGINE_PWM_WriteCompare(0);
    
    ENGINE_DECODER_Start();
    
    ENG_ResetDecoder();
    
}

/**
 * Get's the engine speed from the decoder
 * \param uint16_t ticktime : IN - The ticktime in [ms]
 * \param sint16_t speed    : OUT - The engine speed -100...100
 * \return RC_SUCCESS
 */
RC_t ENG_GetSpeed(uint16_t ticktime, sint16_t *const currentSpeed)
{
    sint32_t currentDecoder = ENGINE_DECODER_GetCounter() * ENG_DECODER_DIR;
    sint32_t deltaDecoder = currentDecoder - ENGINE_decoder;
    ENGINE_decoder = currentDecoder;
    
    //*currentSpeed = currentDecoder;
    *currentSpeed = (sint16_t)((deltaDecoder * 60000)/(ticktime * ENG_DECODER_RATIO * ENG_ENGINE_RATIO));
    
    return RC_SUCCESS;
}

/**
 * Reset the internal decoder value
 * \return RC_SUCCESS
 */
RC_t ENG_ResetDecoder()
{
    ENGINE_decoder = 0;
    ENGINE_DECODER_SetCounter(0);
    
    return RC_SUCCESS;
}

/**
 * Set's the engine speed PWM signal
 * \param sint8_t speed : IN - The engine speed -10000...10000
 * \return RC_SUCCESS
 */
RC_t ENG_SetPWM(sint16_t speed)
{
    //Limit range
    if (speed <= -10000) speed = -10000;
    if (speed >= 10000) speed = 10000;
    
    //Set direction 
    if (speed < 0) 
    {
        ENGINE_Direction_Write((uint8_t)ENG_BACKWARD);
        ENGINE_PWM_WriteCompare((uint16_t)-speed);
    }
    else if (speed > 0)
    {
        ENGINE_Direction_Write((uint8_t)ENG_FORWARD);
        ENGINE_PWM_WriteCompare((uint16_t)speed);
    }
    else
    {
        ENGINE_Direction_Write((uint8_t)ENG_STOP);
        ENGINE_PWM_WriteCompare(0);
    }
 
    return RC_SUCCESS;
}

/**
 * Set's the engine speed as [RPM] using a callibration curve and no-load
 * \param sint16_t targetspeed : IN - The engine targetspeed [RPM]
 * \param sint16_t controlspeed : OUT - The engine control speed [RPM]
 * \return RC_SUCCESS
 */
RC_t ENG_SetEngineOpenLoop(sint16_t targetspeed, sint16_t* controlspeed)
{

    sint16_t sgn = 0;
    sint16_t calSpeed = 0;
    
    //Stopped control
    if (targetspeed == 0)
    {
        //To avoid effects of ENG_PWMSTART
        ENG_SetPWM(0);
        *controlspeed = 0;
        
        return RC_SUCCESS;
    }
    
    //Normal control
    if (targetspeed < 0)
    {
        calSpeed = -targetspeed;
        sgn = -1;
    }
    else
    {
        calSpeed = targetspeed;
        sgn = 1;
    }
    
        
    
    //Minimize speed to maxspeed of engine
    if (calSpeed > ENG_MAXRPM) calSpeed = ENG_MAXRPM;
    
    *controlspeed = (sint16_t) (sgn * calSpeed * PWM_MAXDUTY / ENG_MAXRPM);
    
    ENG_SetPWM(*controlspeed);
    
    return RC_SUCCESS;
    
}

/**
 * Set's the engine speed as [RPM] using a P-Controller
 * \param sint16_t targetspeed : IN - The engine targetspeed [RPM]
 * \param sint16_t measuredspeed : OUT - The engine measured speed [RPM]
 * \param sint16_t controlspeed : OUT - The engine control speed [% duty cycle]
 * \return RC_SUCCESS
 */
RC_t ENG_SetEngineClosedLoopP(uint16_t ticktime, sint16_t targetspeed, sint16_t* measuredspeed, sint16_t* controlspeed)
{
    
    sint16_t error = 0;
    static sint32_t integralError = 0;
    static float32_t lastError = 0;
    sint32_t differentialError = 0;
    RC_t result;
    
    //Get the current speed
    result = ENG_GetSpeed(ticktime, measuredspeed);
    if (RC_SUCCESS != result)
    {
        return result;
    }
    
    //Control logic
    error = targetspeed - (*measuredspeed);
    integralError += error;
    differentialError = (float32_t)(error - lastError) * (1000/ticktime);
    lastError = error;
    
    *controlspeed = (sint16_t)(ENG_CONTROL_KP * (float32_t)error + ENG_CONTROL_KI * (float32_t)integralError + ENG_CONTROL_KD * differentialError);
    
    
    result = ENG_SetPWM(*controlspeed);
    if (RC_SUCCESS != result)
    {
        return result;
    }

    return RC_SUCCESS;
    
}
    





