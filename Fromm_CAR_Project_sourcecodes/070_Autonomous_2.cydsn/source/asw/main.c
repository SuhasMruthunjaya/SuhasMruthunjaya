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
#include "logging.h"

#include "tsk_io.h"
#include "tsk_control.h"
#include "tsk_system.h"

#include "engine.h"
#include "engine_cfg.h"
#include "tft.h"

#include "ringbuffer.h"
#include "statemachine.h"

#include "sc_protocol_type.h"

#include "swc_control.h"

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick);
}


/**
 * This function will activate all tasks / events which are called in a 1ms context
 * Alternatively, we would have to create an own alarm for each
 **/
void callback_1ms()
{
    ActivateTask(tsk_system);
    SetEvent(tsk_io, ev_tick_1ms);
    SetEvent(tsk_control, ev_tick_1ms);
    
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

    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
    
    //Start application peripherals
    
    UART_LOG_Start();
    
    ENG_init(&ENG_RR);
    ENG_init(&ENG_RL);
    ENG_init(&ENG_FR);
    ENG_init(&ENG_FL);
    
    TFT_init();
    TFT_setBacklight(255);
    
    TFT_print("   CAR 6\n");
    

    //Init Ringbuffer for XBee RX and Start XBee
    Ringbuffer_Init(&PROTOCOL_rx_buffer,0,PROTOCOL_uartBuffer,PROTOCOL_SIZERXBUF);
    XBee_Start();
    
    //Start the alarm with 100ms cycle time
    SetRelAlarm(alrm_1ms,1,1);
     
    //Activate extended tasks
    ActivateTask(tsk_control);
    ActivateTask(tsk_io);
    
    //Basic tasks are called from 1ms callback above
    
    ActivateTask(tsk_background);
    
    //Call the State machine Init Task Actions
    STATE_initState(&CONTROL_ConnectionFSM);
    
    LOG_I("Main", "Starting CAR VI");
    LOG_I("DIAG", "r to read diagnostics buffer");
    LOG_I("DIAG", "c to clear diagnostics buffer");
    
    TerminateTask();
    
}



TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

/* [] END OF FILE */

