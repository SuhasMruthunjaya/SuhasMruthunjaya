/*
 * uart_comm.c
 *
 *  Created on: 16.07.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */

#include "uart_comm.h"
#include <sleep.h>
#include "ringbuffer.h"
#include "xil_printf.h"

// Global variables for interrupt handler (make sure they are volatile)
volatile u8 RecvBufferUART0[BUFFER_SIZE];
volatile int TotalReceivedCountUART0 = 0;
volatile int TotalSentCountUART0 = 0;

// UART1 will be handled via polling, so its global variables are no longer strictly
// needed for interrupt handling, but kept for general buffer management.


static XUartPs UartPs0; // Instance for UART0
static XUartPs UartPs1; // Instance for UART1
static XScuGic GicInstance; // GIC instance for interrupt controller

static XUartPs_Config *config0, *config1;

// --- Function Prototypes for Interrupts ---
static int SetupInterruptSystem(XScuGic *IntcInstancePtr, XUartPs *UartInstancePtr, u16 UartIntrId);

// Global Variables used to UART1 Communication
u8 send_buffer_uart1[BUFFER_SIZE] = "";
volatile u8 RecvBufferUART1[BUFFER_SIZE_UART1];
volatile int TotalReceivedCountUART1 = 0;
volatile int TotalSentCountUART1 = 0;

RB_t ringbuffer_inst;
#define ringbuffer_inst_size 4096

void uart_init()
{
	// Initialize UART0
	config0 = XUartPs_LookupConfig(UART0_DEVICE_ID);
	if (config0 == NULL) {
	    xil_printf("Error: UART0 configuration not found! Device ID: 0x%x\r\n", UART0_DEVICE_ID);
	}
	XUartPs_CfgInitialize(&UartPs0, config0, config0->BaseAddress);
	XUartPs_SetBaudRate(&UartPs0, 115200);

	// Initialize UART1 (no interrupt setup for this one)
	config1 = XUartPs_LookupConfig(UART1_DEVICE_ID);
	if (config1 == NULL) {
		xil_printf("Error: UART1 configuration not found! Device ID: 0x%x\r\n", UART1_DEVICE_ID);
	}
	XUartPs_CfgInitialize(&UartPs1, config1, config1->BaseAddress);
	XUartPs_SetBaudRate(&UartPs1, 921600);

	// Ringbuffer initialisation for UART1
	RB_init(&ringbuffer_inst, ringbuffer_inst_size);

}


void uart_interrupt_init()
{

	 // --- Setup Interrupts for UART0 ---
	 int Status = SetupInterruptSystem(&GicInstance, &UartPs0, UART0_INT_IRQ_ID); // <--- Setup UART0 interrupts
	 if (Status != XST_SUCCESS) {
		 xil_printf("Error: UART0 Interrupt System Setup Failed!\r\n");
//		 return XST_FAILURE;
	 }
	 // Set the handler for UART0
	 XUartPs_SetHandler(&UartPs0, (XUartPs_Handler)Uart0Handler, &UartPs0); // <--- Set handler for UART0
	 // Enable relevant UART interrupts for UART0
	 u32 IntrMask = XUARTPS_IXR_RXFULL | XUARTPS_IXR_RXOVR | XUARTPS_IXR_TOUT | XUARTPS_IXR_TXEMPTY;
	 if (UartPs0.Platform == XPLAT_ZYNQ_ULTRA_MP) { // Use UartPs0.Platform
		 IntrMask |= XUARTPS_IXR_RBRK;
     }
	 XUartPs_SetInterruptMask(&UartPs0, IntrMask);
	 // Set receiver timeout for UART0
	 XUartPs_SetRecvTimeout(&UartPs0, 8);

	 // Start an asynchronous receive operation for UART0
	 //XUartPs_Recv(&UartPs0, (u8 *)RecvBufferUART0, BUFFER_SIZE); // <--- Start async receive for UART0
	 recieve_from_UART0();


	 // --- Setup Interrupts for UART1 ---
	    // Connect a device driver handler for UART1 to the GIC
	    Status = XScuGic_Connect(&GicInstance, UART1_INT_IRQ_ID,
	                             (Xil_ExceptionHandler)XUartPs_InterruptHandler,
	                             (void *)&UartPs1);
	    if (Status != XST_SUCCESS) {
	        xil_printf("Error: UART1 GIC Connect Failed!\r\n");
	        return;
	    }

	 // Enable the interrupt for UART1 in the GIC
	 XScuGic_Enable(&GicInstance, UART1_INT_IRQ_ID);

	 // Set the handler for UART0
	 XUartPs_SetHandler(&UartPs1, (XUartPs_Handler)Uart1Handler, &UartPs1); // <--- Set handler for UART0
	 // Enable relevant UART interrupts for UART0
	 IntrMask = XUARTPS_IXR_RXFULL | XUARTPS_IXR_RXOVR | XUARTPS_IXR_TOUT | XUARTPS_IXR_TXEMPTY;
	 if (UartPs1.Platform == XPLAT_ZYNQ_ULTRA_MP) { // Use UartPs0.Platform
		 IntrMask |= XUARTPS_IXR_RBRK;
     }
	 XUartPs_SetInterruptMask(&UartPs1, IntrMask);
	 // Set receiver timeout for UART0
	 XUartPs_SetRecvTimeout(&UartPs1, 8);

	 // Start an asynchronous receive operation for UART0
	 //XUartPs_Recv(&UartPs0, (u8 *)RecvBufferUART0, BUFFER_SIZE); // <--- Start async receive for UART0
	 recieve_from_UART1();

}



// --- Setup Interrupt System for XScuGic (for Zynq UltraScale+ MPSoC) ---
static int SetupInterruptSystem(XScuGic *IntcInstancePtr,
                                XUartPs *UartInstancePtr,
                                u16 UartIntrId)
{
    int Status;
    XScuGic_Config *IntcConfig;

    /* Initialize the interrupt controller driver */
    IntcConfig = XScuGic_LookupConfig(XPAR_SCUGIC_SINGLE_DEVICE_ID);
    if (NULL == IntcConfig) {
        return XST_FAILURE;
    }

    Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig,
                                   IntcConfig->CpuBaseAddress);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    /*
     * Connect the interrupt controller interrupt handler to the
     * hardware interrupt handling logic in the processor.
     */
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
                                 (Xil_ExceptionHandler)XScuGic_InterruptHandler,
                                 IntcInstancePtr);

    /*
     * Connect a device driver handler that will be called when an
     * interrupt for the device occurs, the device driver handler
     * performs the specific interrupt processing for the device
     */
    Status = XScuGic_Connect(IntcInstancePtr, UartIntrId,
                             (Xil_ExceptionHandler)XUartPs_InterruptHandler,
                             (void *)UartInstancePtr);
    if (Status != XST_SUCCESS) {
        return XST_FAILURE;
    }

    /* Enable the interrupt for the device */
    XScuGic_Enable(IntcInstancePtr, UartIntrId);

    /* Enable interrupts at the processor level */
    Xil_ExceptionEnable();

    return XST_SUCCESS;
}

// --- Interrupt Handler Function for UART0 ---
void Uart0Handler(void *CallBackRef, u32 Event, unsigned int EventData) {
    Xil_AssertVoid(CallBackRef != NULL);
    XUartPs *UartInstPtr = (XUartPs *)CallBackRef;


    if (Event == XUARTPS_EVENT_SENT_DATA) {
        TotalSentCountUART0 = EventData;
        // xil_printf("UART0 Sent: %d bytes\r\n", EventData); // For debugging
    }

    if (Event == XUARTPS_EVENT_RECV_DATA) {
        TotalReceivedCountUART0 = EventData;

        // Null-terminate the buffer received in the interrupt context
        RecvBufferUART0[TotalReceivedCountUART0 < BUFFER_SIZE ? TotalReceivedCountUART0 : BUFFER_SIZE - 1] = '\0';
        // Re-arm the receive operation to prepare for the next incoming data
        XUartPs_Recv(UartInstPtr, (u8 *)RecvBufferUART0, BUFFER_SIZE);
        //recieve_from_UART0();

    }

    if (Event == XUARTPS_EVENT_RECV_TOUT) {

        TotalReceivedCountUART0 = EventData; // Data received before timeout
        // xil_printf("UART0 Recv Timeout: %d bytes\r\n", EventData); // For debugging
        // Null-terminate the buffer received
        RecvBufferUART0[TotalReceivedCountUART0 < BUFFER_SIZE ? TotalReceivedCountUART0 : BUFFER_SIZE - 1] = '\0';
        // Re-arm the receive operation
        XUartPs_Recv(UartInstPtr, (u8 *)RecvBufferUART0, BUFFER_SIZE);
        //recieve_from_UART0();
    }

    if (Event == XUARTPS_EVENT_RECV_ERROR ||
        Event == XUARTPS_EVENT_PARE_FRAME_BRKE ||
        Event == XUARTPS_EVENT_RECV_ORERR) {

        // Handle errors, possibly reset UART or log them
        // xil_printf("UART0 Receive Error (Event: %lx, Data: %d)\r\n", Event, EventData); // For debugging
        TotalReceivedCountUART0 = EventData; // Still capture data received before error
        // Re-arm the receive operation even after an error
        XUartPs_Recv(UartInstPtr, (u8 *)RecvBufferUART0, BUFFER_SIZE);
        //recieve_from_UART0();
    }
}

void Uart1Handler(void *CallBackRef, u32 Event, unsigned int EventData) {
	Xil_AssertVoid(CallBackRef != NULL);
	    XUartPs *UartInstPtr = (XUartPs *)CallBackRef;


	    if (Event == XUARTPS_EVENT_SENT_DATA) {
	        TotalSentCountUART1 = EventData;
	        //xil_printf("UART0 Sent: %d bytes\r\n", EventData); // For debugging
	    }

	    if (Event == XUARTPS_EVENT_RECV_DATA) {
	        TotalReceivedCountUART1 = EventData;

	        // Null-terminate the buffer received in the interrupt context
	        RecvBufferUART1[TotalReceivedCountUART1 < BUFFER_SIZE_UART1 ? TotalReceivedCountUART1 : BUFFER_SIZE_UART1 - 1] = '\0';
	        // Re-arm the receive operation to prepare for the next incoming data
	        XUartPs_Recv(UartInstPtr, (u8 *)RecvBufferUART1, BUFFER_SIZE_UART1);

	        for (int i = 0; i < TotalReceivedCountUART1; i++)
	        {
	        	RB_put(&ringbuffer_inst, RecvBufferUART1[i]);
//	        	xil_printf("Data in Ringbuffer: %d\n", RecvBufferUART1[i]);
	        }

	    }

	    if (Event == XUARTPS_EVENT_RECV_TOUT) {

	        TotalReceivedCountUART1 = EventData; // Data received before timeout
	        // xil_printf("UART0 Recv Timeout: %d bytes\r\n", EventData); // For debugging
	        // Null-terminate the buffer received
	        RecvBufferUART1[TotalReceivedCountUART1 < BUFFER_SIZE_UART1 ? TotalReceivedCountUART1 : BUFFER_SIZE_UART1 - 1] = '\0';
	        // Re-arm the receive operation
	        XUartPs_Recv(UartInstPtr, (u8 *)RecvBufferUART1, BUFFER_SIZE_UART1);

	        for (int i = 0; i < TotalReceivedCountUART1; i++)
	        {
	        	RB_put(&ringbuffer_inst, RecvBufferUART1[i]);
//	        	xil_printf("Data in Ringbuffer: %d\n", RecvBufferUART1[i]);
	        }

	    }

	    if (Event == XUARTPS_EVENT_RECV_ERROR ||
	        Event == XUARTPS_EVENT_PARE_FRAME_BRKE ||
	        Event == XUARTPS_EVENT_RECV_ORERR) {

	        // Handle errors, possibly reset UART or log them
	        // xil_printf("UART0 Receive Error (Event: %lx, Data: %d)\r\n", Event, EventData); // For debugging
	        TotalReceivedCountUART1 = EventData; // Still capture data received before error
	        // Re-arm the receive operation even after an error
	        XUartPs_Recv(UartInstPtr, (u8 *)RecvBufferUART1, BUFFER_SIZE_UART1);
	    }

}


void send_via_UART0()
{

}

void send_via_UART1()
{
	XUartPs_Send(&UartPs1, send_buffer_uart1, strlen((char *)send_buffer_uart1));
}

int recieve_from_UART0()
{
	return XUartPs_Recv(&UartPs0, (u8 *)RecvBufferUART0, BUFFER_SIZE);
}

int recieve_from_UART1()
{
	return XUartPs_Recv(&UartPs1, (u8 *)RecvBufferUART1, BUFFER_SIZE_UART1);
}



