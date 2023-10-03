/**
* \file engine_cfg.c
* \author P. Fromm
* \date 16.05.21
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
#include <project.h>
#include "math.h"

#include "engine_cfg.h"



/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

//Engine mechanics
#define ENG_GEARBOX_RATIO   39
#define ENG_PPR             10

//Engine open loop parameters
#define ENG_PWM_MAXDUTY     10000   //Max duty cycle of the PWM
#define ENG_PWMSTART        1100    //To overcome the holding torque

#define ENG_MINRPM          10      //Lowest possiblöe speed due to holding torque

//Engine closed loop parameters
#define ENG_CONTROL_KP      20.0     //KP factor of PID controller ==> 10000 / 200 = approx. 50 
#define ENG_CONTROL_KI      100.0    //KI factor of PID controller
#define ENG_CONTROL_KD      0.0      //KD factor of PID controller


/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/


/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

// Init Wrapper
static RC_t ENG__init_RR();
static RC_t ENG__init_RL();
static RC_t ENG__init_FR();
static RC_t ENG__init_FL();

// Decoder Wrapper
static RC_t ENG__getDecoder_RR(sint32_t* decoder_value);
static RC_t ENG__getDecoder_RL(sint32_t* decoder_value);
static RC_t ENG__getDecoder_FR(sint32_t* decoder_value);
static RC_t ENG__getDecoder_FL(sint32_t* decoder_value);

// PWM Wrapper
static RC_t ENG__setPwm_RR(sint32_t pwm_value);
static RC_t ENG__setPwm_RL(sint32_t pwm_value);
static RC_t ENG__setPwm_FR(sint32_t pwm_value);
static RC_t ENG__setPwm_FL(sint32_t pwm_value);

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/


// Engine configuration records
static const ENG_cfg_t ENG__cfg_RR = {
    ENG__init_RR,
    ENG__getDecoder_RR,
    ENG__setPwm_RR,
    
    ENG_PPR,
    ENG_GEARBOX_RATIO,
    
    ENG_PWM_MAXDUTY,
    ENG_PWMSTART,
    
    ENG_MAXRPM,
    ENG_MINRPM,
    
    ENG_CONTROL_KP,
    ENG_CONTROL_KI,
    ENG_CONTROL_KD,
};
    
static const ENG_cfg_t ENG__cfg_RL = {
    ENG__init_RL,
    ENG__getDecoder_RL,
    ENG__setPwm_RL,
    
    ENG_PPR,
    ENG_GEARBOX_RATIO,
    
    ENG_PWM_MAXDUTY,
    ENG_PWMSTART,
    
    ENG_MAXRPM,
    ENG_MINRPM,
    
    ENG_CONTROL_KP,
    ENG_CONTROL_KI,
    ENG_CONTROL_KD,
};

static const ENG_cfg_t ENG__cfg_FR = {
    ENG__init_FR,
    ENG__getDecoder_FR,
    ENG__setPwm_FR,
    
    ENG_PPR,
    ENG_GEARBOX_RATIO,
    
    ENG_PWM_MAXDUTY,
    ENG_PWMSTART,
    
    ENG_MAXRPM,
    ENG_MINRPM,
    
    ENG_CONTROL_KP,
    ENG_CONTROL_KI,
    ENG_CONTROL_KD,
};

static const ENG_cfg_t ENG__cfg_FL = {
    ENG__init_FL,
    ENG__getDecoder_FL,
    ENG__setPwm_FL,
    
    ENG_PPR,
    ENG_GEARBOX_RATIO,
    
    ENG_PWM_MAXDUTY,
    ENG_PWMSTART,
    
    ENG_MAXRPM,
    ENG_MINRPM,
    
    ENG_CONTROL_KP,
    ENG_CONTROL_KI,
    ENG_CONTROL_KD,
};

 
/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

ENG_t ENG_RR = {
    &ENG__cfg_RR,    //Configuration
    0,               //Current Decoder value
    0,               //I error (PID controller)
    0,               //D error (PID controller)
    0,               //last ticktime (PID controller)
};

ENG_t ENG_RL = {
    &ENG__cfg_RL,    //Configuration
    0,               //Current Decoder value
    0,               //I error (PID controller)
    0,               //D error (PID controller)
    0,               //last ticktime (PID controller)
};

ENG_t ENG_FR = {
    &ENG__cfg_FR,    //Configuration
    0,               //Current Decoder value
    0,               //I error (PID controller)
    0,               //D error (PID controller)
    0,               //last ticktime (PID controller)
};

ENG_t ENG_FL = {
    &ENG__cfg_FL,    //Configuration
    0,               //Current Decoder value
    0,               //I error (PID controller)
    0,               //D error (PID controller)
    0,               //last ticktime (PID controller)
};


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

// Init Wrapper
static RC_t ENG__init_RR()
{
    PWM_RearRight_Start();
    QuadDec_RR_Start();
    
    return RC_SUCCESS;
}

static RC_t ENG__init_RL()
{
    //Todo: A bit hacky, we start PWM twice...Add a flag or check for status
    PWM_RearLeft_Start();
    QuadDec_RL_Start();
    
    return RC_SUCCESS;
}

static RC_t ENG__init_FR()
{
    PWM_FrontRight_Start();
    QuadDec_FR_Start();
    
    return RC_SUCCESS;
}

static RC_t ENG__init_FL()
{
    PWM_FrontLeft_Start();
    QuadDec_FL_Start();
    
    return RC_SUCCESS;
}


// Decoder Wrapper
// We set the counter to 0 after every read operation in order to correct the sign depending on the engine mount
// Doing this, we don't have to do this on the higher driver level and all mechanical aspects are handled here
static RC_t ENG__getDecoder_RR(sint32_t* decoder_value)
{
    *decoder_value = -QuadDec_RR_GetCounter();
    QuadDec_RR_SetCounter(0);
    
    return RC_SUCCESS;
}

static RC_t ENG__getDecoder_RL(sint32_t* decoder_value)
{
    *decoder_value = QuadDec_RL_GetCounter();
    QuadDec_RL_SetCounter(0);
    
    return RC_SUCCESS;

}


static RC_t ENG__getDecoder_FR(sint32_t* decoder_value)
{
    *decoder_value = -QuadDec_FR_GetCounter();
    QuadDec_FR_SetCounter(0);
    
    return RC_SUCCESS;
}


static RC_t ENG__getDecoder_FL(sint32_t* decoder_value)
{
    *decoder_value = QuadDec_FL_GetCounter();
    QuadDec_FL_SetCounter(0);
    
    return RC_SUCCESS;
}


// PWM Wrapper
static RC_t ENG__setPwm_RR(sint32_t pwm_value)
{
    //Calculate Mode Value
    uint8_t new_mode = 0;
    
    //Set mode value considering engine mounting
    //Mode control the direction of the engine
    if (pwm_value < 0) new_mode = 2;
    if (pwm_value > 0) new_mode = 1;

    //Therefore register value for PWM is always positive
    uint16_t new_pwm = (uint16_t)(abs(pwm_value));

    //Write to peripheral driver
    Engine_Mode_RR_Write(new_mode);
    PWM_RearRight_WriteCompare(new_pwm);
}

static RC_t ENG__setPwm_RL(sint32_t pwm_value)
{
    //Calculate Mode Value
    uint8_t new_mode = 0;
    
    //Set mode value considering engine mounting
    //Mode control the direction of the engine
    if (pwm_value < 0) new_mode = 1;
    if (pwm_value > 0) new_mode = 2;

    //Therefore register value for PWM is always positive
    uint16_t new_pwm = (uint16_t)(abs(pwm_value));

    //Write to peripheral driver
    Engine_Mode_RL_Write(new_mode);
    PWM_RearLeft_WriteCompare(new_pwm);

}

static RC_t ENG__setPwm_FR(sint32_t pwm_value)
{
    //Calculate Mode Value
    uint8_t new_mode = 0;
    
    //Set mode value considering engine mounting
    //Mode control the direction of the engine
    if (pwm_value < 0) new_mode = 2;
    if (pwm_value > 0) new_mode = 1;

    //Therefore register value for PWM is always positive
    uint16_t new_pwm = (uint16_t)(abs(pwm_value));

    //Write to peripheral driver
    Engine_Mode_FR_Write(new_mode);
    PWM_FrontRight_WriteCompare(new_pwm);
}

static RC_t ENG__setPwm_FL(sint32_t pwm_value)
{
        //Calculate Mode Value
    uint8_t new_mode = 0;
    
    //Set mode value considering engine mounting
    //Mode control the direction of the engine
    if (pwm_value < 0) new_mode = 1;
    if (pwm_value > 0) new_mode = 2;

    //Therefore register value for PWM is always positive
    uint16_t new_pwm = (uint16_t)(abs(pwm_value));

    //Write to peripheral driver
    Engine_Mode_FL_Write(new_mode);
    PWM_FrontLeft_WriteCompare(new_pwm);
}

