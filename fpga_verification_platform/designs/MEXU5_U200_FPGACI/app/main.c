/*
 * 	main.c
 *
 *  Created on: 16.07.2025
 *      Author: SESA807379 (Suhas Bangalore Mruthunjaya)
 */


#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xuartps.h"
#include "xil_io.h"
#include <string.h>
#include <sleep.h>
#include <stdbool.h>
#include "xtime_l.h"
#include "uart_comm.h"
#include "CurrentSenseVerification.h"
#include "PWMVerification.h"
#include "ringbuffer.h"
#include "xscugic.h" // For Zynq UltraScale+ MPSoC GIC
#include "logFile.h"
#include "VerificationController.h"

// --- Main application code ---
int main() {
    init_platform();

    uart_init();

    uart_interrupt_init();

    file__init();


    while(1){

    	servo_verification_fsm();

    }

    RB_deinit(&ringbuffer_inst);

    file__deinit();

    cleanup_platform();
    return 0;
}

