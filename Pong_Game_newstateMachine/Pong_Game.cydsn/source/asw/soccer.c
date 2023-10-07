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
#include "tft.h"
#include "joystick.h"
#include "screen.h"
#include "soccer.h"
#include "logging.h"
#include "statemachine.h"
#include "button.h"
#include "Event_Ringbuffer.h"
#include "CAN.h"
#include "game.h"

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

 static SOCCER_GAME_t SOCCER_object = {};
 static ButtonPressStates_t StartButtonStateVar = IDLE;
 static RB_t soccer__ringbuffer;

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

 static void SOCCER_object_init();
 static void SOCCER__play();
 static void SOCCER__CANtransmit_ballinfo();
 static void SOCCER__CANtransmit_playerinfo();
 static void SOCCER__CANtransmit_confirm();
 static void SOCCER__CAN_STATUS();
 static RC_t SOCCER__control();
 //static void SOCCER__Show_welcome_message();
static void SOCCER__Gameplay();
 


 
/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/



/** ---------------------------------- Transitions ---------------------------------------- **/

/**  ===== IS_SOCCER_WELCOME ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_STARTING = {
/*    Event                                ToState                      Guard                 Action                       */
    { SOCCER_EV_START_BUTTON,         IS_WAITING_CONFIRMATION,            0,             SOCCER__CANtransmit_playerinfo},
    { SOCCER_EV_CAN_CONNECTRX,        IS_BALL_NOTPRESENT,                 0,             SOCCER__CANtransmit_confirm}, //Soccer_init() need to be done in this func
    {0,0,0,0},
};

/**  ===== IS_SOCCER_WAITING_CONFIRMATION ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_WAITING_CONFIRMATION = {
/*    Event                                ToState                      Guard                 Action                       */
    { SOCCER_EV_CAN_ACK,                IS_BALL_PRESENT,                  0,             SOCCER_object_init},      //Soccer_init() + ball_init() needs to be done here
//    { SOCCER_EV_TIMEOUT,                IS_ERROR_STATE,                   0,             SOCCER__show_error_msg}, //Soccer_init() need to be done in this func
    {0,0,0,0},
};

//
//
/**  ===== IS_BALL_PRESENT ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_BALL_PRESENT = {
/*    Event                                ToState                 Guard                        Action                       */
    { SOCCER_EV_BALL_TRANSMIT,         IS_BALL_NOTPRESENT,            0,                     SOCCER__CANtransmit_ballinfo},
    { SOCCER_EV_TICK,                    IS_BALL_PRESENT,                0,                     SOCCER__play},  //Need to impliment game not over guard
    {0,0,0,0},
};
//
//
/**  ===== IS_BALL_NOTPRESENT ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_BALL_NOTPRESENT = {
/*    Event                                ToState                     Guard                              Action                       */
    { SOCCER_EV_BALL_RECIEVE,           IS_BALL_PRESENT,                  0,                                0},
    { SOCCER_EV_TICK,                   IS_BALL_NOTPRESENT,               0,                           SOCCER__play},     //Need to impliment game not over guard
    {0,0,0,0},
};
//
//
/** ======= OUTERTRANSITION_TABLE =======   */
static const STATE_stateOuterTransitionTable_t STATE_SOCCER_StateMachine = {
/*    fromState                    Pointer to table                            Size of table [Elements]    */
    { IS_STARTING,                &STATE_IS_STARTING,                     sizeof(STATE_IS_STARTING)/sizeof(STATE_stateInnerTransition_t)},
    { IS_WAITING_CONFIRMATION,    &STATE_IS_WAITING_CONFIRMATION,         sizeof(STATE_IS_WAITING_CONFIRMATION)/sizeof(STATE_stateInnerTransition_t)},
    { IS_BALL_PRESENT,            &STATE_IS_BALL_PRESENT,                 sizeof(STATE_IS_BALL_PRESENT)/sizeof(STATE_stateInnerTransition_t)},
    { IS_BALL_NOTPRESENT,         &STATE_IS_BALL_NOTPRESENT,              sizeof(STATE_IS_BALL_NOTPRESENT)/sizeof(STATE_stateInnerTransition_t)},
    {0,0,0},
};
static const uint16_t STATE_SOCCER_StateMachine_size = sizeof(STATE_SOCCER_StateMachine)/sizeof(STATE_stateOuterTransition_t);

///** ---------------------------------- Action ------------------------------------------- **/
//
static const STATE_stateActionTable_t STATE_SOCCER_StateActions = {
/*  fromState                          Entry                                     Exit    */
  { IS_STARTING,                    SOCCER__Show_welcome_message,                   0   },
  { IS_WAITING_CONFIRMATION,                0,                                      0   },        // Timeout entry action need to be implimented
  { IS_BALL_PRESENT,                SOCCER__CAN_STATUS,                             0   },
  { IS_BALL_NOTPRESENT,             SOCCER__CAN_STATUS,                             0   },
  {0,0,0},
};
static const uint16_t STATE_SOCCER_StateActions_size = sizeof(STATE_SOCCER_StateActions)/sizeof(STATE_stateAction_t);



/**
 * Updates the position and draws the bat on the screen
 * @param *me : Pointer pointing to the bat object
 * @return void
*/


static RC_t SOCCER__control()
{
    
//    //Input part - we look at various inputs and translate this into events for the soccer game
//    //May of course also happen in ISR
//    
//    if (ButtonPressed(1)) AddSoccerEvent(ev_buttton_1)
//    if (BallIsCrossingLine() AddCoccerEVent(ev_crossedLine)
//    if (CAN_rx_Requested Player1) AddSoccerEvent(ev_CAN_player1)
//    ...TimeOutEvent must be created
//    
//    //These 2 lines are moved to a state machine action
//    JOYSTICK_update(&SOCCER_object.joystick);  
//    BAT_update_pos(&SOCCER_object.bat,&SOCCER_object.joystick);
//        
//    if (SoccerEventAvailable() directCallToSTateMAchine
//    SOCCER__control(&SOCCER_object.ball); 
//        
//    //This will also be in an action
//    BALL_update_pos(&SOCCER_object.ball);
    
    
            
    while(RB_prots_available(&soccer__ringbuffer))
    {
        RB_content_t data;
        RC_t ret = RB_get(&soccer__ringbuffer,&data); 
                
        
                
        STATE_processEvent(STATE_SOCCER_StateMachine,STATE_SOCCER_StateMachine_size,STATE_SOCCER_StateActions,STATE_SOCCER_StateActions_size,(SOCCER_Event_t)data,&SOCCER_object.state);
        
        UART_LOG_PutChar(SOCCER_object.state);
    }
    
    return RC_SUCCESS;

}

SOCCER_BOUNDARY SOCCER_BallReachedBoundary()
{
    SOCCER_BOUNDARY res= SOCCER_BOUNDARY_none;

    //Checking for a normal boundary situation
    if (SOCCER_object.ball.current_ball_pos.Y >= (SCREEN_WIDTH - BALL_WIDTH))    
    {
        res=SOCCER_BOUNDARY_right;
    }
    else if(SOCCER_object.ball.current_ball_pos.X >= (SCREEN_HEIGHT - BALL_WIDTH))
    {
        res = SOCCER_BOUNDARY_up;
    }
    else if (SOCCER_object.ball.current_ball_pos.Y <= 0)
    {
        res = SOCCER_BOUNDARY_left;
    }
    else if((SOCCER_object.ball.current_ball_pos.X <= BALL_WIDTH)&&(SOCCER_object.bat.current_bat_pos <= SOCCER_object.ball.current_ball_pos.Y) && (SOCCER_object.ball.current_ball_pos.Y <= (SOCCER_object.bat.current_bat_pos + BAT_HEIGHT) ))
    {
        res = SOCCER_BOUNDARY_down;
    }
    
    //Check for special cases, overwriting the normal boundary
    if(( SOCCER_object.ball.current_ball_pos.X <= BALL_WIDTH)&&
    ((SOCCER_object.bat.current_bat_pos > SOCCER_object.ball.current_ball_pos.Y) || 
    (SOCCER_object.ball.current_ball_pos.Y > (SOCCER_object.bat.current_bat_pos + BAT_HEIGHT) )))
    {  
       res = SOCCER_BOUNDARY_GAME_OVER_SPOT;
    }
 
    return res;
}

static void SOCCER__play()
{
    
    JOYSTICK_update(&SOCCER_object.joystick);  
    BAT_update_pos(&SOCCER_object.bat,&SOCCER_object.joystick);
        
    //if (SoccerEventAvailable() directCallToSTateMAchine
    SOCCER__Gameplay(); 
        
    //This will also be in an action
    BALL_update_pos(&SOCCER_object.ball);

    SCREEN_update(&SOCCER_object.screen);
    
}



static void SOCCER__Gameplay()
{
    
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_right)
    {
        BALL_flipYSpeed(&SOCCER_object.ball);
        
    }
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_left)
    {
        BALL_flipYSpeed(&SOCCER_object.ball);
        
    }
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_up)
    {

       SOCCER_object.event = SOCCER_EV_BALL_TRANSMIT;
        
    }
    

    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_down)
    {
        BALL_flipXSpeed(&SOCCER_object.ball);
        
    }
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_GAME_OVER_SPOT)
    {
        
        BALL_STOP(&SOCCER_object.ball);
        
    }
}
  

/** This one is the init function, which is called once before starting the game
**/
RC_t SOCCER_init()
{
    RB_init(&soccer__ringbuffer,8);
    STATE_initState(STATE_SOCCER_StateActions,STATE_SOCCER_StateActions_size,&SOCCER_object.state,SOCCER_STATEMACHINE_INIT_DATA);
    //SOCCER_object.state = SOCCER_STATEMACHINE_INIT_DATA;
}



static void SOCCER_object_init()
{
    TFT_clearScreen();
    //Creating some local values required for the init functions
    Cordinate_t pos = {10 , 20};
    SPEED_t ball_speed = {1,1};
    
    
    
    
    //Initialisaing the BAT part of the SOCCER_object
    BAT_init(&SOCCER_object.bat, 50);
    
    //Initialisaing the BALL part of the SOCCER_object
    BALL_init(&SOCCER_object.ball, pos, ball_speed);
    
    //Initialisaing the SCREEN part of the SOCCER_object
    SCREEN_init(&SOCCER_object.screen, &SOCCER_object.bat, &SOCCER_object.ball);
    SCREEN_update(&SOCCER_object.screen);    
    

    
   // SOCCER__transmit_firstPlayer(); - Need soccer welcome state
    
    //The joystick part will be updated by the driver, so no need for an explizit initialisation
}

/**
 * This one will be called cyclically while playing the game
 */
RC_t SOCCER_cyclic()
{
   
    
    //SOCCER_play();
    //SCREEN_update(&SOCCER_object.screen);
    
    
    uint16_t EV  = SOCCER_EV_NONE;
    
    BUTTON1_CheckShortPress(&StartButtonStateVar, &EV , SOCCER_EV_START_BUTTON);
    
    if(EV == SOCCER_EV_START_BUTTON)
    {
        RB_put(&soccer__ringbuffer,SOCCER_EV_START_BUTTON);
    }
    else if(SOCCER_object.event == SOCCER_EV_CAN_CONNECTRX)
    {
       RB_put(&soccer__ringbuffer,SOCCER_EV_CAN_CONNECTRX);
       SOCCER_object.event = SOCCER_EV_NONE;
    }
    else if(SOCCER_object.event == SOCCER_EV_CAN_ACK)
    {
       RB_put(&soccer__ringbuffer,SOCCER_EV_CAN_ACK);
       SOCCER_object.event = SOCCER_EV_NONE;
    }
    else if(SOCCER_object.event == SOCCER_EV_BALL_TRANSMIT)
    {
       RB_put(&soccer__ringbuffer,SOCCER_EV_BALL_TRANSMIT);
       SOCCER_object.event = SOCCER_EV_NONE;
    }
    else if(SOCCER_object.event == SOCCER_EV_BALL_RECIEVE)
    {
       RB_put(&soccer__ringbuffer,SOCCER_EV_BALL_RECIEVE);
       SOCCER_object.event = SOCCER_EV_NONE;
    }
    else 
    {
        RB_put(&soccer__ringbuffer,SOCCER_EV_TICK);
    }
    
    SOCCER__control();
    
    
}

 SOCCER_GAME_t SOCCER_getobj()
{
    return SOCCER_object;
}


static void SOCCER__CAN_STATUS()
{
   //LOG_I("CAN state","%d\r", SOCCER_object.state); 
}

static void SOCCER__CANtransmit_ballinfo()
{
    CAN_DATA_BYTES_MSG payload = {0,0,0,0,0,0};
    
    payload.byte[0] = SOCCER_object.ball.previous_ball_pos.X;
    payload.byte[1] = SOCCER_object.ball.previous_ball_pos.Y;
    payload.byte[2] = SOCCER_object.ball.current_ball_pos.X;
    payload.byte[3] = SOCCER_object.ball.current_ball_pos.Y;
    payload.byte[4] = SOCCER_object.ball.ball_speed.pos.X;
    payload.byte[5] = SOCCER_object.ball.ball_speed.pos.Y;
    
    //Set up message
    CAN_TX_MSG msg;
    msg.id = 0x100; //CobId
    msg.ide = 0; //11bit identifier (else 29)
    msg.rtr = 0; //Normal message
    msg.dlc = 6; //Length
    msg.msg = &payload; //Data to be transmitted
    
    
//    LOG_I("ball cordinates","%d,%d,%d,%d,%d,%d", SOCCER_object.ball.previous_ball_pos.X,SOCCER_object.ball.previous_ball_pos.Y,
//        SOCCER_object.ball.current_ball_pos.X,SOCCER_object.ball.current_ball_pos.Y, SOCCER_object.ball.ball_speed.pos.X, SOCCER_object.ball.ball_speed.pos.Y); 
    
    //UART_LOG_PutChar(SOCCER_object.state);
    
    CAN_SendMsg(&msg);

}

static void SOCCER__CANtransmit_playerinfo()
{
    UART_LOG_PutString("button pressed");
    
    CAN_DATA_BYTES_MSG payload = {0};
    
    payload.byte[0] = 1;
    
    //Set up message
    CAN_TX_MSG msg;
    msg.id = 0x200; //CobId
    msg.ide = 0; //11bit identifier (else 29)
    msg.rtr = 0; //Normal message
    msg.dlc = 1; //Length
    msg.msg = &payload; //Data to be transmitted
        
    CAN_SendMsg(&msg);

}

static void SOCCER__CANtransmit_confirm()
{
    
    CAN_DATA_BYTES_MSG payload = {0};
    
    payload.byte[0] = 1;
    
    //Set up message
    CAN_TX_MSG msg;
    msg.id = 0x300; //CobId
    msg.ide = 0; //11bit identifier (else 29)
    msg.rtr = 0; //Normal message
    msg.dlc = 1; //Length
    msg.msg = &payload; //Data to be transmitted
        
    CAN_SendMsg(&msg);

}


void SOCCER_can_recieve(uint8_t mailbox)
{

    CAN_DATA_BYTES_MSG payload = {0,0,0,0,0,0};

    //Get the metadata of the message
    uint16_t cobid = CAN_GET_RX_ID(mailbox);
    uint8_t len = CAN_GET_DLC(mailbox);
 
    //Read in the payload
    for (uint8_t i = 0; i < len; i++)
    {
        payload.byte[i] = CAN_RX_DATA_BYTE(mailbox, i);
    }

    
    
    if(cobid == 0x200)
    {
        
        TFT_clearScreen();

    
        //Initialisaing the BAT part of the SOCCER_object
        BAT_init(&SOCCER_object.bat, 50);
    

    
        //Initialisaing the SCREEN part of the SOCCER_object
        SCREEN_init(&SOCCER_object.screen, &SOCCER_object.bat,0);
        SCREEN_update(&SOCCER_object.screen);  
        

        
        SOCCER_object.event = SOCCER_EV_CAN_CONNECTRX;
        
        //RB_put(&soccer__ringbuffer,SOCCER_EV_CAN_CONNECTRX);
        
    }
    
    
    
    else if(cobid == 0x100)
    {
        //Creating some local values required for the init functions

        
       
        SOCCER_object.ball.previous_ball_pos.X = payload.byte[0];
        SOCCER_object.ball.previous_ball_pos.Y = payload.byte[1];
        SOCCER_object.ball.current_ball_pos.X = payload.byte[2];
        SOCCER_object.ball.current_ball_pos.Y = payload.byte[3];
        SOCCER_object.ball.ball_speed.pos.X = -payload.byte[4];
        SOCCER_object.ball.ball_speed.pos.Y = -payload.byte[5];
        
        
        LOG_I("ball cordinates","%d,%d,%d,%d,%d,%d", SOCCER_object.ball.previous_ball_pos.X,SOCCER_object.ball.previous_ball_pos.Y,
        SOCCER_object.ball.current_ball_pos.X,SOCCER_object.ball.current_ball_pos.Y, SOCCER_object.ball.ball_speed.pos.X, SOCCER_object.ball.ball_speed.pos.Y); 
    
        
        
        
        SOCCER_object.event = SOCCER_EV_BALL_RECIEVE;
        
    }
    
    
    else if(cobid == 0x300)
    {
        
        SOCCER_object.event = SOCCER_EV_CAN_ACK;
    
    
    
    }

    
}


void SOCCER__Show_welcome_message()
{
TFT_clearScreen();
TFT_setTextColor(YELLOW);
TFT_setTextSize(1);
TFT_setCursor(5,10);
TFT_print("Welcome to SOCCER Game");
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

RC_t SOCCER_loosing_menu()
{
TFT_clearScreen();
TFT_setTextColor(YELLOW);
TFT_setTextSize(1);
TFT_setCursor(20,35);
TFT_print("You lost 1 life");
TFT_setCursor(20,60);
TFT_print("For restarting");
TFT_setCursor(20,100);
TFT_print("Press B.1");
}