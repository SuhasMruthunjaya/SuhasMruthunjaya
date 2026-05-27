/*
 * CurrentSenseVerification.h
 *
 *  Created on: 16.07.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#ifndef SRC_CURRENTSENSEVERIFICATION_H_
#define SRC_CURRENTSENSEVERIFICATION_H_

#include "uart_comm.h"
#include "dsp/transform_functions.h"


//VerificationType command_parser();

void float2string(float32_t value, char* outbuf, int precision);

void axi_phase_write(u32 phase_val);

void axi_testType_write(u32 phase_val);

void axi_staticData_write(int index);

void axi_startOp_write();

void single_static_test();

void multiple_static_test();

void dynamic_test();

void cb_test();

void view_dynamic_buffer();

void view_dynamic_buffer_dec();

void dynamic_test_non_interrupt();

void fft_func();

void staticTestError_calculations(float32_t refValue);

void dynamicTestError_calculations();

float32_t peak2peak_f32(const float32_t* data, uint32_t length);

void dynamicTestResult_reset();

void dynamicTestResult_passed();

void dynamicTestResult_failed();

void staticTestResult_reset();

void staticTestResult_passed();

void staticTestResult_failed();

#endif /* SRC_CURRENTSENSEVERIFICATION_H_ */
