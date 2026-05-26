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

#include "button.h"
#include "led.h"
#include "seven.h"

#include "blinker.h"

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick); //application counter
}

int main()
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
        asm("bkpt");   
    }

}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    asm("bkpt");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_Init)
{
    
    //Init MCAL Drivers
    LED_Init();
    SEVEN_Init();
    
    //Init Complex Drivers and Applications
    BLINKER_Init(&BLINKER_left, BLINKER_LEFT);
    BLINKER_Init(&BLINKER_right, BLINKER_RIGHT);
    
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
    
    //Start the alarm with 100ms cycle time
    SetRelAlarm(alrm_100ms,100,100);
    SetRelAlarm(alrm_500ms,500,500);
    
    //Activate the remaining tasks
    ActivateTask(tsk_Control);
    ActivateTask(tsk_Background);
    
    TerminateTask();
    
}



/**
 * This task will c heck the input and based on this, "control" the output
 */
TASK(tsk_Control)
{
    
    EventMaskType ev = 0;
    while(1)
    {
        //Wait, read and clear the event
        WaitEvent(ev_100ms | ev_BlinkerButton1 | ev_BlinkerButton2);
        GetEvent(tsk_Control,&ev);
        ClearEvent(ev);

        //Check for left button
        if (TRUE == BUTTON_IsPressed(BUTTON_1))
        {
            BLINKER_Set(&BLINKER_left,1);
        }
        
        //Check for right button
        if (TRUE == BUTTON_IsPressed(BUTTON_2))
        {
            BLINKER_Set(&BLINKER_right,1);
        }
        

        //Check for emergency button
        if (TRUE == BUTTON_IsPressed(BUTTON_3))
        {
            BLINKER_Emergency(&BLINKER_left, &BLINKER_right);
        }
        
        //Check for otertake left
        if (ev & ev_BlinkerButton1)
        {
            BLINKER_Set(&BLINKER_left,5);
        }

        //Check for otertake right
        if (ev & ev_BlinkerButton2)
        {
            BLINKER_Set(&BLINKER_right,5);
        }
    
    }
}

/**
 * This task will c heck the input and based on this, "control" the output
 */
TASK(tsk_Output)
{
    BLINKER_Blink(&BLINKER_left);
    BLINKER_Blink(&BLINKER_right);
    
    //LED_Toggle(LED_GREEN);
    
    TerminateTask();
    
}


TASK(tsk_Background)
{
    while(1)
    {
        //do something with low prioroty
        asm("nop");
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/

ISR2(isr_Button)
{
    if (TRUE == BUTTON_IsPressed(BUTTON_1)) SetEvent(tsk_Control, ev_BlinkerButton1);
    if (TRUE == BUTTON_IsPressed(BUTTON_2)) SetEvent(tsk_Control, ev_BlinkerButton2);
}
/* [] END OF FILE */
