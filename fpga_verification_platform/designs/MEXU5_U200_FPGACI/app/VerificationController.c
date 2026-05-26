/*
 * VerificationController.c
 *
 *  Created on: 01.10.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#include "VerificationController.h"


static VerificationType state_type = Idle;
static u8 temp_recv_buffer[BUFFER_SIZE] = {};
static char *token = 0;
//#define multiple_static_value
#define single_static_value
char* pwm_freq[3] = {"2000","4000","8000"};
//uint64_t duty = 67117057000ULL; 	// 0x0FA07D03E8 16khz - 50,50,50
//uint64_t duty = 67113780800ULL; 	// 0x0fa04b0640 16khz - 50,30,80
//uint64_t duty = 26856653800ULL;   // 0x640C803E8  16khz - 20,80,50
//uint64_t duty = 134234114000ULL;  // 0x1F40FA07D0 8Kz   - 50,50,50
//uint64_t duty = 107397121000ULL;  // 0x19015E03E8 8Khz  - 40,70,25
//uint64_t duty = 26873039200ULL;	// 0x641C20960  8Khz  - 10,90,60
//uint64_t duty = 268468228000ULL;	// 0x3E81F40FA0 4Khz  - 50,50,50
//uint64_t duty = 187914655600ULL;  // 0x2BC0961770 4khz  - 35,15,75
//uint64_t duty = 375822749600ULL;	// 0x5780C80FA0 4khz  - 70,20,50
uint64_t duty_16k[3] = {67117057000ULL, 67113780800ULL, 26856653800ULL};
uint64_t duty_8k[3] = {134234114000ULL, 107397121000ULL, 26873039200ULL};
uint64_t duty_4k[3] = {187914655600ULL, 268468228000ULL, 375822749600ULL};
static u8 freq_increment = 0;
static u8 duty_increment = 0;

u32 phase_val = 0;
u32 mode_val = 0;
u32 ovc_phase_val = 0;

VerificationType servo_verification_fsm()
{

	switch(state_type)
	{
		case Idle:

			 xil_printf("Please send the command to UART0 (e.g., phu_s): \r\n");

			 // Wait for input on UART0 via interrupt
			 TotalReceivedCountUART0 = 0; // Reset count
			 while(TotalReceivedCountUART0 == 0){
				 // Do other tasks or simply yield/sleep briefly
			 	 usleep(100);
			 }

			 if (TotalReceivedCountUART0 > 0)
			 {
				 state_type = Parse_command;
			 }
			 break;

		case Parse_command:

			xil_printf("Received command: %s\r\n", RecvBufferUART0);

			// Copy received command to UART1 send buffer
			strncpy((char *)send_buffer_uart1, (char *)RecvBufferUART0, BUFFER_SIZE - 1);
			send_buffer_uart1[BUFFER_SIZE - 1] = '\0'; // Ensure null-termination

			// Make a copy of RecvBufferUART0 for strtok, as strtok modifies its input

			strncpy((char *)temp_recv_buffer, (char *)RecvBufferUART0, BUFFER_SIZE);
			temp_recv_buffer[BUFFER_SIZE - 1] = '\0';

			token = strtok((char*)temp_recv_buffer, "_");

			 if(token != NULL) {
				 if (strcmp(token, "phu") == 0)       { phase_val = 0x08; state_type = CurrentSense_Verification; }
				 else if (strcmp(token , "phv") == 0) { phase_val = 0x09; state_type = CurrentSense_Verification; }
				 else if (strcmp(token , "phw") == 0) { phase_val = 0x0A; state_type = CurrentSense_Verification; }
				 else if (strcmp(token , "pwm") == 0) { state_type = PWM_Verification; }
				 else if (strcmp(token , "ovc") == 0) { state_type = OVC_Verification; }
				 }
			 break;

		case CurrentSense_Verification:

			 axi_phase_write(phase_val);

			 token = strtok (NULL, "_");

			 if (token != NULL) {
				 if (strcmp (token, "s") == 0) mode_val = 0;
				 else if (strcmp(token, "d") == 0) mode_val = 1;
				 }

			 if (mode_val == 0)
				  state_type = CurrentSense_static;
			 else if(mode_val == 1)
				  state_type =  CurrentSense_dynamic;

			break;
		case CurrentSense_static:

			axi_testType_write(mode_val);

#ifdef single_static_value

			single_static_test();

#endif

#ifdef multiple_static_value

			multiple_static_test();

#endif

			state_type = Idle;

			break;

		case CurrentSense_dynamic:

			axi_testType_write(mode_val);
			dynamic_test();
			fft_func();
			dynamicTestError_calculations();
			state_type = Idle;

			break;

		case PWM_Verification:

			state_type = PWM_setFrequency;

			break;

		case PWM_setFrequency:

			memset(send_buffer_uart1, 0, sizeof(send_buffer_uart1));
			strncpy((char *)send_buffer_uart1, "pwm_f_a1", BUFFER_SIZE);
			send_via_UART1();

			strncpy((char *)temp_recv_buffer, pwm_freq[freq_increment], BUFFER_SIZE);
			temp_recv_buffer[BUFFER_SIZE - 1] = '\0';

				// Convert received string to integer
			uint16_t freq_ = (uint16_t)atoi((char *)temp_recv_buffer);

			memset(send_buffer_uart1, 0, sizeof(send_buffer_uart1));
			send_buffer_uart1[1] = (uint8_t)(freq_ & 0xFF);        // LSB
			send_buffer_uart1[0] = (uint8_t)((freq_ >> 8) & 0xFF); // MSB
			send_buffer_uart1[2] = '\0';                          // Null terminator for strlen
			send_via_UART1();

			state_type = PWM_setDutyCycle;
			break;

		case PWM_setDutyCycle:

			memset(send_buffer_uart1, 0, sizeof(send_buffer_uart1));
			strncpy((char *)send_buffer_uart1, "pwm_d_a1", BUFFER_SIZE);
			send_via_UART1();

			uint64_t duty = 0;

			if (freq_increment == 0)
			{
				duty = duty_16k[duty_increment];
			}
			else if(freq_increment == 1)
			{
				duty = duty_8k[duty_increment];
			}
			else if(freq_increment == 2)
			{
				duty = duty_4k[duty_increment];
			}

			memset(send_buffer_uart1, 0, sizeof(send_buffer_uart1));
			send_buffer_uart1[4] = (uint8_t)(duty & 0xFF);
			send_buffer_uart1[3] = (uint8_t)((duty >> 8) & 0xFF);
			send_buffer_uart1[2] = (uint8_t)((duty >> 16) & 0xFF);
			send_buffer_uart1[1] = (uint8_t)((duty >> 24) & 0xFF);
			send_buffer_uart1[0] = (uint8_t)((duty >> 32) & 0xFF);
			send_buffer_uart1[5] = '\0'; // Null terminator for strlen
			send_via_UART1();
			usleep(800);


			state_type = PWM_Capture;
			break;

		case PWM_Capture:

			pwm_capture();

			if(duty_increment == 2)
			{
				duty_increment = 0;

				if(freq_increment == 2)
				{
					freq_increment = 0;
					state_type = Idle;
				}
				else
				{
					freq_increment = freq_increment + 1;
					state_type = PWM_setFrequency;
				}
			}
			else
			{
				duty_increment = duty_increment + 1;
				state_type = PWM_setDutyCycle;
			}

			break;

		case OVC_Verification:

			token = strtok (NULL, "_");

			if (token != NULL) {
				if (strcmp (token, "u") == 0) ovc_phase_val = 0x08;
				else if (strcmp(token, "v") == 0) ovc_phase_val = 0x09;
				else if (strcmp(token, "w") == 0) ovc_phase_val = 0x0A;
			}

			ovc_axi_phase_write(ovc_phase_val);

			ovc_static_verification();

			state_type = Idle;

			break;

		case Error:

			break;
		default:
			break;

	}

	return 0;
}
