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

/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "project.h"
#include "global.h"
#include "stdlib.h"
//#include "tft.h"
#include "joystick.h"
#include "screen.h"
#include "pong.h"
#include "button.h"
#include "logging.h"
#include "Event_Ringbuffer.h"
#include "statemachine.h"
#include "seven.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/
#define PongGameLife    3
/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static PONG_GAME_t PONG_object = {};
STATE_state_t Pong_StateVar;

static RB_t PONG_EV_Ringbuffer;


/* Action */
static void PONG__ClearLife();
static void PONG__ShowWelcomeMsg();
static void PONG__ShowGameScore();
static void PONG__DecrementLife();
static void PONG__ShowLoosingMessage();
static void PONG__LifeScoreInit();
static void PONG__ClearLife();

/* Guard*/
static boolean_t NotGameOver();
static boolean_t GameOverAndLifeRemain();
static boolean_t GameOverAndNoLifeRemain();
static boolean_t LifeRemain();
static boolean_t NoLifeRemain();

/*****************************************************************************/
/* Local const table ('static')                                      */
/*****************************************************************************/

/** ---------------------------------- Transitions ---------------------------------------- **/

/**  ===== PONG_IS_STARTING ====   */
static const STATE_stateInnerTransitionTable_t PONG_IS_STARTING_Transitions = {
/*    Event                      ToState                 Guard               Action                       */
    { PONG_EV_BUTTON_START,      PONG_IS_PLAYING,       0,                 PONG_init}, 
};

/**  ===== PONG_IS_PLAYING ====   */
static const STATE_stateInnerTransitionTable_t PONG_IS_PLAYING_Transitions = {
/*    Event                   ToState                 Guard                       Action                       */
    { PONG_EV_TICK,           PONG_IS_PLAYING,        NotGameOver,                PONG_play}, 
    { PONG_EV_TICK,           PONG_IS_GAMEOVER,       GameOverAndLifeRemain,      PONG__ShowLoosingMessage},
    { PONG_EV_TICK,           PONG_IS_GAMEOVER,       GameOverAndNoLifeRemain,    PONG__ShowGameScore},
};

/**  ===== PONG_IS_GAMEOVER ====   */
static const STATE_stateInnerTransitionTable_t PONG_IS_GAMEOVER_Transitions = {
/*    Event                   ToState                 Guard                       Action                       */
    { PONG_EV_BUTTON_START,   PONG_IS_PLAYING,         LifeRemain,                PONG_init}, 
    { PONG_EV_BUTTON_START,    PONG_IS_STARTING,       NoLifeRemain,              PONG__ClearLife},
};


static const STATE_stateOuterTransitionTable_t PongStateMachine_Transitions = {
/*    fromState             Pointer to table                    Size of table [Elements]    */
    { PONG_IS_STARTING,    &PONG_IS_STARTING_Transitions,     sizeof(PONG_IS_STARTING_Transitions)/sizeof(STATE_stateInnerTransition_t)    },
    { PONG_IS_PLAYING,      &PONG_IS_PLAYING_Transitions,       sizeof(PONG_IS_PLAYING_Transitions)/sizeof(STATE_stateInnerTransition_t)      },
    { PONG_IS_GAMEOVER,     &PONG_IS_GAMEOVER_Transitions,      sizeof(PONG_IS_GAMEOVER_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
};
static const uint16_t PongStateMachine_Transitions_size = sizeof(PongStateMachine_Transitions)/sizeof(STATE_stateOuterTransition_t);

/** ---------------------------------- Action ------------------------------------------- **/

static const STATE_stateActionTable_t PongStateMachine_StateActions = {
/*  fromState               Entry                    Exit    */
  { PONG_IS_STARTING,      PONG__ShowWelcomeMsg,      PONG__LifeScoreInit},
  { PONG_IS_PLAYING,       0,                         0   }, 
  { PONG_IS_GAMEOVER,       0,                        0 },
};
static const uint16_t PongStateMachine_StateActions_size = sizeof(PongStateMachine_StateActions)/sizeof(STATE_stateAction_t);


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/*********************** State machine Actions ******************************************/
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
static void PONG__ClearLife()
{
  SEVEN_Init();
}

static void PONG__DecrementLife()
{
  //UART_LOG_PutString("PONG__DecrementLife\r"); 
  PONG_object.life--;
  SEVEN_Set(SEVEN_1, PONG_object.life); 
}

static void PONG__ShowWelcomeMsg()
{
  SCREEN_PongShowWelcomeMessage();
}
static void PONG__ShowLoosingMessage()
{
  PONG__DecrementLife();
  //UART_LOG_PutString("PONG__ShowLoosingMessage\r");
  SCREEN_PongShowLoosingLife();
}

static void PONG__ShowGameScore()
{
  PONG__DecrementLife();
  PONG_object.score = PONG_object.score/6; // In Pong logic, the is ball hitting bat once is counted 6 times
  SCREEN_PongShowGameScore(PONG_object.score);
}
static void PONG__LifeScoreInit()
{
  PONG_object.life=PongGameLife;
  SEVEN_Set(SEVEN_1, PONG_object.life); 
  PONG_object.score=0;
}
/*********************** State machine Actions ******************************************/

/*********************** State machine Gaurds ******************************************/
static boolean_t NotGameOver()
{
  //UART_LOG_PutString("NotGameOver\r"); 
    if (PONG_BallReachedBoundary()== PONG_BOUNDARY_GAME_OVER_SPOT)
    {
        return FALSE;
    }
    else 
    {
        return TRUE;
    }
}
static boolean_t GameOverAndLifeRemain()
{
  //UART_LOG_PutString("GameOverAndLifeRemain\r");
    if (PONG_BallReachedBoundary()== PONG_BOUNDARY_GAME_OVER_SPOT && PONG_object.life>1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
static boolean_t GameOverAndNoLifeRemain()
{
  //UART_LOG_PutString("GameOverAndNoLifeRemain\r");
  
  if (PONG_BallReachedBoundary()== PONG_BOUNDARY_GAME_OVER_SPOT && PONG_object.life==1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static boolean_t LifeRemain()
{
    //UART_LOG_PutString("LifeRemain\r");
    if(PONG_object.life>0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
    
}
static boolean_t NoLifeRemain()
{
    //UART_LOG_PutString("NoLifeRemain\r");
    if(PONG_object.life==0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
    
}

/*********************** State machine Gaurds ******************************************/

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/
/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
*/
static RC_t PONG__BallBounceLogic();

/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
*/
static RC_t PONG__logic();

/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
*/
static RC_t PONG__Control();

 
/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
void PONG_init()
{
    TFT_clearScreen(); //can be moved to screen file?
    //Creating some local values required for the init functions
    Cordinate_t pos = {10 , 20};
    SPEED_t ball_speed = {1,1};


    //Initialisaing the BAT part of the PONG_object
    BAT_init(&PONG_object.bat, 50);
    
    //Initialisaing the BALL part of the PONG_object
    BALL_init(&PONG_object.ball, pos, ball_speed);
    
    //Initialisaing the SCREEN part of the PONG_object
    SCREEN_init(&PONG_object.screen, &PONG_object.bat, &PONG_object.ball);
    SCREEN_update(&PONG_object.screen);    
    
    //The joystick part will be updated by the driver, so no need for an explizit initialisation
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
void PONG_play()
{
    PONG__logic();
    SCREEN_update(&PONG_object.screen);
}

/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
*/
static RC_t PONG__logic()
{
    JOYSTICK_update(&PONG_object.joystick);  
    BAT_update_pos(&PONG_object.bat,&PONG_object.joystick);
        
    PONG__BallBounceLogic(); 
        
    BALL_update_pos(&PONG_object.ball);
        
    return RC_SUCCESS;
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t PONG_cyclic()
{
    
    //Prepare events
    static ButtonPressStates_t StartButtonStateVar = IDLE;
    uint16 EV  = PONG_EV_NULL;
    
    BUTTON1_CheckShortPress(&StartButtonStateVar, &EV , PONG_EV_BUTTON_START);
    
    //put in ring buffer
    if(EV== PONG_EV_BUTTON_START)
    {
        RB_put(&PONG_EV_Ringbuffer ,(uint8_t)PONG_EV_BUTTON_START);//write into the buffer
    }
    
    RB_put(&PONG_EV_Ringbuffer ,(uint8_t)PONG_EV_TICK);//write into the buffer

    
    //call process event until ringbuffer is empty
    PONG__Control();
    
    
}

/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
*/
static RC_t PONG__Control()
{
    uint8_t EV;
    //call process event until ringbuffer is empty
   while(RB_prots_available(&PONG_EV_Ringbuffer))//read all the remaining protocols available in the RingBuffer 
   {
      RC_t ret= RB_get(&PONG_EV_Ringbuffer, &EV);
    switch(EV)
    {
        case PONG_EV_NULL: 
        {
          //UART_LOG_PutString("PONG_EV_NULL \r"); 
        }
        break;
        
        case PONG_EV_BUTTON_START: 
        {
          //UART_LOG_PutString("PONG_EV_BUTTON_START \r"); 
        }
        break;
        case PONG_EV_TICK: 
        {
          //UART_LOG_PutString("PONG_EV_TICK \r"); 
        }
        break;
    }
    
        if (ret == RC_SUCCESS)
        {
            STATE_processEvent(PongStateMachine_Transitions,
                        PongStateMachine_Transitions_size,
                        PongStateMachine_StateActions, 
                        PongStateMachine_StateActions_size,
                        (PONG_event_t)EV,
                        &Pong_StateVar);    
        }
    
        else
        {
        return RC_ERROR;  
        }
    
   }
    return RC_SUCCESS;
    
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */    
RC_t Pong_InitState()
{
   RB_init(&PONG_EV_Ringbuffer, 50);
   STATE_initState( PongStateMachine_StateActions , 
                        PongStateMachine_StateActions_size,
                        &Pong_StateVar, PongStateMachine_INIT_DATA);  
    return RC_SUCCESS;
}
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
PONG_BOUNDARY PONG_BallReachedBoundary()
{
    PONG_BOUNDARY res= PONG_BOUNDARY_none;

    //Checking for a normal boundary situation
    if (PONG_object.ball.current_ball_pos.Y >= (SCREEN_WIDTH - BALL_WIDTH))    
    {
        res=PONG_BOUNDARY_right;
    }
    else if(PONG_object.ball.current_ball_pos.X >= (SCREEN_HEIGHT - BALL_WIDTH))
    {
        res = PONG_BOUNDARY_up;
    }
    else if (PONG_object.ball.current_ball_pos.Y <= 0)
    {
        res = PONG_BOUNDARY_left;
    }
    else if((PONG_object.ball.current_ball_pos.X <= BALL_WIDTH)&&(PONG_object.bat.current_bat_pos <= PONG_object.ball.current_ball_pos.Y) && (PONG_object.ball.current_ball_pos.Y <= (PONG_object.bat.current_bat_pos + BAT_HEIGHT) ))
    {
        PONG_object.score++;
        res = PONG_BOUNDARY_down;
    }
    
    //Check for special cases, overwriting the normal boundary
    if(( PONG_object.ball.current_ball_pos.X <= BALL_WIDTH)&&
    ((PONG_object.bat.current_bat_pos > PONG_object.ball.current_ball_pos.Y) || 
    (PONG_object.ball.current_ball_pos.Y > (PONG_object.bat.current_bat_pos + BAT_HEIGHT) )))
    {  
       res = PONG_BOUNDARY_GAME_OVER_SPOT;
       
    }
 
    return res;
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
static RC_t PONG__BallBounceLogic()
{
 if(PONG_BallReachedBoundary() == PONG_BOUNDARY_right)
    {
        BALL_flipYSpeed(&PONG_object.ball);
        
    }
    if(PONG_BallReachedBoundary() == PONG_BOUNDARY_left)
    {
        BALL_flipYSpeed(&PONG_object.ball);
        
    }
    if(PONG_BallReachedBoundary() == PONG_BOUNDARY_up)
    {
        BALL_flipXSpeed(&PONG_object.ball);
        
    }
    

   if(PONG_BallReachedBoundary() == PONG_BOUNDARY_down)
    {
        BALL_flipXSpeed(&PONG_object.ball);
        
    }
 if(PONG_BallReachedBoundary() == PONG_BOUNDARY_GAME_OVER_SPOT)
    {
        
        BALL_STOP(&PONG_object.ball);
        
    }
    return RC_SUCCESS; 
}
  
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */    
RC_t Pong_DeInit()
{
   RB_deinit(&PONG_EV_Ringbuffer);
   PONG__ClearLife();
   return RC_SUCCESS;
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t PONG_show_menu()
{
    TFT_clearScreen();
    TFT_setTextColor(YELLOW);
    TFT_setTextSize(1);
    TFT_setCursor(5,10);
    TFT_print("Welcome to PONG Game");
    TFT_writeLine(0, 30, 128, 30, YELLOW);
    TFT_setCursor(40,50);
    TFT_print("Press B.1");
    TFT_setCursor(0,70);
    TFT_print("for starting the game"); 
    TFT_writeLine(0,90,128,90,YELLOW);
    TFT_setCursor(10,110);
    TFT_print("The number of life"); 
    TFT_setCursor(10,130);
    TFT_print("will be displayed"); 
    TFT_setCursor(40,150);
    TFT_print("on 7seg "); 
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t PONG_LoosingLifeMsg()
{
    TFT_clearScreen();
    TFT_setTextColor(YELLOW);
    TFT_setTextSize(1);
    TFT_setCursor(20,35);
    TFT_print("You lost 1 life");
    TFT_setCursor(20,60);
    TFT_print("To Continue");
    TFT_setCursor(20,80);
    TFT_print("Press B.1");
    TFT_setCursor(20,100);
    TFT_print("To Exit the Game");
    TFT_setCursor(20,120);
    TFT_print("Press B.3");
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t PONG_LoosingGameMsg()
{
    TFT_clearScreen();
    TFT_setTextColor(RED);
    TFT_setTextSize(2);
    TFT_setCursor(10,25);
    TFT_print("Game Over");
    TFT_setTextSize(1);
    TFT_setTextColor(YELLOW);
    TFT_setCursor(20,60);
    TFT_print("For restarting");
    TFT_setCursor(20,80);
    TFT_print("Press B.1");
    TFT_setCursor(20,100);
    TFT_print("To Exit the Game");
    TFT_setCursor(20,120);
    TFT_print("Press B.3");
}

