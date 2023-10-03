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
#include "CAN.h"
#include "stdlib.h"
#include "logging.h"

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
    
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

TASK(tsk_init)
{

    
    //Init MCAL Drivers
    CAN_Init();
    UART_LOG_Start();
    CAN_Start();
    CAN_Enable();
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start(); 
    
//    UART_LOG_PutString("Hello init");
    
    SetRelAlarm(alrm_cyclic,1,500);
    
    ActivateTask(tsk_cyclic);
	
    ActivateTask(tsk_background);
    
    TerminateTask();
    
}

TASK(tsk_cyclic)
{
 static uint8_t count = 0;
    
 //LOG_I("UART","%d",count);
 
 count++;
 
 //Setup payload
 CAN_DATA_BYTES_MSG payload = {0,0,0,0,0,0,0,0};
 //UART_LOG_PutString("Hello cyclic");
 payload.byte[0] = 00;
 payload.byte[1] = 11;
 payload.byte[2] = 22;
 payload.byte[3] = 33;
 payload.byte[4] = 44;
 payload.byte[5] = 55;
 payload.byte[6] = 66;
 payload.byte[7] = 77;

 //Set up message
 CAN_TX_MSG msg;
 msg.id = 0x100; //CobId
 msg.ide = 0; //11bit identifier (else 29)
 msg.rtr = 0; //Normal message
 msg.dlc = 8; //Length
 msg.msg = &payload; //Data to be transmitted
 
 CAN_SendMsg(&msg);
 
 TerminateTask();
}

void can_rx_basic_cb(uint8_t mailbox)
{
 CAN_DATA_BYTES_MSG payload = {0,0,0,0,0,0,0,0};
 //Get the metadata of the message
 uint16_t cobid = CAN_GET_RX_ID(mailbox);
 uint8_t len = CAN_GET_DLC(mailbox);
 
 //Read in the payload
 for (uint8_t i = 0; i < len; i++)
 {
 payload.byte[i] = CAN_RX_DATA_BYTE(mailbox, i);
 }

//if(cobid == 0x100)
{
UART_LOG_PutString("in receive func");
LOG_I("CAN RX","%x [%d] %x %x %x %x %x %x %x %x\r", cobid, len, 
payload.byte[0], payload.byte[1], payload.byte[2], payload.byte[3], 
payload.byte[4], payload.byte[5], payload.byte[6], payload.byte[7]); 
} 
}

TASK(tsk_background)
{
    while(1)
    {
             
    }
}



/* [] END OF FILE */
