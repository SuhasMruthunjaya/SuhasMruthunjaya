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
#include "stdlib.h"
#include "seven.h"
#include "led.h"
#include "game.h"


ISR(systick_handler)
{
 CounterTick(cnt_systick);
 // A static variable to be used at various places, the life time of this variable
 // is until the lifetime of the program.
 variable_number++;
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
 LED_Init();
 UART_LOG_Start();
 PWM_ledRed_Start();
 PWM_ledGreen_Start();
 PWM_ledYellow_Start();
 

 //Reconfigure ISRs with OS parameters.
 //This line MUST be called after the hardware driver
 //initialization!
 EE_system_init();
 // Must be started after interrupt reconfiguration
 EE_systick_start();


 /*Start the alarm with 1ms period cycle, This is used to activate and run
   the fadar Task. */
SetRelAlarm(alarm_ledRedblink,1,2);
 /*Start the alarm for only once, This is used to activate and run
   the Glower Task. */
SetRelAlarm(alarm_rgb,1,0);


 UART_LOG_PutString("\rPress one of the two buttons to start");
 ActivateTask(tsk_ReactionGame);
 TerminateTask();

}

/*This task calls the glower function*/
TASK(tsk_rgb)
{
 rgb_glower_fun();
 TerminateTask();
}


/*This task calls the fadar function*/
TASK(tsk_ledRedBlink)
{
   
    fadar_fun();
    TerminateTask();


}

/*This task calls the Reaction game function*/
TASK(tsk_ReactionGame)
{  
   
    EventMaskType ev = 0;
    while(1)
    {
    WaitEvent(ev_buttonpress);
    GetEvent(tsk_ReactionGame,&ev);
    ClearEvent(ev);
   
    if(ev & ev_buttonpress)
        {
            reaction_game_fun();
        }
        
    }
    TerminateTask();
}

/* This Task counts the reaction time from the time the number is displayed 
   in the seven segment to the button being pressed for the second time */
TASK(tsk_reactiontime)
{   
    count++;
    TerminateTask();
}

/* This Task calls a function to wait for a random time 1,2 or 3 seconds,
   after a button is pressed at the start of the game, before the number 
   is displayed on the seven segment */

TASK(tsk_seven_segment_display_wait)
{
   
    Seven_segment_button(variable_number);
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

ISR2(isr_button)
{       
   GAME_Play();
}




/* [] END OF FILE */
