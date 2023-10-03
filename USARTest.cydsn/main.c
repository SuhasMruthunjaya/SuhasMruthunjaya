/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "stdlib.h"
#include "project.h"



volatile unsigned int time = 0;
//char* itoa(char* string, unsigned int time);
CY_ISR_PROTO(isr_timerTick);


int main(void)
{
   CyGlobalIntEnable; /* Enable global interrupts. */
 /* Place your initialization/startup code here */

 isr_timer_StartEx(isr_timerTick);
 SYSCLOCK_Start();
 SYSCOUNTER_Start();
 for(;;)
 {
 /* Place your application code here. */
    
    //UART_LOG_Start();
    
    
 }
}
CY_ISR(isr_timerTick)
{   
    char string[sizeof(int)*8+1];
    time++;
    UART_LOG_Start();
    itoa(time,string,10);
    UART_LOG_PutString(string);
 Led_Green_Write(time%2);
}
