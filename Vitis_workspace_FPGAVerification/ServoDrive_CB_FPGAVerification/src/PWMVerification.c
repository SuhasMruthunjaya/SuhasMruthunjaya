/*
 * PWMVerification.c
 *
 *  Created on: 15.09.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#include "PWMVerification.h"
#include "CurrentSenseVerification.h"

//u32 phase_UH = 0;
//u32 phase_UL = 0;
//u32 phase_VH = 0;
//u32 phase_VL = 0;
//u32 phase_WH = 0;
//u32 phase_WL = 0;
//u32 phase_U_deadtime_count = 0;
//u32 phase_V_deadtime_count = 0;
//u32 phase_W_deadtime_count = 0;

void pwm_decode(u32 dec_number, float32_t* pwm_frequency, float32_t* pwm_duty_cycle)
{
	u16 pwmfreq = dec_number & 0xffff;
	u16 pwmdutyCyl = (dec_number >> 16) & 0xffff;

	*pwm_frequency = calc_freq(pwmfreq);
	*pwm_duty_cycle = calc_dutyCycle(pwmdutyCyl, pwmfreq);

}

void deadtime_decode(u32 dec_number, float32_t* pwm_deadtime_HL, float32_t* pwm_deadtime_LH)
{
	u16 Highlow_DT = dec_number & 0xffff;
	u16 lowHigh_DT = (dec_number >> 16) & 0xffff;

	xil_printf("HighlowDT: %d, ", Highlow_DT);
	xil_printf("lowHigh_DT: %d\n", lowHigh_DT);

	*pwm_deadtime_HL = ((float32_t)Highlow_DT/(float32_t)192000000.0f) * 1000000;
	*pwm_deadtime_LH = ((float32_t)lowHigh_DT/(float32_t)192000000.0f) * 1000000;
}

void pwm_capture()
{
	float32_t pwm_frequency_uh = 0.0f , pwm_duty_cycle_uh = 0.0f, pwm_frequency_vh = 0.0f,pwm_duty_cycle_vh = 0.0f;
	float32_t pwm_frequency_wh = 0.0f , pwm_duty_cycle_wh = 0.0f, pwm_frequency_wl = 0.0f, pwm_duty_cycle_wl = 0.0f;
	float32_t pwm_frequency_ul = 0.0f , pwm_duty_cycle_ul = 0.0f, pwm_frequency_vl = 0.0f, pwm_duty_cycle_vl = 0.0f;
	float32_t pwm_deadtime_U_HL = 0.0f, pwm_deadtime_U_LH = 0.0f, pwm_deadtime_V_HL = 0.0f, pwm_deadtime_V_LH = 0.0f;
	float32_t pwm_deadtime_W_HL = 0.0f, pwm_deadtime_W_LH = 0.0f;

	u32 phase_UH = 0;
	u32 phase_UL = 0;
	u32 phase_VH = 0;
	u32 phase_VL = 0;
	u32 phase_WH = 0;
	u32 phase_WL = 0;
	u32 phase_U_deadtime_count = 0;
	u32 phase_V_deadtime_count = 0;
	u32 phase_W_deadtime_count = 0;

	char buffer[10000], freq_uh[10], dc_uh[10],dt_uh[10], freq_ul[10], dc_ul[10], dt_ul[10], freq_vh[10], dc_vh[10], dt_vh[10];
	char freq_vl[10], dc_vl[10], dt_vl[10], freq_wh[10], dc_wh[10], dt_wh[10], freq_wl[10], dc_wl[10], dt_wl[10];
	buffer[0] = '\0';

//	xil_printf("before AXI read");

	pwm_read_axi(&phase_UH, &phase_UL, &phase_VH, &phase_VL, &phase_WH, &phase_WL, &phase_U_deadtime_count, &phase_V_deadtime_count, &phase_W_deadtime_count);
	deadtime_decode(phase_U_deadtime_count, &pwm_deadtime_U_HL, &pwm_deadtime_U_LH);
	deadtime_decode(phase_V_deadtime_count, &pwm_deadtime_V_HL, &pwm_deadtime_V_LH);
	deadtime_decode(phase_W_deadtime_count, &pwm_deadtime_W_HL, &pwm_deadtime_W_LH);

	pwm_decode(phase_UH , &pwm_frequency_uh, &pwm_duty_cycle_uh);
	strcat(buffer, "PWM frequency phase U High: ");
	float2string(pwm_frequency_uh, freq_uh, 3);
	strcat(buffer, freq_uh);
	strcat(buffer, "Hz and duty cycle: ");
	float2string(pwm_duty_cycle_uh, dc_uh, 3);
	strcat(buffer, dc_uh);
	strcat(buffer, "% deadtime: ");
	float2string(pwm_deadtime_U_HL, dt_uh, 3);
	strcat(buffer, dt_uh);

	pwm_decode(phase_UL , &pwm_frequency_ul, &pwm_duty_cycle_ul);
	strcat(buffer,"us\n PWM frequency phase U Low: ");
	float2string(pwm_frequency_ul, freq_ul, 3);
	strcat(buffer, freq_ul);
	strcat(buffer, "Hz and duty cycle: ");
	float2string(pwm_duty_cycle_ul, dc_ul, 3);
	strcat(buffer, dc_ul);
	strcat(buffer, "% deadtime: ");
	float2string(pwm_deadtime_U_LH, dt_ul, 3);
	strcat(buffer, dt_ul);

	pwm_decode(phase_VH , &pwm_frequency_vh, &pwm_duty_cycle_vh);
	strcat(buffer,"us\n PWM frequency phase V High: ");
	float2string(pwm_frequency_vh, freq_vh, 3);
	strcat(buffer, freq_vh);
	strcat(buffer, "Hz and duty cycle: ");
	float2string(pwm_duty_cycle_vh, dc_vh, 3);
	strcat(buffer, dc_vh);
	strcat(buffer, "% deadtime: ");
	float2string(pwm_deadtime_V_HL, dt_vh, 3);
	strcat(buffer, dt_vh);

	pwm_decode(phase_VL , &pwm_frequency_vl, &pwm_duty_cycle_vl);
	strcat(buffer,"us\n PWM frequency phase V Low: ");
	float2string(pwm_frequency_vl, freq_vl, 3);
	strcat(buffer, freq_vl);
	strcat(buffer, "Hz and duty cycle: ");
	float2string(pwm_duty_cycle_vl, dc_vl, 3);
	strcat(buffer, dc_vl);
	strcat(buffer, "% deadtime: ");
	float2string(pwm_deadtime_V_LH, dt_vl, 3);
	strcat(buffer, dt_vl);

	pwm_decode(phase_WH , &pwm_frequency_wh, &pwm_duty_cycle_wh);
	strcat(buffer,"us\n PWM frequency phase W High: ");
	float2string(pwm_frequency_wh, freq_wh, 3);
	strcat(buffer, freq_wh);
	strcat(buffer, "Hz and duty cycle: ");
	float2string(pwm_duty_cycle_wh, dc_wh, 3);
	strcat(buffer, dc_wh);
	strcat(buffer, "% deadtime: ");
	float2string(pwm_deadtime_W_HL, dt_wh, 3);
	strcat(buffer, dt_wh);

	pwm_decode(phase_WL , &pwm_frequency_wl, &pwm_duty_cycle_wl);
	strcat(buffer,"us\n PWM frequency phase W low: ");
	float2string(pwm_frequency_wl, freq_wl, 3);
	strcat(buffer, freq_wl);
	strcat(buffer, "Hz and duty cycle: ");
	float2string(pwm_duty_cycle_wl, dc_wl, 3);
	strcat(buffer, dc_wl);
	strcat(buffer, "% deadtime: ");
	float2string(pwm_deadtime_W_LH, dt_wl, 3);
	strcat(buffer, dt_wl);

	strcat(buffer, "us\n");
	xil_printf("%s",buffer);

}

float32_t calc_freq(u16 pwm_cycle)
{
	if (pwm_cycle != 0)
		return (float32_t)192000000.0f/(float32_t)pwm_cycle;
	else
		return 0.0f;
}

float32_t calc_dutyCycle(u16 duty_cycle, u16 pwm_cycle)
{
//	printf("duty_cycle: %d\n", duty_cycle);
//	printf("pwm_cycle: %d\n", pwm_cycle);
	if (pwm_cycle != 0)
		return ((float32_t)duty_cycle/(float32_t)pwm_cycle) * 100.0f;
	else
		return 0.0f;
}

void pwm_read_axi(u32* phase_UH,
u32* phase_UL,
u32* phase_VH,
u32* phase_VL,
u32* phase_WH,
u32* phase_WL,
u32* phase_U_deadtime_count,
u32* phase_V_deadtime_count,
u32* phase_W_deadtime_count)
{
	*phase_UH = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_UH_FREQUENCY_DUTYCYCLE);

	*phase_UL = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_UL_FREQUENCY_DUTYCYCLE);

	*phase_VH = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_VH_FREQUENCY_DUTYCYCLE);

	*phase_VL = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_VL_FREQUENCY_DUTYCYCLE);

	*phase_WH = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_WH_FREQUENCY_DUTYCYCLE);

	*phase_WL = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_WL_FREQUENCY_DUTYCYCLE);

	*phase_U_deadtime_count = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_U_DEADTIME);

	*phase_V_deadtime_count = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_V_DEADTIME);

	*phase_W_deadtime_count = Xil_In32(PWMCAPTURE_AXI_IP_BASE_ADDR + PHASE_W_DEADTIME);

//	xil_printf("AXI reg read");

}
