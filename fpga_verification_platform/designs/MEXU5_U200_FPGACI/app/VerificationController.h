/*
 * VerificationController.h
 *
 *  Created on: 01.10.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#ifndef SRC_VERIFICATIONCONTROLLER_H_
#define SRC_VERIFICATIONCONTROLLER_H_

#include "dsp/transform_functions.h"
#include "PWMVerification.h"
#include "uart_comm.h"
#include "CurrentSenseVerification.h"
#include "OVCVerification.h"
#include <sleep.h>
#include "ringbuffer.h"
#include "arm_math.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dsp/transform_functions.h"
#include "logFile.h"
#include "string.h"

typedef enum {
	Idle,
	Parse_command,
	CurrentSense_Verification,
	CurrentSense_static,
	CurrentSense_dynamic,
	PWM_Verification,
	PWM_setFrequency,
	PWM_setDutyCycle,
	PWM_Capture,
	OVC_Verification,
	Error
}VerificationType;


extern u32 phase_val;
extern u32 mode_val;
VerificationType servo_verification_fsm();

#endif /* SRC_VERIFICATIONCONTROLLER_H_ */
