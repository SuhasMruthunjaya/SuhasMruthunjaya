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
#include "tft.h"
#include "joystick_adc.h"
#include "joystick.h"
#include "stdlib.h"
#include "screen.h"
#include "pong.h"
#include "game.h"
#include "menu.h"



ISR(systick_handler)
{
 CounterTick(cnt_systick);
}

int main()
{
int counter;

//Set systick period to 1 ms. Enable the INT and start it.
EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
EE_systick_enable_int();
CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
 
 // Start Operating System








 for(;;)
 StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

void cb_tick()
{
    GAME_set_event(GAME_EV_TICK);
    //Testing
    //UART_LOG_PutString("GAME_EV_TICK is being activated\n") ;  
}
ISR2(isr_Button)
    {
        if (BUTTON_1_Read()==1) 
        {
            GAME_set_event(GAME_EV_BUTTON_START);
       //UART_LOG_PutString("start button is pressed\n") ;
        
        }
        if (BUTTON_2_Read()==1) 
        {
           GAME_set_event(GAME_EV_BUTTON_UP);
       //UART_LOG_PutString("stop button is pressed\n") ;
        
        }
        if (BUTTON_3_Read()==1) 
        {
            GAME_set_event(GAME_EV_BUTTON_STOP);
       //UART_LOG_PutString("start button is pressed\n") ;
        
        }
        if (BUTTON_4_Read()==1) 
        {
            GAME_set_event(GAME_EV_BUTTON_DOWN);
       //UART_LOG_PutString("start button is pressed\n") ;
        
        }
    }
    

/*********************************************************************
***********
* Task Definitions
**********************************************************************
**********/


TASK(tsk_init)
{

 //Init MCAL Drivers
 
UART_LOG_Start();
JOYSTICK_ADC_Init();
CAN_Start();

TFT_init();


 //Reconfigure ISRs with OS parameters.
 //This line MUST be called after the hardware driver
 //initialization!
 EE_system_init();
 // Must be started after interrupt reconfiguration
 EE_systick_start();

ActivateTask(tsk_game);
ActivateTask(tsk_background);
SetRelAlarm(alarm_10ms,10,10);
TerminateTask();
}


TASK(tsk_game)
{
       
    EventMaskType ev = 0;
    GAME_event_t gameEv = GAME_EV_NONE;
  
    MENU_init();
    
    //GAME_show_menu();
    GAME_InitState();
    //Pong_InitState();
    
    while(1)
    {
        WaitEvent(ev_newGameEvent);
        GetEvent(tsk_game,&ev);
        ClearEvent(ev);
        
        
        if (ev & ev_newGameEvent)
        {         
            gameEv = GAME_get_event();
 
            //RC_t res = GAME_process_event(gameEv);
            GAME_process_event(gameEv);
            
        }
    }
    
   TerminateTask();
}


 
//*****************************************************

TASK(tsk_background)
{
    while(1)
    {
        __asm("nop");
    }
}


/* [] END OF FILE */


/* [] END OF FILE */
