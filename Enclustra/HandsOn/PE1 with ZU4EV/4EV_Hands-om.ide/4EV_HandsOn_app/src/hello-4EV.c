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
#include "xgpio.h"

#define GPIO_EXAMPLE_DEVICE_ID XPAR_GPIO_0_DEVICE_ID
#define GPIO_EXAMPLE_DEVICE_ID1 XPAR_GPIO_1_DEVICE_ID
#define GPIO_EXAMPLE_DEVICE_ID2 XPAR_GPIO_2_DEVICE_ID
#define LED_CHANNEL 1
#define LED_DELAY   10000000
#define LED 0x0F
XGpio  Gpio;

XGpio  Gpio1;
XGpio  Gpio2;

int main()
{
	int Status;
	volatile long int Delay;
    init_platform();

    print("Hello World\n\r");
    print("Successfully ran Hello World application");
    Status=XGpio_Initialize(&Gpio, GPIO_EXAMPLE_DEVICE_ID);
    if (Status != XST_SUCCESS){
    	xil_printf("Fehler\r\n");
    	return XST_FAILURE;
    }

/*
    Status=XGpio_Initialize(&Gpio1, GPIO_EXAMPLE_DEVICE_ID1);
       if (Status != XST_SUCCESS){
       	xil_printf("Fehler\r\n");
       	return XST_FAILURE;
       }

       Status=XGpio_Initialize(&Gpio2, GPIO_EXAMPLE_DEVICE_ID2);
              if (Status != XST_SUCCESS){
              	xil_printf("Fehler\r\n");
              	return XST_FAILURE;
              }
*/
       while(1){
   /* 	   for (Delay=0; Delay<LED_DELAY;Delay++);
      XGpio_DiscreteWrite(&Gpio1,1,0x0E);//Segment 1bis 5

      for (Delay=0; Delay<LED_DELAY;Delay++);
      XGpio_DiscreteWrite(&Gpio1,1,0x0D);//Segment 1
	   for (Delay=0; Delay<LED_DELAY;Delay++);
     XGpio_DiscreteWrite(&Gpio1,1,0x0B);//Segment 1bis 5

     for (Delay=0; Delay<LED_DELAY;Delay++);
     XGpio_DiscreteWrite(&Gpio1,1,0x07);//Segment 1
*/


          for (Delay=0; Delay<LED_DELAY;Delay++);
          XGpio_DiscreteWrite(&Gpio,1,0x0F);//Segment 1

          for (Delay=0; Delay<LED_DELAY;Delay++);
          XGpio_DiscreteWrite(&Gpio,1,0x01);//Segment 1

          for (Delay=0; Delay<(LED_DELAY*10);Delay++);
          XGpio_DiscreteWrite(&Gpio,1,0x02);//Segment 1

          for (Delay=0; Delay<(LED_DELAY*10);Delay++);
          XGpio_DiscreteWrite(&Gpio,1,0x04);//Segment 1


       }


    cleanup_platform();
    return 0;
}
