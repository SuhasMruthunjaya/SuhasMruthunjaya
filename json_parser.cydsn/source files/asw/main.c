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
#include "global.h"
#include "ringbuffer.h"
#include "parser.h"
#include "drawer.h"
#include "message.h"

#define POSTBOX_SIZE 10;
RB_t myRingbuffer;
MSG_messagebox_t mymessage; 

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
    EventMaskType ev = 0;
    RB_init(&myRingbuffer,200);
    MSG_init(&mymessage,10,ev_msg_send,tsk_hmi);
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();  
	
    //Start the alarm with 100ms cycle time
    ActivateTask(tsk_background);
    ActivateTask(tsk_json);
    ActivateTask(tsk_hmi);
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


TASK(tsk_json)
{
    EventMaskType ev = 0;
    uint8_t recieved_data;
    Parser_t p;
    Drawer_t drawer_object;
    
    
    PARSER_init(&p);

    char display[sizeof(int)*8+1];
    while(1)
    {
    WaitEvent(ev_endofstr);
    GetEvent(tsk_json,&ev);
    ClearEvent(ev);
    
    
    if(ev & ev_endofstr)
        {   
            // Gets inside the loop if there is data present in the Ringbuffer
            while(if_RB_data_present(&myRingbuffer))
            {
            while(1)
            {
                RC_t ret = RB_get(&myRingbuffer,(unsigned char*)&recieved_data);               
                //if the recieved data is null character, break the recieve operation
                if(recieved_data == '\0') 
                {
                   
                    break;
                    
                }
                
                // Adds the recieved data into a content Array.
                PARSER_addChar(&p,recieved_data);
            }
           
            
            PARSER_dbg_printContent(&p);
  
            PARSER_parse(&p);
            UART_LOG_PutString("\r");
            PARSER_dbg_printToken(&p);
            
            // Passes the drawer objects into the Message buffer .
            // Loops till the end of tokens in a given JSON command.
            while(p.token[p.nextToken+1].type!=JSMN_UNDEFINED)
                {
                    DRAWER_getNextDrawCommand(&drawer_object,&p);
                    MSG_sendMessage(&mymessage,&drawer_object,sizeof(drawer_object));
                }
            
            PARSER_clear(&p);
             
            } 
        }
    }
}
    
    
    
TASK(tsk_hmi)
{
    
    Drawer_t drawer_object_recieve;
   
    while(1)
    {   
       RC_t ret = MSG_waitNextMessage(&mymessage);

        if(ret==RC_SUCCESS)
         {
           //receive the drawer objects from the Message buffer if there is still
           // message objects present in the buffer. 
           while(if_data_present(&mymessage))
           {
            MSG_receiveMessage(&mymessage,&drawer_object_recieve,sizeof(drawer_object_recieve));
            printdbg_msg(&drawer_object_recieve);
           }
         }
    }
    
}




/********************************************************************************
 * ISR Definitions
 ********************************************************************************/
RB_content_t data=0;

ISR2(ISR_Uart_RX)
{
    uint8_t sent_data;
    sent_data = UART_LOG_GetByte();
    
        if(sent_data=='\0')
    {   
        RC_t ret = RB_put(&myRingbuffer, sent_data);
        if(RC_SUCCESS!=ret)
        {
            UART_LOG_PutString("RC_ERROR_BUFFER_FULL");
        }
        SetEvent(tsk_json,ev_endofstr);
    }
    else
    {
       RC_t ret = RB_put(&myRingbuffer, sent_data);
       if(RC_SUCCESS!=ret)
        {
            UART_LOG_PutString("RC_ERROR_BUFFER_FULL");
        }
        
    }
}

/* [] END OF FILE */
