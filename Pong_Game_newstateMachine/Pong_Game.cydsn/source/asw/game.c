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
#include "game.h"
#include "logging.h"
#include "tft.h"
#include "joystick_adc.h"
#include "joystick.h"
#include "stdlib.h"
#include "screen.h"
#include "pong.h"
#include "soccer.h"
#include "seven.h"
#include "ball.h"
#include "bat.h"
#include "position.h"
#include "menu.h"
#include "statemachine.h"
#include "game_cfg.h"
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/

static GAME_t GAME_object;
STATE_state_t Game_state;

//static GAME_cfg_t pong_cfg= {PONG_init, PONG_show_menu,PONG_cyclic};
GAME_CfgTable_t GAME_table= {
/*    m_gameName     Init             Game_cyclic        DeInit  */
    { "PONG",        Pong_InitState,  PONG_cyclic,       Pong_DeInit}, 
    { "SOCCER",      SOCCER_init,     SOCCER_cyclic,            0},
};

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/* Action */
static void GAME_StateMachineInit();
static void GAME_DeInit();
static void GAME_ShowGameInfo();
static void GAME_Cyclic();
static void GAME_ShowGameScore();
static void GAME_DecrementLife();
static void GAME_ShowLoosingMessage();
static void GAME_LifeScoreInit();
static void GAME_ClearLife();

/* Guard*/
static boolean_t NotGameOver();
static boolean_t GameOverAndLifeRemain();
static boolean_t GameOverAndNoLifeRemain();


/*****************************************************************************/
/* Local const table ('static')                                      */
/*****************************************************************************/

/** ---------------------------------- Transitions ---------------------------------------- **/

/**  ===== GAME_IS_SELECTING ====   */
static const STATE_stateInnerTransitionTable_t GAME_IS_SELECTING_Transitions = {
/*    Event                      ToState                 Guard               Action                       */
    { GAME_EV_BUTTON_UP,         GAME_IS_SELECTING,       0,                 MENU_prevgame}, 
    { GAME_EV_BUTTON_DOWN,       GAME_IS_SELECTING,       0,                 MENU_nextgame},
    { GAME_EV_BUTTON_START,      GAME_IS_SELECTEDGAME,    0,                 GAME_StateMachineInit},
};
 
/**  ===== GAME_IS_SELECTEDGAME ====   */
static const STATE_stateInnerTransitionTable_t GAME_IS_SELECTEDGAME_Transitions = {
/*    Event                      ToState                  Guard               Action                       */
    { GAME_EV_TICK,              GAME_IS_SELECTEDGAME,    0,                  GAME_Cyclic}, 
    { GAME_EV_BUTTON_STOP,       GAME_IS_SELECTING,       0,                  GAME_DeInit},
};


static const STATE_stateOuterTransitionTable_t GameStateMachine_Transitions = {
/*    fromState             Pointer to table                    Size of table [Elements]    */
    { GAME_IS_SELECTING,    &GAME_IS_SELECTING_Transitions,     sizeof(GAME_IS_SELECTING_Transitions)/sizeof(STATE_stateInnerTransition_t)    },
    { GAME_IS_SELECTEDGAME,     &GAME_IS_SELECTEDGAME_Transitions,      sizeof(GAME_IS_SELECTEDGAME_Transitions)/sizeof(STATE_stateInnerTransition_t)     },
};
static const uint16_t GameStateMachine_Transitions_size = sizeof(GameStateMachine_Transitions)/sizeof(STATE_stateOuterTransition_t);

/** ---------------------------------- Action ------------------------------------------- **/

static const STATE_stateActionTable_t GameStateMachine_StateActions = {
/*  fromState               Entry                    Exit    */
  { GAME_IS_SELECTING,      MENU_ShowMenu,            0   },
  { GAME_IS_SELECTEDGAME,      0,            0   },
};
static const uint16_t GameStateMachine_StateActions_size = sizeof(GameStateMachine_StateActions)/sizeof(STATE_stateAction_t);


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
static void GAME_ClearLife()
{
  SEVEN_Init();
}

static void GAME_StateMachineInit()
{
  GAME_table[MENU_GetIndex()].Init();  
}

static void GAME_DeInit()
{
  GAME_table[MENU_GetIndex()].DeInit();  
}
static void GAME_ShowGameInfo()
{
  UART_LOG_PutString("GAME_ShowGameInfo\r");
 //GAME_table[MENU_GetIndex()].Show_game_info();
}

static void GAME_Cyclic()
{
  //UART_LOG_PutString("GAME_Cyclic\r");
 GAME_table[MENU_GetIndex()].Game_cyclic();
}
static void GAME_ShowGameScore()
{
  UART_LOG_PutString("GAME_ShowGameScore\r"); 
  //GAME_table[MENU_GetIndex()].Game_LoosingGameMsg();
}
static void GAME_DecrementLife()
{
  UART_LOG_PutString("GAME_DecrementLife\r"); 
  
  GAME_decrement_life();
}
static void GAME_ShowLoosingMessage()
{
  UART_LOG_PutString("GAME_ShowLoosingMessage\r");
  //GAME_table[MENU_GetIndex()].Game_LoosingLifeMsg();
}
static void GAME_LifeScoreInit()
{
  GAME_set_life(3);
  GAME_object.score=0;
}

static boolean_t NotGameOver()
{
  UART_LOG_PutString("NotGameOver\r"); 
    if (GAME_lost_life()== BALL_ISNOTMISSING)
    {
        return TRUE;
    }
    else 
    {
        return FALSE;
    }
}
static boolean_t GameOverAndLifeRemain()
{
  UART_LOG_PutString("GameOverAndLifeRemain\r");
  LOG_D("GLL","GAME_object.life %d",GAME_object.life);
    if (GAME_lost_life()== BALL_ISMISSING && GAME_object.life>1)
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
  UART_LOG_PutString("GameOverAndNoLifeRemain\r");
  if (GAME_lost_life()== BALL_ISMISSING && GAME_object.life==1)
    {
        GAME_decrement_life();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
void GAME_init()
{
    //Cfg_init(&pong_cfg);
    //GAME_table[];
    GAME_table[MENU_GetIndex()].Init();
    
}
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t GAME_set_event(GAME_event_t ev)
{
    GAME_object.ev = ev;
   SetEvent(tsk_game, ev_newGameEvent);    
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
GAME_event_t GAME_get_event()
{
    return GAME_object.ev;
    
    
}
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t GAME_show_menu()
{
    TFT_setTextColor(YELLOW);
    TFT_setTextSize(2);
    TFT_setCursor(20,10);
    TFT_print("Welcome");
    TFT_writeLine(0, 35, 128, 35, YELLOW); 
    //This will be shown after 5 seconds        
    TFT_setTextSize(1);
    TFT_setCursor(20,60);
    TFT_print("Select your Game:");
    TFT_setCursor(40,100);
    TFT_print("PONG Game");
    TFT_setCursor(30,140);
    TFT_print("SOCCER Game");
   // break;
}
//}
/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t GAME_Menu_selecting (GAME_Enum_t selection)
{
    //Todoi change game object game selector    
  
   if (selection == GAME_PONG)
{
   TFT_setTextColor(RED);
   TFT_setCursor(40,100);
   TFT_print("PONG Game"); 
}
  if (selection == GAME_SOCCER)
{
   TFT_setTextColor(RED);
   TFT_setCursor(30,140);
   TFT_print("SOCCER Game");
}
   
}
/* <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */

RC_t GAME_set_life(sint8_t life)
{
 GAME_object.life=life;
 SEVEN_Set(SEVEN_1, life);   
}
/* <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t GAME_decrement_life()
{
    GAME_object.life -=1;
    GAME_set_life(GAME_object.life);
    
}
/* <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */

Ball_Situation_t GAME_lost_life ()
{
    Ball_Situation_t result = BALL_UNKNOWN;
    PONG_BOUNDARY res=PONG_BallReachedBoundary();
    //LOG_D("GLL","PONG_BallReachedBoundary %d",res);
    if(res == PONG_BOUNDARY_GAME_OVER_SPOT)
    {
       result = BALL_ISMISSING; 
       //LOG_D( "GLL","miss");
    }
    else
    {
        result= BALL_ISNOTMISSING; 
        //LOG_D( "GLL","no miss");
    }
    
    return result;
}


/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */
RC_t GAME_InitState()
{
   STATE_initState( GameStateMachine_StateActions , 
                        GameStateMachine_StateActions_size,
                        &Game_state, GameStateMachine_INIT_DATA); 
    
}


RC_t GAME_process_event(STATE_event_t ev)
{
   STATE_processEvent(GameStateMachine_Transitions,
                        GameStateMachine_Transitions_size,
                        GameStateMachine_StateActions, 
                        GameStateMachine_StateActions_size,
                        ev,
                        &Game_state);
    
    
    
    
    
}

/**
 * <Description>
 * @param <Format: copy of the parameter type and name - description>
 * @return <return description>
 */

//RC_t GAME_process_event(GAME_event_t ev)
//{
//
//    switch (GAME_object.state)
//    {       
//        case GAME_IS_SELECTING: 
//        
//            if (ev == GAME_EV_BUTTON_START) 
//            {
//                MENU_activategame();
//               if (GAME_object.selection==GAME_PONG)
//            {
////               GAME_object.state = GAME_ISPLAYING;
////               RC_t ret = PONG_init();
//            }
//
//            }      
//            else if (ev == GAME_EV_BUTTON_UP) 
//            {
//                MENU_prevgame();
//                // UART_LOG_PutString("GAME_EV_START is being activated\n");
//              //  GAME_object.selection = GAME_PONG;
//                //GAME_object.life=3;
//                GAME_Menu_selecting(GAME_PONG);  
////              if (GAME_object.selection==GAME_PONG)
////            {
////               PONG_show_menu(); 
////               GAME_set_life(3);
////            }
//
//               // UART_LOG_PutString("PONG_menu\n");
//            }  
//            else if (ev == GAME_EV_BUTTON_DOWN) 
//            {
//             //   GAME_object.selection = GAME_SOCCER;
//                MENU_nextgame();
//                GAME_Menu_selecting (GAME_SOCCER); 
//            }
//
//            break;
//
//        case GAME_IS_PLAYING:
//    
//            if (ev == GAME_EV_BUTTON_STOP)
//            {
//               // UART_LOG_PutString("GAME_EV_Sop is being activated\n");
//                GAME_object.state = GAME_IS_SELECTING;
//            }
//            else if (ev == GAME_EV_TICK) 
//            {
//          GAME_object.BallSituation=GAME_lost_life ();
//                
//            LOG_D("GAME","GO.ballsituation %d",GAME_object.BallSituation);
//           if (GAME_object.BallSituation==BALL_ISMISSING)
//           {
//            GAME_decrement_life();
//            PONG_loosing_menu();
//            GAME_object.state = GAME_IS_SELECTING;        
//            UART_LOG_PutString("missing happens");
//            }
//             else
//            {
//            RC_t ret = PONG_cyclic();
//            UART_LOG_PutString("normal situation\n");
//            }
//            }         
//            break;
//            
//        default:
//            break;
//    }
//
//}
