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

#include "logging.h"

#include <math.h>

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


static volatile sint32_t ENGINE_decoder[ENG_ALL] = {0};

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
    
    ENG_ResetDecoder(ENG_ALL);
    
}

/**
 * Get's the engine speed from the decoder
 * \param uint16_t ticktime : IN - The ticktime in [ms]
 * \param sint16_t speed    : OUT - The engine speed in RPM 
 * \return RC_SUCCESS
 */
RC_t ENG_GetSpeed(ENG_id_t id, uint16_t ticktime, sint16_t *const currentSpeed)
{
    sint32_t currentDecoder = 0;
    switch (id)
    {
        case ENG_1 : currentDecoder = ENGINE_DECODER_GetCounter(); break;
        default: break;
    }
    

   
    //Correct sign bit if needed
    currentDecoder *= ENG_getDecoderOrientation(id);
        
    sint32_t deltaDecoder = currentDecoder - ENGINE_decoder[id];
    ENGINE_decoder[id] = currentDecoder;
    
    //Debug story
    //DET_Toggle();
    //LOG_I("ENG_GetSpeed"," decoder = %d delta = %d Tick = %d",currentDecoder, deltaDecoder, ticktime);
    
    //Ticktime in [ms]. CurrentSpeed in [rpm]
    *currentSpeed = (sint16_t)((deltaDecoder * 60000)/(ticktime * ENG_DECODER_RATIO * ENG_ENGINE_RATIO));
    
    return RC_SUCCESS;
}

/**
 * Reset the internal decoder value
 * \return RC_SUCCESS
 */
RC_t ENG_ResetDecoder(ENG_id_t id)
{

    if (ENG_ALL == id || ENG_1 == id)
    {
        ENGINE_decoder[ENG_1] = 0;
        ENGINE_DECODER_SetCounter(0);
    }
    
    return RC_SUCCESS;
}

/**
 * Set's the engine speed PWM signal
 * \param sint16_t speed : IN - The engine speed -10000...10000
 * \return RC_SUCCESS
 */
RC_t ENG_SetPWM(ENG_id_t id, sint16_t speed)
{
    //Scale speed direction based on engine mounting
    speed *=  ENG_getEngineOrientation(id);
    
    //Limit range
    if (speed <= -ENG_PWM_MAXDUTY) speed = -ENG_PWM_MAXDUTY;
    if (speed >= ENG_PWM_MAXDUTY) speed = ENG_PWM_MAXDUTY;
    
    //Set direction and speed register values
    ENG_direction_t dir = ENG_STOP;
    uint16_t pwm = 0;
    
    if (speed < 0) 
    {
        dir = ENG_BACKWARD;
        pwm = (uint16_t)-speed;
    }
    else if (speed > 0)
    {
        dir = ENG_FORWARD;
        pwm = (uint16_t)speed;
    }
    
    switch (id) {
        case ENG_1:
            ENGINE_Direction_Write((uint8_t)dir);
            ENGINE_PWM_WriteCompare(pwm);
            break;
        case ENG_ALL:
            //Todo Add all calls
        default: break;
    }

    
    return RC_SUCCESS;
}


/**
 * Read the PWM duty cycle
 * \param ENG_id_t id        : IN - The engine identifier (use ENG_ALL) for all engines simultaniously
 * \param sint16_t* dutycycle: OUT - The PWM duty cycle in [0.01 % duty cycle] -10000...10000
 * \return RC_SUCCESS
 */
RC_t ENG_GetPWM(ENG_id_t id, sint16_t* dutycycle)
{
    sint16_t pwm = 0;
    ENG_direction_t dir = ENG_STOP;
    
    //Read the value from the register
    switch (id) {
        case ENG_1:
            dir = (ENG_direction_t)ENGINE_Direction_Read();
            pwm = ENGINE_PWM_ReadCompare();
            break;
        case ENG_ALL:
            //Does not make sense in this case
        default: break;
    }
        
    //Check the speed direction setting
    if (ENG_BACKWARD == dir)
    {
        pwm *= -1;
    }
        
    //Correct the speed sign considering the engine orientation
    pwm *= ENG_getEngineOrientation(id);
    
    *dutycycle = pwm;
}
/**
 * Set's the engine speed as [RPM] using a callibration curve and no-load
 * \param sint16_t targetspeed : IN - The engine targetspeed [RPM]
 * \param sint16_t controlspeed : OUT - The engine control speed [RPM] / for information purposes only
 * \return RC_SUCCESS
 */
RC_t ENG_SetEngineOpenLoop(ENG_id_t id, sint16_t targetspeed, sint16_t* controlspeed)
{

    
    //Stopped control
    if (targetspeed == 0)
    {
        //To avoid effects of ENG_PWMSTART
        ENG_SetPWM(id, 0);
        *controlspeed = 0;
        
        return RC_SUCCESS;
    }

    uint16_t index = 0;    
    uint16_t size = 0;
    ENG_calibration_t* curve;
    sint16_t calSpeed = 0;
    
    //Normal control
    if (targetspeed < 0)
    {
        size = ENG_cal_backward_size;
        curve = ENG_cal_backward;
    }
    else
    {
        size = ENG_cal_forward_size;
        curve = ENG_cal_forward;
    }
    
    for (index = 0; index < size + 1; index++)
    {
        if ( (abs(targetspeed) >= abs(curve[index].m_targetspeed)) && 
             (abs(targetspeed) < abs(curve[index+1].m_targetspeed)) )
        {
            //Found the correct 
            break;
        }
    }
    
    if (index >= size - 1)
    {
        //Special handling for last element in list
        calSpeed = curve[size - 1].m_controlspeed;
    }
    else
    {
        //Linear approximation
        sint16_t t1, c1, t2, c2 = 0;
        t1 = curve[index].m_targetspeed;
        c1 = curve[index].m_controlspeed;
        t2 = curve[index+1].m_targetspeed;
        c2 = curve[index+1].m_controlspeed;
        
        calSpeed = c1 + ((targetspeed - t1) * (c2-c1) / (t2-t1));
        //calSpeed = c1;
    }
        
    
    //Minimize speed to maxspeed of engine
    //SHould never happen, but who knows
    if (calSpeed > ENG_PWM_MAXDUTY) calSpeed = ENG_PWM_MAXDUTY;
    if (calSpeed < -ENG_PWM_MAXDUTY) calSpeed = -ENG_PWM_MAXDUTY;
    
    *controlspeed = calSpeed;
    
    //ENG_SetPWM(id, calSpeed);
    
    return RC_SUCCESS;
    
}


/**
 * Set's the engine speed as [RPM] using a P-Controller
 * \param sint16_t targetspeed : IN - The engine targetspeed [RPM]
 * \param sint16_t measuredspeed : IN - The engine measured speed [RPM]
 * \param sint16_t controlspeed : OUT - The engine control speed [% duty cycle]
 * \return RC_SUCCESS
 */
RC_t ENG_SetEngineClosedLoopPID(ENG_id_t id, uint16_t ticktime, sint16_t targetspeed, sint16_t measuredspeed, sint16_t* controlspeed)
{
    
    float32_t error = 0;
    static float32_t integralError = 0;
    static float32_t lastError = 0;
    float32_t differentialError = 0;
    RC_t result;
    
    
    //Control logic
    error = targetspeed - measuredspeed;
    integralError += ((error * ticktime) / 1000);       
    differentialError = (float32_t)(error - lastError) * (1000/ticktime);
    lastError = error;


    sint16_t calSpeed = 0;
    calSpeed = (sint16_t)(ENG_CONTROL_KP * error + ENG_CONTROL_KI * integralError + ENG_CONTROL_KD * differentialError);

    LOG_I("ENG_SetEngineClosedLoopPID","T: %d M: %d C: %d, EP: %d EI: %d", targetspeed, measuredspeed, calSpeed, (sint32_t)error, (sint32_t)integralError);
    
    if (calSpeed > ENG_PWM_MAXDUTY) calSpeed = ENG_PWM_MAXDUTY;
    if (calSpeed < -ENG_PWM_MAXDUTY) calSpeed = -ENG_PWM_MAXDUTY;
    if (abs(calSpeed) < ENG_PWMMIN) calSpeed = 0;

    *controlspeed = calSpeed;
    


    return RC_SUCCESS;
    
}
    





