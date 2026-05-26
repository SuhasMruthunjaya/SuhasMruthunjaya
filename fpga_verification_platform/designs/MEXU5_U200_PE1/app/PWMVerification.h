/*
 * PWMVerification.h
 *
 *  Created on: 15.09.2025
 *      Author: SESA807379
 */

#ifndef SRC_PWMVERIFICATION_H_
#define SRC_PWMVERIFICATION_H_

#include "axi_reg.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "logFile.h"
#include "platform.h"
#include "xil_printf.h"
#include "xuartps.h"
#include "xil_io.h"
#include "dsp/transform_functions.h"


void pwm_decode(u32 dec_number, float32_t* pwm_frequency, float32_t* pwm_duty_cycle);

void pwm_capture();

float32_t calc_freq(u16 pwm_cycle);

float32_t calc_dutyCycle(u16 duty_cycle, u16 pwm_cycle);

void pwm_read_axi(u32* phase_UH,
u32* phase_UL,
u32* phase_VH,
u32* phase_VL,
u32* phase_WH,
u32* phase_WL,
u32* phase_U_deadtime_count,
u32* phase_V_deadtime_count,
u32* phase_W_deadtime_count);

#endif /* SRC_PWMVERIFICATION_H_ */
