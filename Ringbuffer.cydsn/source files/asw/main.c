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
#include "ringbuffer.h"

ringbuffer_hdl_t myRingbuffer ={};
uint8_t single_letter;
uint8_t size;

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
 //   CounterTick(cnt_systick);
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
    UART_LOG_Start();
    Ringbuffer_Init(&myRingbuffer, uint32_t_MAX,&single_letter,10);
    
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the alarm with 100ms cycle time
    
   // UART_LOG_PutString("hello task");
    
   // UART_LOG_PutChar(s);
    
    ActivateTask(tsk_json);
    TerminateTask();
    
}

TASK(tsk_json)
{
 /*    EventMaskType ev = 0;
    
    void* data;
    while(1)
    {
    WaitEvent(ev_read);
    GetEvent(tsk_json,&ev);
    ClearEvent(ev);
    
    if(ev & ev_read)
    Ringbuffer_Read(&myRingbuffer,&data,5);
    }
   */
    
     EventMaskType ev = 0;
    uint8_t recieved_data;
   // char display[sizeof(int)*8+1];
    while(1)
    {
    WaitEvent(ev_read);
    GetEvent(tsk_json,&ev);
    ClearEvent(ev);
   
    if(ev & ev_read)
        {
            while(1)
            {
                RC_t ret = Ringbuffer_Read(&myRingbuffer,&recieved_data,5);               
                if(RC_SUCCESS != ret) 
                {
                    UART_LOG_PutString("\r");
                    break;
                }
                UART_LOG_PutChar(recieved_data);
                //CyDelay(10000);
            }
        
            
        
        }
    }
    
    
    
    
    
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


ISR2(ISR_Uart_RX)
{
   uint8_t sent_data;
    

    sent_data = UART_LOG_GetByte();
    
    if(sent_data=='0')
    {
        SetEvent(tsk_json,ev_read);
    }
    else
     //   RB_put(&myRingbuffer, sent_data);
    Ringbuffer_Write(&myRingbuffer,&sent_data,10);
    
}
/* [] END OF FILE */
