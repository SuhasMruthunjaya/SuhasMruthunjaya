/******************************************************************************
*
* Copyright (C) 2009 - 2014 Xilinx, Inc.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* Use of the Software is limited solely to applications:
* (a) running on a Xilinx device, or
* (b) that interact with a Xilinx device through a bus or interconnect.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
* XILINX  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
* OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
* Except as contained in this notice, the name of the Xilinx shall not be used
* in advertising or otherwise to promote the sale, use or other dealings in
* this Software without prior written authorization from Xilinx.
*
******************************************************************************/

/*
 * helloworld.c: simple test application
 *
 * This application configures UART 16550 to baud rate 9600.
 * PS7 UART (Zynq) is not initialized by this application, since
 * bootrom/bsp configures it to baud rate 115200
 *
 * ------------------------------------------------
 * | UART TYPE   BAUD RATE                        |
 * ------------------------------------------------
 *   uartns550   9600
 *   uartlite    Configurable only in HW design
 *   ps7_uart    115200 (configured by bootrom/bsp)
 */

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
// Xilinx Include
#include "xil_types.h"
#include "xparameters.h"
#include "xil_io.h"
#include "OVC_PROTECT_IP.h"

#define OVC_IP_A 			XPAR_OVC_PROTECT_IP_0_S_AXI_LITE_BASEADDR   	// 0x80030000
#define OVC_LIMITS_OFFSET	OVC_PROTECT_IP_S_AXI_LITE_OVC_LIMITS_OFFSET		// 0x8
#define OVC_SETTINGS_OFFSET OVC_PROTECT_IP_S_AXI_LITE_OVC_SETTINGS_OFFSET   // 0xC

#define PHX_ENABLE_TRIGGER	XPAR_AXI_GPIO_0_BASEADDR

int main()
{
    init_platform();
    // Hardware PSAVE Activation
    Xil_Out32(0x00FF180094, 0x00000000);
    Xil_Out32(0x00FF0A0008, 0x00000000);
    Xil_Out32(0x00FF0A000C, 0x00000000);
    Xil_Out32(0x00FF0A0244, 0x00000800);
    Xil_Out32(0x00FF0A0248, 0x00000800);
    Xil_Out32(0x00FF0A0044, 0x00000800);
    //PSAVE activated --> SPI can be started

    // Wait 50ms for Power Supplies ramp up
    usleep(50000);

    // FPGA PSAVE EMIO Activation
    Xil_Out32(0x00FF0A0018, 0x00000000); // MASK_DATA_3_LSW Register for EMIO Bank 0
    Xil_Out32(0x00FF0A001C, 0x00000000); // MASK_DATA_3_MSW Register for EMIO Bank 0
    Xil_Out32(0x00FF0A02C4, 0x00004000); // INT_MASK_3 Register for EMIO Bank 0  --> activate Interrupt
    Xil_Out32(0x00FF0A02C8, 0x00004000); // OEN_3  Register for EMIO Bank 0  --> Output Enable
    Xil_Out32(0x00FF0A004C, 0x00004000); // DATA_3 Register for EMIO Bank 0  --> Activate the right GPIO EMIO Pin

    // Wait some time before activating current sense
    usleep(2000);

    // Current Sense Enable
    Xil_Out32(PHX_ENABLE_TRIGGER, 0x1);

    // Trigger Current Sensor continuous enable
    Xil_Out32(PHX_ENABLE_TRIGGER, 0x3);

    // Trigger Current Sensor
    Xil_Out32(PHX_ENABLE_TRIGGER, 0x7);

    usleep(5);
    // Trigger Current Sensor
    Xil_Out32(PHX_ENABLE_TRIGGER, 0x3);

    print("Hello World\n\r");
    print("Successfully ran Hello World application");
    while(1){

    }
    cleanup_platform();
    return 0;
}
