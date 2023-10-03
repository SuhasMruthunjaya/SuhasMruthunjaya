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
#include "project.h"
#include "global.h"
#include "stdlib.h"


ISR(systick_handler)
{
 CounterTick(cnt_systick);
 // A static variable to be used at various places, the life time of this variable
 // is until the lifetime of the program.
}

int main()
{
 CyGlobalIntEnable; /* Enable global interrupts. */

    //Set systick period to 1 ms. Enable the INT and start it.
    EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
    EE_systick_enable_int();

// Start Operating System
 for(;;)
 StartOS(OSDEFAULTAPPMODE);
}
/*********************************************************************
***********
* Task Definitions
**********************************************************************
**********/

/* All the peripherals and the drivers used are initialised in tsk_init */
TASK(tsk_init)
{

 //Init MCAL Drivers
// LED_Init();

 //Reconfigure ISRs with OS parameters.
 //This line MUST be called after the hardware driver
 //initialization!
 EE_system_init();
 // Must be started after interrupt reconfiguration
 EE_systick_start();

 TerminateTask();

}


TASK(tsk_background)
{
    while(1)
    {
        __asm("nop");
    }
}


/* The ISR is triggered whenever a button is pressed, this inturn calls 
   a function (state machine)*/

//ISR2(isr_button)
//{       
 //  GAME_Play();
//}




/* [] END OF FILE */
