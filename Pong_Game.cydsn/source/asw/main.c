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



ISR(systick_handler)
{
 CounterTick(cnt_systick);
}

int main()
{
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


TFT_init();


 //Reconfigure ISRs with OS parameters.
 //This line MUST be called after the hardware driver
 //initialization!
 EE_system_init();
 // Must be started after interrupt reconfiguration
 EE_systick_start();

ActivateTask(tsk_bat);

SetRelAlarm(alarm_10ms,1,10);

}

TASK(tsk_bat)
{
    PONG_GAME_t pong;
    
    //Init the kids (incl. screen)
    //Draw the game specific background
    PONG_init(&pong);
    
    
    //On the longrun Option 1
    //PONG_GAME_t pong;
    //SOCCER_GAME_t soccer;
    //if game_selection == pong 
    //{ 
    //  PONG_init(pGame); }
    //else if game_selection == soccer
    //{ 
    //  SOCCER_init(pGame); }
    
    
    //On the longrun Option 2 (we only need memory for one object at a time)
    //if game_selection == pong 
    //{ PONG_GAME_t* pGame = (PONG_GAME_t)malloc(sizeof(PONG_GAME_t));
    //  PONG_init(pGame); }
    //else if game_selection == soccer
    //{ SOCCER_GAME_t* pGame = (SOCCER_GAME_t)malloc(sizeof(PONG_GAME_t));
    //  SOCCER_init(pGame); }
    

 //   BAT_t bat;
 //   BALL_t ball;
  
    Cordinate_t pos = {10 , 20};
    SPEED_t ball_speed = {1,1};
 //   JOYSTICK_t joystick;
    SCREEN_t screen;


    BAT_init(&pong.bat, 50);
    BALL_init(&pong.ball, pos, ball_speed);
    
   // PONG_init(&pong,&joystick,&pong.bat,&pong.ball);
    
    SCREEN_init(&screen, &pong.bat, &pong.ball);
  
    SCREEN_update(&screen);
        
    EventMaskType ev = 0;
    
    while(1)
    {
    WaitEvent(ev_10ms);
    GetEvent(tsk_bat,&ev);
    ClearEvent(ev);
    
    if (ev & ev_10ms)
    {         
    
        PONG_play(&pong);
        
        SCREEN_update(&screen);
        
     /*   
        JOYSTICK_update(&joystick);  
        BAT_update_pos(&bat,joystick);
        
        BALL_update_pos(&ball);
        
        SCREEN_update(&screen);
      */  
    }
    }
    TerminateTask();
   
}


/*****************************************************       
        //Input
  //      JOYSTICK_get(&joystick);
        
        //Logic Some math

        
  //      BAT_updatePosition(&bat, &joystick);
        
        //output
  //      SCREEN_update(&screen, &bat);
        
********************************************************/
/*****************************************************         
        
       Joystick_update(&joystick);
    
       //option 1
        pos = JOYSTICK_getPosition(&joystick);
        BAT_move(&bat, pos);
        
        SCREEN_update(&screen);
        
        //Option 2
        BAT_move(&bat, &joystick);
 
*****************************************************/ 

TASK(tsk_background)
{
    while(1)
    {
        __asm("nop");
    }
}


/* [] END OF FILE */


/* [] END OF FILE */
