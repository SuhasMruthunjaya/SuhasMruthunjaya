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
#include "derivate.h"
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
   
 //   PWM_RGB_Red_Start();

 //  PWM_RGB_Blue_Start();
   
    UART_LOG_Start();
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start(); 
    
    CyWdtStart(CYWDT_1024_TICKS,CYWDT_LPMODE_NOCHANGE);
    
    UART_LOG_PutString("Task init entered");
    
    SetRelAlarm(alrm_led,1,100);
    
    ActivateTask(tsk_background);
    
    TerminateTask();
    
}

static int C;
static int alive =0;

TASK(tsk_led)
{
    C = C+1;
    
      char display[sizeof(int)*8+1];
      itoa(C,display,10);
      UART_LOG_PutString(display);
      if (C == 10) CancelAlarm(alrm_led);
    
    alive = 1;
    
 /*   RED_PIN_Write(1);
    CyDelay(500);
    RED_PIN_Write(0);
    CyDelay(500);
    
  */  
  //  CyWdtClear();
    TerminateTask();
}

TASK(tsk_background)
{
   while(1)
    {
     //CyWdtStart(CYWDT_1024_TICKS,CYWDT_LPMODE_NOCHANGE);  
      //  UART_LOG_PutString("task background");
      
        if (1 == alive)
        {
            CyWdtClear();
            alive = 0;
        }
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

/* [] END OF FILE */
