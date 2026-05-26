/*
 * uart_comm.h
 *
 *  Created on: 16.07.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#ifndef SRC_UART_COMM_H_
#define SRC_UART_COMM_H_

#include "xscugic.h" // For Zynq UltraScale+ MPSoC GIC
#include "xuartps.h"
#include "axi_reg.h"
#include "ringbuffer.h"

// UART Configuration
#define UART0_DEVICE_ID 	XPAR_XUARTPS_0_DEVICE_ID
#define UART0_INT_IRQ_ID	XPAR_XUARTPS_0_INTR      // <--- Changed to UART0 interrupt ID
#define UART1_DEVICE_ID 	XPAR_XUARTPS_1_DEVICE_ID // UART1 will now be polled or used differently
#define UART1_INT_IRQ_ID 	XPAR_XUARTPS_1_INTR

#define BUFFER_SIZE 32
#define BUFFER_SIZE_UART1	4096

// Global variables for interrupt handler (make sure they are volatile)
extern volatile u8 RecvBufferUART0[BUFFER_SIZE];
extern volatile int TotalReceivedCountUART0;
extern volatile int TotalSentCountUART0;

// UART1 will be handled via polling, so its global variables are no longer strictly
// needed for interrupt handling, but kept for general buffer management.

// Global Variables used to UART1 Communication
extern u8 send_buffer_uart1[BUFFER_SIZE];
extern volatile u8 RecvBufferUART1[BUFFER_SIZE_UART1];
extern volatile int TotalReceivedCountUART1;
extern volatile int TotalSentCountUART1;

extern RB_t ringbuffer_inst;

//typedef struct {
//	XUartPs* UartInstPtr;
//	RB_t* 	 RingBufPtr;
//}UartHandlerContext;

void uart_init();

void uart_interrupt_init();

void Uart0Handler(void *CallBackRef, u32 Event, unsigned int EventData);

void Uart1Handler(void *CallBackRef, u32 Event, unsigned int EventData);

void send_via_UART0();

void send_via_UART1();

int recieve_from_UART0();

int recieve_from_UART1();



#endif /* SRC_UART_COMM_H_ */
