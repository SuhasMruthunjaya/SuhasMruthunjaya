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

#include "global.h"
#include "game.h"
#include "project.h"
#include "stdlib.h"
#include "seven.h"


/* A static variable Game_round is used to know at which round we are in. Reaction 
   game consits of 10 rounds*/
static uint8_t Game_round=1;

const RG__Glow_t RG_glowtable[] = {
//Red Green Blue TimeInMS
{255, 0, 0, 500},
{0, 255, 0, 500},
{0, 0, 255, 500},
{0, 0, 0, 100},
{255, 255, 255, 100},
{0, 0, 0, 100},
{255, 255, 255, 100},
{0, 0, 0, 100},
{255, 255, 255, 100}
};

/* 
    Sets the Red, green, and blue pins in the RGB 
    @param RG__Glow_t value - It is of type struct RG__Glow_t, each 
    elements in the constant RG_glowtable[] array is passed into this 
    function at a time and red, blue,green RGB Led is set
*/

void rgb (RG__Glow_t value)
{
    Pin_RGB_RED_Write(value.RED);
    Pin_RGB_Green_Write(value.Green);
    Pin_RGB_Blue_Write(value.Blue);
   // CyDelay(value.time);
   
   /* Alarm starts at value.time ms, this acts as a delay required 
      to see the RGB functionality. */
    SetRelAlarm(alarm_rgb,value.time,value.time);
}

/*
    This function calls the rgb function for 9 times. (because there are 
    9 elements in the constant table).
*/

void rgb_glower_fun()
{
    if(glow_period<=8)
    {
       rgb(RG_glowtable[glow_period]);
       glow_period++;
    }
    else
    {
        glow_period=0;

    }

}

/*
    FADAR Function
*/

void fadar_fun()
{
    if(fadar_period > 1000)
    {
        fadar_period=0;
        red=0;
        green=0;
        yellow=0;
    }
    else
    {
    
    if((fadar_period>0) && (fadar_period<=250)) 
    {
        PWM_ledRed_WriteCompare(red++);
    }
        if((fadar_period>250) && (fadar_period<=500))
    {
        PWM_ledYellow_WriteCompare(yellow++);
      
    }
       if((fadar_period>250) && (fadar_period<=500))
    {
      
        PWM_ledRed_WriteCompare(red--);
    }
    
    
        if((fadar_period>500) && (fadar_period<=750))
    {
        PWM_ledYellow_WriteCompare(yellow--);
      
    }
           
        if((fadar_period>500) && (fadar_period<=750))
    {
      
        PWM_ledGreen_WriteCompare(green++);
    }
        if((fadar_period>750) && (fadar_period<=1000))
    {
        PWM_ledGreen_WriteCompare(green--);
    }
    
    fadar_period++;
    
    }
    
}

/*
    This function is called after the button is presed for the second time
    It calculates total score, Total reaction time and average reaction time 
    and prints it. It also prints whether the button pressed is the Correct
    one or not.
*/

void reaction_game_fun()
{
    char display[sizeof(int)*8+1];
    if((randomTime == 0) && (Button1_Read()==1))       
        { 
          score++;
          Total_Reaction_count += count;
          itoa(count,display,10);
          UART_LOG_PutString("\rCorrect Button. Reaction time (in ms): ");
          UART_LOG_PutString(display);
          Control_Reg_1_Write(0);
          UART_LOG_PutString("\rNext round: Press press one of the two buttons to start");
        }
        else if((randomTime == 1) && (Button2_Read()==1))
        {   
            
          score++;
          Total_Reaction_count += count;
          itoa(count,display,10);
          UART_LOG_PutString("\rCorrect Button. Reaction time (in ms): ");
          UART_LOG_PutString(display);
          Control_Reg_1_Write(0);
          UART_LOG_PutString("\rNext round: Press press one of the two buttons to start");
          
        }
        else
        {   
        
           // Total_Reaction_count += count;
            UART_LOG_PutString("\rWrong Button pressed ");
            Control_Reg_1_Write(0);
            game = GAME__ISIDLE;
            UART_LOG_PutString("\rNext round: Press press one of the two buttons to start");
        }
     }


/*
    This is the function which contains the state machine of the Reaction game.
*/

void GAME_Play(){
        
    switch(game)
        {
           case  GAME__ISIDLE: 
            {   
                if(Game_round<=10)
                {
                char display[sizeof(int)*8+1];
                UART_LOG_PutString("\rReaction Game round ");
                itoa(Game_round,display,10);
                UART_LOG_PutString(display);

                
                if((Button1_Read() == 1) || (Button2_Read() == 1))
                    Seven_segment_wait_time(variable_number);
                
                game = GAME_ISWAITINGBUTTON;
                Game_round++;    
              
                
                }
                else
                {
                 char display[sizeof(int)*8+1];
                 char Avg_display[sizeof(int)*8+1];
                 char score_display[sizeof(int)*8+1];
                 UART_LOG_PutString("\rEND OF THE GAME");
                 
                 
                 UART_LOG_PutString("\rPlease find your score: ");
                 itoa(score,score_display,10);
                 UART_LOG_PutString(score_display);
                
                 UART_LOG_PutString("\rTotal Reaction time (in ms): ");
                 itoa(Total_Reaction_count,display,10);
                 UART_LOG_PutString(display);
                
                 UART_LOG_PutString("\rAverage Reaction time (in ms): ");  
                 Average_Reaction_count = Total_Reaction_count/10;
                 itoa(Average_Reaction_count,Avg_display,10);
                 UART_LOG_PutString(Avg_display);
                }
            break;
            }
            
            
            case GAME_ISWAITINGBUTTON:
            {  
                CancelAlarm(alarm_count);
                if(count<1000)
                {
                if((Button1_Read() == 1) || (Button2_Read() == 1))
                SetEvent(tsk_ReactionGame,ev_buttonpress);
                }
                else
                {
                    UART_LOG_PutString("\rToo Slow");
                    Control_Reg_1_Write(0);
                    UART_LOG_PutString("\rNext round: Press press one of the two buttons to start");
                }
                
                game = GAME__ISIDLE;
                break;
            }

           }
}