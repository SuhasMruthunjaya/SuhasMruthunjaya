/*
 * CurrentSenseVerification.c
 *
 *  Created on: 16.07.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#include "CurrentSenseVerification.h"
#include "VerificationController.h"
#include <sleep.h>
#include "ringbuffer.h"
#include "arm_math.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dsp/transform_functions.h"
#include "logFile.h"
#include "string.h"

// Define constants for the ADC and reference voltage
#define ADC_BITS            12
#define ADC_MAX_VAL         (float32_t)(1 << (ADC_BITS - 1)) // 2048.0 for a signed 12-bit ADC
#define V_REF               3.3f
#define FFT_SIZE            2048

#define REF_MAX_VALUE 			4.342615f
#define REF_MAX_IDX				2
#define REF_MAX_FREQUENCY		1000.000000f
#define REF_PEAK2PEAK_VALUE		3.299950f
#define REF_RMS_VALUE			1.165821f

static u16 static_data[6] = {0x0000, 0x3333, 0x6666, 0x9999, 0xCCCC, 0xFFFF};
static int16_t dynamic_data_buffer[FFT_SIZE] = {};
static int16_t static_data_16t = 0;
static float32_t dynamic_data_decimal_buffer[FFT_SIZE] = {};
static float32_t dynamic_data_decimal_buffer_copy[FFT_SIZE] = {};
//static u8 temp_recv_buffer[BUFFER_SIZE] = {};

static int dynamicTestResult = 0;
static int staticTestResult = 0;
static float32_t max_val, freq;
static uint32_t max_index;

// Output buffer for the FFT, must be 2*FFT_SIZE for a real FFT
static float32_t fft_output_buffer[FFT_SIZE * 2];
// Buffer to store the magnitudes of the frequency bins
static float32_t magnitude_buffer[(FFT_SIZE / 2) + 1];

// ARM CMSIS DSP FFT instance
arm_rfft_fast_instance_f32 S;

void axi_phase_write(u32 phase_val)
{
	Xil_Out32(AXI_PRACTISE_IP_BASE_ADDR + DAC_PHASE_AXIS_REG_OFFSET, phase_val);
	usleep(1000); // Small delay for AXI write
}

void axi_testType_write(u32 mode_val)
{
	Xil_Out32(AXI_PRACTISE_IP_BASE_ADDR + STATIC_DYNAMIC_REG_OFFSET, mode_val);
	usleep(1000); // Small delay for AXI write
}

void axi_staticData_write(int index)
{
    Xil_Out32(AXI_PRACTISE_IP_BASE_ADDR + STATIC_DATA_REG_OFFSET, static_data[index]);
    //xil_printf("static data written : 0x%x", static_data[index]);
    usleep(1000); // Small delay for AXI write
}

void axi_startOp_write()
{
    Xil_Out32(AXI_PRACTISE_IP_BASE_ADDR + START_OP_REG_OFFSET, 0x01);
    usleep(1000); // Small delay for AXI write
}

void single_static_test()
{
	axi_staticData_write(0);

	axi_startOp_write();

	send_via_UART1();

	while (ringbuffer_inst.m_fillLevel != 2){};

	xil_printf("Received from UART1: ");

	while (ringbuffer_inst.m_fillLevel > 0)
	{

		RB_content_t data = 0;
	    RB_get(&ringbuffer_inst, &data);
	    xil_printf("%c", data);

	}

	xil_printf("\r\n");

	RB_clear(&ringbuffer_inst);

	usleep(10000); // Delay between multiple static value iterations
}


void multiple_static_test()
{
    for (int i = 0; i < 6; i++) {

    	axi_staticData_write(i);

    	axi_startOp_write();

        send_via_UART1();


        while (ringbuffer_inst.m_fillLevel != 2){};

        xil_printf("Received from UART1 %d: ", i);

        while (ringbuffer_inst.m_fillLevel > 0)
        {

        	RB_content_t data1 = 0, data2 = 0;
        	RC_t ret = RB_get(&ringbuffer_inst, &data1);
        	if (ret != RC_SUCCESS)
        	{
        		xil_printf(" Error while receiving dynamic data from CB or in the Ringbuffer");
        	}
        	xil_printf("%c", data1);

        	ret = RB_get(&ringbuffer_inst, &data2);
        	if (ret != RC_SUCCESS)
        	{
        		xil_printf(" Error while receiving dynamic data from CB or in the Ringbuffer");
        	}
        	xil_printf("%c", data2);

        	static_data_16t = ((uint16_t)data1 << 8) | data2;

        }
        xil_printf("\r\n");

        RB_clear(&ringbuffer_inst);

        staticTestError_calculations(static_data[i]);

        usleep(10000); // Delay between multiple static value iterations
    }

}


void dynamic_test()
{

	axi_startOp_write();

	usleep(10000);

	send_via_UART1();

	while(ringbuffer_inst.m_fillLevel != 4096){};

	int i = 0;

    while (ringbuffer_inst.m_fillLevel > 0)
    {

    	RB_content_t data1, data2 = 0;
    	RC_t ret = RB_get(&ringbuffer_inst, &data1);
    	if (ret != RC_SUCCESS)
    	{
    		xil_printf(" Error while receiving dynamic data from CB or in the Ringbuffer");
    	}

    	ret = RB_get(&ringbuffer_inst, &data2);
    	if (ret != RC_SUCCESS)
    	{
    		xil_printf(" Error while receiving dynamic data from CB or in the Ringbuffer");
    	}

    	dynamic_data_buffer[i] = ((uint16_t)data1 << 8) | data2;

    	i ++;
    }


    for( int j=0 ; j < 2048; j++)
    {
    	u16 hwData;
    	float32_t decData;

    	hwData = dynamic_data_buffer[j];

    	decData = ((float32_t)hwData / pow(2, 12)) * 3.3;

    	dynamic_data_decimal_buffer[j] = decData;

    }

    RB_clear(&ringbuffer_inst);

    usleep(10000); // Delay between multiple dynamic value iterations

}

void dynamic_test_non_interrupt()
{

	axi_startOp_write();

	send_via_UART1();

	usleep(4000);

	recieve_from_UART1();

	for (int i = 0; i < 4096; i++) {
	    xil_printf("%03X", RecvBufferUART1[i]);
	    xil_printf("\n");
	}


}


void view_dynamic_buffer()
{
	for (int i = 0; i < 2048; i++) {
	    xil_printf("%03X", dynamic_data_buffer[i]);
	    xil_printf("\n");
	}
}

void view_dynamic_buffer_dec()
{
	for (int i = 0; i < 2048; i++) {
	    printf("%f\n\r", dynamic_data_decimal_buffer[i]);
	}
}

/**
 * @brief Performs a Fast Fourier Transform and calculates the magnitude.
 *
 * This function initializes the ARM CMSIS DSP real FFT instance,
 * performs a forward FFT on the `dynamic_data_float_buffer`, and then
 * calculates the magnitude of each frequency bin from the complex output.
 * The results are printed to the UART.
 */

void fft_func()
{
	// Initialize the real FFT instance for a 2048-point FFT
		arm_rfft_fast_init_f32(&S, FFT_SIZE);

		float32_t mean;

		arm_mean_f32(dynamic_data_decimal_buffer, FFT_SIZE, &mean);

		for (int i = 0; i < FFT_SIZE; i++) {
			dynamic_data_decimal_buffer[i] -= mean;
		}

		memcpy(dynamic_data_decimal_buffer_copy, dynamic_data_decimal_buffer, FFT_SIZE * sizeof(float32_t));

		// Perform the real FFT.
		// The output buffer is 2*FFT_SIZE in size to hold the interleaved complex results.
		// The `ifftFlag` is 0 for a forward FFT.
		arm_rfft_fast_f32(&S, dynamic_data_decimal_buffer, fft_output_buffer, 0);

		// Magnitude of DC component
		magnitude_buffer[0] = fabsf(fft_output_buffer[0]);

		// Magnitude of Nyquist component
		magnitude_buffer[FFT_SIZE / 2] = fabsf(fft_output_buffer[1]);

		// Calculate magnitudes for all other bins (k=1 to N/2-1)
		for (int i = 1; i < (FFT_SIZE / 2); i++)
		{
			float32_t real = fft_output_buffer[2 * i];
			float32_t imag = fft_output_buffer[2 * i + 1];
			magnitude_buffer[i] = sqrtf((real * real) + (imag * imag));
		}

		arm_max_f32(magnitude_buffer, (FFT_SIZE/2) + 1 , &max_val, &max_index);

		float32_t Fs = 984615.3846f;

		float32_t bin_width = Fs / (float32_t)FFT_SIZE;
		freq = max_index * bin_width;
		printf("Frequency of the sine wave: %.3f Hz\r\n", freq);

}


float32_t peak2peak_f32(const float32_t* data, uint32_t length)
{
	float32_t maxVal, minVal;
	uint32_t index;

	arm_max_f32(data, length, &maxVal, &index);
	arm_min_f32(data, length, &minVal, &index);

	return maxVal - minVal;

}

/**
 * @brief Convert a float to a string with fixed decimal precision.
 *
 * This function converts a floating-point number into a string representation
 * with a specified number of decimal places. It avoids using heavy printf
 * float formatting and is safe for bare-metal usage.
 *
 * @param value     The float value to convert.
 * @param outbuf    Pointer to a char array where the result will be stored.
 *                  The caller must ensure it is large enough to hold the result.
 * @param precision Number of digits after the decimal point.
 */
void float2string(float32_t value, char* outbuf, int precision)
{
    int scale = 1;
    for (int i = 0; i < precision; i++) scale *= 10;

    int ipart = (int)value;
    int fpart = (int)((value - ipart) * scale);
    if (fpart < 0) fpart = -fpart;

    char intstr[16], fracstr[16];

    itoa(ipart, intstr, 10);
    itoa(fpart, fracstr, 10);

    // pad fractional part with leading zeros
    int len = strlen(fracstr);
    char frac_padded[16] = {0};
    for (int i = 0; i < precision - len; i++) frac_padded[i] = '0';
    strcat(frac_padded, fracstr);

    strcpy(outbuf, intstr);
    strcat(outbuf, ".");
    strcat(outbuf, frac_padded);

}


void save_errors_to_sd(float32_t error_f, float32_t error_amp, float32_t error_rms, float32_t error_staticTest,
					   float32_t measuredValue, float32_t refValue) {

	char buffer[250];
	buffer[0] = '\0';

	if (phase_val == 0x08)
	{
		strcat(buffer, "Phase U - ");
	}
	else if (phase_val == 0x09)
	{
		strcat(buffer, "Phase V - ");
	}
	else if (phase_val == 0x0A)
	{
		strcat(buffer, "Phase W - ");
	}

	if (mode_val == 0)
	{
		strcat(buffer, "static test - ");
	}
	else if(mode_val == 1)
	{
		strcat(buffer, "dynamic test - ");
	}

	char freq_buff[20], error_f_buff[20], error_amp_buff[20], error_rms_buff[20], error_staticTest_buff[20];
	char measuredValue_buff[20], refValue_buff[20];

	if (mode_val == 1)
	{
			strcat(buffer, "Frequency : ");
			float2string(freq, freq_buff, 3);
			strcat(buffer, freq_buff);

			strcat(buffer, "Hz Freq Error: ");
			float2string(error_f, error_f_buff, 3);
			strcat(buffer, error_f_buff);

			strcat(buffer, "% Amp Error: ");
			float2string(error_amp, error_amp_buff, 3);
			strcat(buffer, error_amp_buff);

			strcat(buffer, "% RMS Error: ");
			float2string(error_rms, error_rms_buff, 3);
			strcat(buffer, error_rms_buff);

			if(dynamicTestResult == 1){
				strcat(buffer, "% TEST PASSED");
			}else if (dynamicTestResult == -1){
				strcat(buffer, "% TEST FAILED");
			}

			strcat(buffer, "\n");
	}
	else if(mode_val == 0)
	{
			strcat(buffer,"Reference Value (Volt) - ");
			float2string(refValue, refValue_buff, 3);
			strcat(buffer,refValue_buff);

			strcat(buffer, "V Measured Value (Volt) - ");
			float2string(measuredValue, measuredValue_buff, 3);
			strcat(buffer, measuredValue_buff);

			strcat(buffer, "V Error Percentage - ");
			float2string(error_staticTest, error_staticTest_buff, 3);
			strcat(buffer, error_staticTest_buff);

		 	if(staticTestResult == 1)
		 		strcat(buffer, "% TEST PASSED");
		 	else if (staticTestResult == -1)
		 		strcat(buffer, "% TEST FAILED");

		 	strcat(buffer, "\n");
	}


	file__write(buffer);

	xil_printf("Frequency and Error Percentages are saved to SD card.\r\n");

}

void staticTestError_calculations( float32_t refValue_16t)
{
		staticTestResult_reset();

		float32_t measuredValue = ((float32_t)static_data_16t / pow(2, 12)) * 3.3;
//		printf(" measured value : %f\r\n", measuredValue);

		float32_t refValue = ((float32_t)refValue_16t / pow(2, 16)) * 3.3;
//		printf(" reference value : %f\r\n", refValue);

		float32_t staticTest_error = 100.0f * (measuredValue - refValue) / refValue;
		if (staticTest_error < 0) staticTest_error = -staticTest_error;

		if ((measuredValue == 0.0f) && (refValue == 0.0f))
		{
			staticTest_error = 0.0f;
		}

//		printf("staticTest error: %f\r\n", staticTest_error);

		if (staticTest_error <= 1.5f)
			staticTestResult_passed();
		else
			staticTestResult_failed();

		save_errors_to_sd(0, 0, 0, staticTest_error, measuredValue, refValue);

}


void dynamicTestError_calculations()
{
		dynamicTestResult_reset();

		float32_t error_f = 100/REF_MAX_FREQUENCY * fabsf(REF_MAX_FREQUENCY - freq);
//		printf("Frequency Error : %f\r\n", error_f);

		float32_t error_amp = 100/REF_PEAK2PEAK_VALUE * (REF_PEAK2PEAK_VALUE - peak2peak_f32(dynamic_data_decimal_buffer_copy, FFT_SIZE));
//		printf("Amplitude Error : %f\r\n", error_amp);

		float32_t rms_result;

		arm_rms_f32(dynamic_data_decimal_buffer_copy, FFT_SIZE, &rms_result);

		float32_t error_rms = 100/REF_RMS_VALUE * (REF_RMS_VALUE - rms_result);
//		printf("RMS Error : %f\r\n", error_rms);

		if ((error_f < 5.0f) && (error_amp < 5.0f) && (error_rms < 5.0f)){
			dynamicTestResult_passed();
		}
		else{
			dynamicTestResult_failed();
		}

		save_errors_to_sd(error_f, error_amp, error_rms, 0, 0, 0);

}

void staticTestResult_reset()
{
	staticTestResult = 0;
}

void staticTestResult_passed()
{
	staticTestResult = 1;
}

void staticTestResult_failed()
{
	staticTestResult = -1;
}

void dynamicTestResult_reset()
{
	dynamicTestResult = 0;
}

void dynamicTestResult_passed()
{
	dynamicTestResult = 1;
}

void dynamicTestResult_failed()
{
	dynamicTestResult = -1;
}



void cb_test()
{

	    xil_printf("inside cb\r\n");

	    axi_staticData_write(2);
	    axi_startOp_write();

	    int received = 0;
	        while (received == 0) {
	            received = recieve_from_UART1();  // Try to receive data
	            usleep(100);                      // Prevent tight loop
	        }

	        xil_printf("Received from UART1:\r\n");
	        for (int i = 0; i < received; i++) {
	            xil_printf("%c", RecvBufferUART1[i]);
	        }

}

