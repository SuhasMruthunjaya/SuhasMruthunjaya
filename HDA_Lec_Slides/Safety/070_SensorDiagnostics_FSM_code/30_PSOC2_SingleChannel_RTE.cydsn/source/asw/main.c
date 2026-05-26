/**
* \file main
* \author OPeter Fromm
* \date 5.12.2019
*
* \brief Demonstrator for critical regions
*
* The file contains two cyclic tasks, whioch both access the same UART to create a critical region
* Depending on priority and timing configuration, the data may get corrupted.
*
* \note <notes>
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/


#include "project.h"
#include "global.h"
#include "trcRecorder.h"

#include "logging.h"

#include "poti.h"
#include "engine.h"
#include "ssd1306.h"

#include "rte.h"
#include "rte_activation.h"
#include "rte_signalpool.h"




//Global handles for Tracealyser
//traceHandle TRC_SystickHandle;
//traceHandle TRC_ISRButtonHandle;

#undef TRC_SYSTICK

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
#ifdef TRC_SYSTICK
    vTraceStoreISRBegin(TRC_SystickHandle);
#endif   
    
    CounterTick(cnt_systick);

#ifdef TRC_SYSTICK
    vTraceStoreISREnd(0);
#endif   

}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
    
    //Enable trace
    vTraceEnable(TRC_INIT);
    //TRC_SystickHandle = xTraceSetISRProperties("SysTick", 1);
    ///TRC_ISRButtonHandle = xTraceSetISRProperties("ISR_Button", 1);
   
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

TASK(tsk_Init)
{
    
    RC_t result;
    
    //Init MCAL Drivers
    //UART_LOG_Start();
    LOG_Init();
    
    result = POTI_Init();
    result = ENG_Init();
    
        
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	EE_systick_start();
    
    I2C_Start();
    result = SSD1306_init();
    
    LOG_I("tsk_Init", "Starting...\n");

    
    //Start the alarm with 10ms cycle time
    SetRelAlarm(alrm_10ms,10,10);
    
    //Tracealyser
    SetRelAlarm(alrm_trace,100,100);
 
    ActivateTask(tsk_EventDispatcher);
    ActivateTask(tsk_Background);
    
    TerminateTask();
    
}


TASK(tsk_EventDispatcher)
{
    EventMaskType ev = 0;
    
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(RTE_EVENTMASK);
        GetEvent(tsk_EventDispatcher,&ev);
        ClearEvent(ev);
    
        //Process all events from the mask
        RTE_ProcessEventTable(RTE_eventActivationTable, RTE_eventActivation_size, ev);
        
    }
}

//Will be called every 10ms
TASK(tsk_CyclicDispatcher)
{
    //Increment the age of all signals by 1ms
    RTE_timertick();   
    
    //Process all cyclic runnables which are due
    RTE_ProcessCyclicTable(RTE_cyclicActivationTable, RTE_cyclicActivation_size, 10);
    
}

TASK(tsk_Background)
{
    while(1)
    {
        //do something with low priority
        asm("nop");
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/


ISR2(isr_Button)
{
    /*
    vTraceStoreISRBegin(TRC_ISRButtonHandle);

    if (BUTTON_1_Read() == 1) SetEvent(tsk_event,ev_Button_1);   
    if (BUTTON_2_Read() == 1) SetEvent(tsk_event,ev_Button_2);   
    if (BUTTON_3_Read() == 1) SetEvent(tsk_event,ev_Button_3);   
    if (BUTTON_4_Read() == 1) SetEvent(tsk_event,ev_Button_4);   
    
    vTraceStoreISREnd(0);
    */
}

ISR1(I2C_I2C_IRQ)
{
    I2C_ISR();
}

/* [] END OF FILE */
