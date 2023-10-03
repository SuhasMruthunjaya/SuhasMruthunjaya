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

#include "tsk_realtime.h"
#include "tsk_system.h"
#include "joystick.h"
#include "pwm.h"
#include "watchdog.h"
#include "stdlib.h"


//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
    // Start Watchdog Timer
    WD_Start(WDT_1024_TICKS);
    
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_init)
{

    
    //Init MCAL Drivers
    UART_LOG_Start();
    JOYSTICK_INIT();
    PWM_INIT();   
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start(); 
    
    
    if(WD_CheckResetBit())
    UART_LOG_PutString("The system was rebooted after a WATCHDOG reset\r");
    else 
    UART_LOG_PutString("The system was rebooted after a power on reset (POR)\r");
 
 
    SetRelAlarm(alrm_callback,1,1);
	
    ActivateTask(tsk_background);
    
    TerminateTask();
    
}

ALARMCALLBACK(alarm_1ms)
{
    ActivateTask(tsk_realtime);
    SetEvent(tsk_realtime,ev_1ms);
    ActivateTask(tsk_system);
    
}




TASK(tsk_background)
{
    while(1)
    {
       while(global_bitfield == 31)
      {
        WD_Trigger();
        global_bitfield = 0;
      }
             
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_button)
{       

   ShutdownOS(OSDEFAULTAPPMODE);

}




/* [] END OF FILE */
