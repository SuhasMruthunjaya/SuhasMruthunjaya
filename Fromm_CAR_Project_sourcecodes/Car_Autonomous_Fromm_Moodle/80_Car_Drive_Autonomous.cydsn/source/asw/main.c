/* ========================================
 *
 * Copyright H-DA, Prof. P. Fromm, 2018ff
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF H-DA.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"

#include "logging.h"

#include "rte.h"
#include "rte_activation.h"
#include "rte_signalpool.h"

#include "swc_engine.h"
#include "swc_remote.h"
#include "swc_control.h"
#include "swc_ultrasonic.h"

#include "engine.h"
#include "ultrasonic.h"


ISR(systick_handler)
{
    CounterTick(cnt_systick);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
	EE_systick_start();
   
    // Start Operating System
    StartOS(OSDEFAULTAPPMODE);
    for(;;)
    {
        asm("nop");
    }
        
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
    
    //Init MCAL Drivers, which are not activated by the SWC_init routines
    UART_LOG_Start();
    
    //CDD Drivers, which are not activated by the SWC_init routines
    
    
    //Components
    ENGINE_init_run();
    REMOTE_init_run();
    US_init_run();
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
    
    LOG_I("tsk_Init", "Starting...\n");

    
    //Start the alarm with 1ms cycle time
    SetRelAlarm(alrm_1ms,1,1);
    
    //Tracealyser
    SetRelAlarm(alrm_trace,100,100);
 
    ActivateTask(tsk_EventDispatcher);
    ActivateTask(tsk_Background);
    
    //Initialise state machine and call initial state action. For this, the event task has to be up and running
    CONTROL_init_run();
    
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
    
        //Some stack analysis
        //uint8_t data = 0;
        //LOG_I("Stack extended task","%x",&data);
        
        //Process all events from the mask
        RTE_ProcessEventTable(RTE_eventActivationTable, RTE_eventActivation_size, ev);
        
    }
}

//Will be called every 1ms
TASK(tsk_CyclicDispatcher)
{
    
    //Some stack analysis
    //uint8_t data = 0;
    //LOG_I("Stack basic task","%x",&data);
    
    //Increment the age of all signals by 1ms
    RTE_timertick();   
    
    //Process all cyclic runnables which are due
    RTE_ProcessCyclicTable(RTE_cyclicActivationTable, RTE_cyclicActivation_size, 1);
    
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

ISR2(isr_UART_LOG_rx)
{

        
}


ISR2(isr_Xbee_rx)
{
    uint16_t error_data = UART_Zigbee_GetByte();
    uint8_t data = (uint8_t)error_data;
    uint8_t error = (uint8_t)(error_data >> 8);
    
    //static boolean_t preRun = TRUE;
    
    static uint8_t prevChar = 0;
    
    //LOG_I("rx","%x",data);

    //Check for transmission errors
    if (UART_Zigbee_RX_STS_PAR_ERROR & error || 
        UART_Zigbee_RX_STS_STOP_ERROR & error ||
        UART_Zigbee_RX_STS_OVERRUN & error)
    {
        return;
    }
    
    //Synchronise on first run
    if (FALSE == SIGNAL_PROTOCOL__SyncProtocol(data))
    {
        //ignore data
        return;
    }
    /*
    //Rule out invalid 0 characters upon reset - very hacky...
    if (preRun == TRUE && data == 0)
    {
        //Ignore data
        return;
    }
    else
    {
        preRun = FALSE;
    }
    */
    
    RC_t result = Ringbuffer_Put(&REMOTE_rx_buffer,data);
    if (PROT_EOP1 == prevChar && PROT_EOP2 == data)
    {
        //Complete protocol
        SetEvent(tsk_EventDispatcher, ev_isr_protocolBufferComplete);
        prevChar = 0;
        
    }
    else
    {
        prevChar = data;
    }
}

volatile uint32_t TIME_FRONT = 0;
volatile uint32_t TIME_REAR = 0;

ISR1(isr_sw_tick)
{
    TIME_FRONT += 100;
    TIME_REAR += 100;
}

ISR1(isr_US_Timer_Front_Start)
{
    TIME_FRONT = 0;
    
    Pin_Toggle_Write(1);
}

ISR1(isr_US_Timer_Rear_Start)
{
    TIME_REAR = 0;
}


ISR2(isr_US_Timer_Front_Stop)
{
    
    uint32_t dt =  TIME_FRONT;
    uint16_t distance = 0;
    
    Pin_Toggle_Write(0);
    
    SIGNAL_ULTRASONICSENSOR_data_t us_front = RTE_SIGNAL_ULTRASONICSENSOR_get(&SO_USFRONT_signal);

    us_front.m_distance = US_calcDistance(dt);
    us_front.m_status = US_ISVALID;
    
    RTE_SIGNAL_ULTRASONICSENSOR_set(&SO_USFRONT_signal, us_front);

}

ISR2(isr_US_Timer_Rear_Stop)
{
    
    uint32_t dt =  TIME_REAR;
    uint16_t distance = 0;
    
    SIGNAL_ULTRASONICSENSOR_data_t us_rear = RTE_SIGNAL_ULTRASONICSENSOR_get(&SO_USREAR_signal);

    us_rear.m_distance = US_calcDistance(dt);
    us_rear.m_status = US_ISVALID;
    
    RTE_SIGNAL_ULTRASONICSENSOR_set(&SO_USREAR_signal, us_rear);

}

/* [] END OF FILE */


