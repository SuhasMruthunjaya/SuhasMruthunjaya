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
* \brief File containing attributes and functions of Soccer Class
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
#include "seven.h"
/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/
#define SoccerGameLife 3
#define CAN_ID_BALL_INFO 0x100
#define CAN_ID_PLAYER1_INFO 0x200
#define CAN_ID_PLAYER2_INFO 0x300
#define CAN_ID_GAMEOVER 0x400
#define CAN_ID_GAMESTOP 0x500
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
static int timer_10s_count;
static int timer_2s_count;
/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

static void SOCCER_object_init();
static void SOCCER__play();
static void SOCCER__CANtransmit_ballinfo();
static void SOCCER__CANtransmit_player_1_info();
static void SOCCER__CANtransmit_confirm();
static void SOCCER__CANSend_gameover();
static RC_t SOCCER__control();
static void SOCCER__Gameplay();
static void SOCCER__LifeInit();
static void SOCCER__ShowLostRoundMessage();
static void SOCCER__ShowWonRoundMessage();
static void SOCCER__ShowGameLostMessage();
static void SOCCER__ShowGameWonMessage();
static void SOCCER__CANSend_GameStop();
static void SOCCER__Set_FlagGameStop();
static void SOCCER__Reset_FlagGameStop();
static void SOCCER__NoBallStateINIT();
static void SOCCER__timer_2s();
static void SOCCER__timer_10s();
static void SOCCER__ResetTimer_2s();
static void SOCCER__ResetTimer_10s();
static void SOCCER__NoBallPlay();
static void SOCCER__show_error_msg();
static SOCCER_BOUNDARY SOCCER_BallReachedBoundary(  );
static void SOCCER__Show_welcome_message();

/* State Machine Gaurds   */
static boolean_t NotGameOver();
static boolean_t GameOverAndLifeRemain();
static boolean_t IfFlagGameStopSet();
static boolean_t IfFlagGameStopReset();
static boolean_t GameOverAndNoLifeRemain();


 
/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/



/** ---------------------------------- Transitions ---------------------------------------- **/

/**  ===== IS_STARTING ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_STARTING = {
/*    Event                                ToState                      Guard                 Action                       */
    { SOCCER_EV_START_BUTTON,         IS_WAITING_CONFIRMATION,            0,             SOCCER__CANtransmit_player_1_info},
    { SOCCER_EV_CAN_CONNECTRX,        IS_BALL_NOTPRESENT,                 0,             SOCCER__CANtransmit_confirm},
    {0,0,0,0},
};

/**  ===== IS_SOCCER_WAITING_CONFIRMATION ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_WAITING_CONFIRMATION = {
/*    Event                                ToState                      Guard                 Action                       */
    { SOCCER_EV_CAN_ACK,                IS_BALL_PRESENT,                  0,             SOCCER_object_init},
    { SOCCER_EV_TICK,                   IS_WAITING_CONFIRMATION,          0,             SOCCER__timer_2s},
    { SOCCER_EV_TIMEOUT,                IS_ERROR_STATE,                   0,             SOCCER__show_error_msg},
    {0,0,0,0},
};

//
/**  ===== IS_BALL_PRESENT ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_BALL_PRESENT = {
/*    Event                                ToState                 Guard                        Action                       */
    { SOCCER_EV_BALL_TRANSMIT,         IS_BALL_NOTPRESENT,            0,                     SOCCER__CANtransmit_ballinfo},
    { SOCCER_EV_TICK,                    IS_BALL_PRESENT,         NotGameOver,               SOCCER__play},
    { SOCCER_EV_TICK,                    IS_GAME_OVER,            GameOverAndLifeRemain,     SOCCER__ShowLostRoundMessage},
    { SOCCER_EV_TICK,                    IS_GAME_OVER,            GameOverAndNoLifeRemain,   SOCCER__ShowGameLostMessage},
};
//
//
/**  ===== IS_BALL_NOTPRESENT ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_BALL_NOTPRESENT = {
/*    Event                                ToState                     Guard                              Action                       */
    { SOCCER_EV_CAN_BALL_RECIEVE,       IS_BALL_PRESENT,                  0,                     SOCCER__ResetTimer_10s},
    { SOCCER_EV_TIMEOUT,                IS_ERROR_STATE,                   0,             	     SOCCER__show_error_msg},
    { SOCCER_EV_TICK,                   IS_BALL_NOTPRESENT,           NotGameOver,               SOCCER__NoBallPlay},
    {SOCCER_EV_CAN_GAMEOVERRX,          IS_GAME_OVER,                     0,                     SOCCER__ShowWonRoundMessage},
    {SOCCER_EV_CAN_GAMESTOPRX,          IS_GAME_OVER,                     0,                     SOCCER__ShowGameWonMessage},
};

/**  ===== IS_GAME_OVER ====   */
static const STATE_stateInnerTransitionTable_t STATE_IS_GAME_OVER = {
/*    Event                                ToState                     Guard                              Action                       */
    { SOCCER_EV_CAN_CONNECTRX,        IS_BALL_NOTPRESENT,             IfFlagGameStopReset,                 SOCCER__CANtransmit_confirm},
    { SOCCER_EV_START_BUTTON,         IS_WAITING_CONFIRMATION,        IfFlagGameStopReset,   SOCCER__CANtransmit_player_1_info}, 
    { SOCCER_EV_START_BUTTON,         IS_STARTING,                    IfFlagGameStopSet,                    0},      
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
    { IS_GAME_OVER,               &STATE_IS_GAME_OVER,                   sizeof(STATE_IS_GAME_OVER)/sizeof(STATE_stateInnerTransition_t)},
};
static const uint16_t STATE_SOCCER_StateMachine_size = sizeof(STATE_SOCCER_StateMachine)/sizeof(STATE_stateOuterTransition_t);

///** ---------------------------------- Action ------------------------------------------- **/
//
static const STATE_stateActionTable_t STATE_SOCCER_StateActions = {
/*  fromState                          Entry                                     Exit    */
  { IS_STARTING,                    SOCCER__Show_welcome_message,                   0   }, 
  { IS_STARTING,                    SOCCER__LifeInit,                               0   },
  { IS_STARTING,                    SOCCER__Reset_FlagGameStop,                     0   },
  { IS_WAITING_CONFIRMATION,                0,                                      0   },        // Timeout entry action need to be implimented
  { IS_BALL_PRESENT,                        0,                                      0   },
  { IS_BALL_NOTPRESENT,                     0,                                      0  },
  {0,0,0},
};
static const uint16_t STATE_SOCCER_StateActions_size = sizeof(STATE_SOCCER_StateActions)/sizeof(STATE_stateAction_t);

/*!
 * This static function controls the game flow by processing events from the ring buffer. Passes the events from the ringbuffer
 * to the soccer state machine. Each event triggers a corresponding state transition in the soccer game state machine.
 * @return RC_SUCCESS - Return code indicating successful execution.
 */
static RC_t SOCCER__control()
{
    
    while(RB_prots_available(&soccer__ringbuffer))
    {
        RB_content_t data;
        RC_t ret;

        ret = RB_get(&soccer__ringbuffer,&data);
        if (ret != RC_SUCCESS)
        {
        	UART_LOG_PutString("Error while receiving the Events from the RingBuffer");
        	return RC_ERROR;
        }
        
                
        ret = STATE_processEvent(STATE_SOCCER_StateMachine,STATE_SOCCER_StateMachine_size,STATE_SOCCER_StateActions,STATE_SOCCER_StateActions_size,(SOCCER_Event_t)data,&SOCCER_object.state);
        if(ret != RC_SUCCESS)
        {
        	UART_LOG_PutString("Error processing the Soccer State machine");
        	return RC_ERROR;
        }
    }
    
    return RC_SUCCESS;

}


/*!
 * This static function determines if the soccer ball has reached a boundary and returns the result.
 * The function checks for normal and special boundary situations.
 * @return SOCCER_BOUNDARY - Enum representing the boundary reached by the soccer ball.
 */
static SOCCER_BOUNDARY SOCCER_BallReachedBoundary()
{
    SOCCER_BOUNDARY res= SOCCER_BOUNDARY_none;

    //Checking for a normal boundary situation
    if (SOCCER_object.ball.current_ball_pos.Y >= (SCREEN_WIDTH - WALL_WIDTH - BALL_WIDTH))    
    {
        res=SOCCER_BOUNDARY_right;
    }
    else if(SOCCER_object.ball.current_ball_pos.X >= (SCREEN_HEIGHT))
    {

        res = SOCCER_BOUNDARY_up;
    }
    else if (SOCCER_object.ball.current_ball_pos.Y <= WALL_WIDTH)
    {
        res = SOCCER_BOUNDARY_left;
    }
    else if((SOCCER_object.ball.current_ball_pos.X <= BALL_WIDTH)&&
    (SOCCER_object.bat.current_bat_pos <= SOCCER_object.ball.current_ball_pos.Y + BALL_WIDTH) && 
    ((SOCCER_object.bat.current_bat_pos + BAT_HEIGHT)>= SOCCER_object.ball.current_ball_pos.Y))
    {
        res = SOCCER_BOUNDARY_down;
    }
    
    //Check for special cases, overwriting the normal boundary
    if(( SOCCER_object.ball.current_ball_pos.X <= BALL_WIDTH)&&
    ((SOCCER_object.bat.current_bat_pos > (SOCCER_object.ball.current_ball_pos.Y + BALL_WIDTH) )|| 
    ((SOCCER_object.bat.current_bat_pos + BAT_HEIGHT)< SOCCER_object.ball.current_ball_pos.Y)))
    {  
       res = SOCCER_BOUNDARY_GAME_OVER_SPOT;
    }
 
    return res;
}


static void SOCCER__play()
{
    //SCREEN_drawSoccerNet();
    JOYSTICK_update(&SOCCER_object.joystick);  
    BAT_update_pos(&SOCCER_object.bat,&SOCCER_object.joystick);
        
    //This will also be in an action
    BALL_update_pos(&SOCCER_object.ball);
    

    SOCCER__Gameplay(); 


    SCREEN_update(&SOCCER_object.screen);
    SCREEN_SoccerCheckBallHitNet(&SOCCER_object.screen);
}

/*!
 * This static function executes the gameplay logic, updating ball positions and checking for boundary conditions.
 * Handles specific actions based on different boundary conditions. If a ball hits the right /left boundary and the bat
 * it should flip its direction and bounce, if the ball reaches the Boundary UP, a CAN Message is transmitted to the other
 * board by updating the Event parameter of the static soccer object. If the ball didn't meet the bat in the Boundary down, it
 * goes into a Game over Spot and stops the ball movement by calling the BALL_Stop function.
 * @return void - Returns void
 */

static void SOCCER__Gameplay()
{
    
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_right)
    {
        BALL_flipYSpeed(&SOCCER_object.ball);
        
        SOCCER_object.ball.current_ball_pos.Y = SCREEN_WIDTH - WALL_WIDTH - BALL_WIDTH;
    }
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_left)
    {
        BALL_flipYSpeed(&SOCCER_object.ball);
        if(SOCCER_object.ball.current_ball_pos.Y<WALL_WIDTH)
        SOCCER_object.ball.current_ball_pos.Y=WALL_WIDTH;
        
    }
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_up)
    {
       SOCCER_object.event = SOCCER_EV_BALL_TRANSMIT;
        
    }
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_down)
    {
        BALL_flipXSpeed(&SOCCER_object.ball);
        BALL_setAngle(&SOCCER_object.ball);
        SOCCER_object.ball.current_ball_pos.X=BALL_WIDTH;
        
    }
    if(SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_GAME_OVER_SPOT)
    {
        
        BALL_STOP(&SOCCER_object.ball);
        
    }
}
 
/*!
 * This static function Checks if the game is over, and there is at least one life remaining.
 * @return boolean_t - TRUE if the game is over, and lives are remaining, else FALSE otherwise.
 */
static boolean_t GameOverAndLifeRemain()
{
  
    if (SOCCER_BallReachedBoundary()== SOCCER_BOUNDARY_GAME_OVER_SPOT && SOCCER_object.life>1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*!
 * This static function Checks if the game is over, and there are no lives remaining.
 * @return boolean_t - TRUE if the game is over, and no lives are remaining; FALSE otherwise.
 */
static boolean_t GameOverAndNoLifeRemain()
{
  
  
  if (SOCCER_BallReachedBoundary()== SOCCER_BOUNDARY_GAME_OVER_SPOT && SOCCER_object.life==1)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*!
 * This static function Checks if the game is not over.
 * @return boolean_t - TRUE if the game is not over; FALSE if the game is over.
 */
static boolean_t NotGameOver()
{
  
    if (SOCCER_BallReachedBoundary() == SOCCER_BOUNDARY_GAME_OVER_SPOT)
    {
        return FALSE;
    }
    else 
    {
        return TRUE;
    }
}

/*!
 * This static function Checks if the game stop flag is set.
 * @return boolean_t - TRUE if the game stop flag is set; FALSE otherwise.
 */
static boolean_t IfFlagGameStopSet()
{
   if (SOCCER_object.Flag_GameStop==TRUE)
    {
        return TRUE;
    }
    else 
    {
        return FALSE;
    } 
}

/*!
 * This static function checks if the game stop flag is reset.
 * @return boolean_t - TRUE if the game stop flag is reset; FALSE otherwise.
 */
static boolean_t IfFlagGameStopReset()
{
   if (SOCCER_object.Flag_GameStop==FALSE)
    {
        return TRUE;
    }
    else 
    {
        return FALSE;
    } 
}

/*!
 * This static function Clears the life display (initialize seven-segment display).
 * @return void
 */
static void SOCCER__ClearLife()
{
  SEVEN_Init();
}

/*!
 * This function decrement the life count and update the seven-segment display.
 * @return void
 */
static void SOCCER__DecrementLife()
{
  
  SOCCER_object.life--;
  SEVEN_Set(SEVEN_1, SOCCER_object.life); 
}

/*!
 * This static function Displays a message and perform actions for a lost round.
 * Decrements life count.
 * Send game over message over CAN.
 * Shows a message on the screen for a lost round.
 * @return void
 */
static void SOCCER__ShowLostRoundMessage()
{
  SOCCER__DecrementLife();
  SOCCER__CANSend_gameover();
  SCREEN_SoccerShowLostRound();

}

/*!
 * THis static function displays a message on the screen for a won round.
 * @return void
 */
static void SOCCER__ShowWonRoundMessage()
{
   SCREEN_SoccerWonRoundMessage(); 
}

/*!
 * Display a message and perform actions for a lost game.
 * - Decrement life count.
 * - Send game stop message over CAN.
 * - Set the game stop flag.
 * - Show a message on the screen for a lost game.
 * @return void
 */
static void SOCCER__ShowGameLostMessage()
{
   SOCCER__DecrementLife();
   SOCCER__CANSend_GameStop();
   SOCCER__Set_FlagGameStop();
   SCREEN_SoccerShowGameLostMessage(); 
}

/*!
 * This static function Displays a message and perform actions for a won game.
 * - Set the game stop flag.
 * - Show a message on the screen for a won game.
 * @return void
 */
static void SOCCER__ShowGameWonMessage()
{
   SOCCER__Set_FlagGameStop();
   SCREEN_SoccerShowGameWonMessage(); 
}

/*!
 * This static function initializes the life and score parameters of the soccer game.
 * The seven segment display is also set by the life attribute
 * @return void
 */
static void SOCCER__LifeInit()
{
  SOCCER_object.life=SoccerGameLife;
  SEVEN_Set(SEVEN_1, SOCCER_object.life); 
}

/*!
 * This static function sets the game stop flag.
 */
static void SOCCER__Set_FlagGameStop()
{
  SOCCER_object.Flag_GameStop=TRUE;  
}

/*!
 * This static function resets the game stop flag.
 * @return void
 */
static void SOCCER__Reset_FlagGameStop()
{
  SOCCER_object.Flag_GameStop=FALSE; 
}

/*!
 * This static function is a Timer callback for a 2-second timer.
 * Increments the timer count and triggers a SOCCER_EV_TIMEOUT if the timer reaches 2 seconds.
 * @return void
 */
static void SOCCER__timer_2s()
{

	timer_2s_count ++;
    
    if(timer_2s_count == 200) //! 2 secs waiting time
    {
        
        timer_2s_count = 0;
        SOCCER_object.event = SOCCER_EV_TIMEOUT;
    }
}

/*!
 * This static function is a Timer callback for a 10-second timer.
 * Increments the timer count and triggers a SOCCER_EV_TIMEOUT if the timer reaches 10 seconds.
 * @return void
 */
static void SOCCER__timer_10s()
{
    timer_10s_count ++;
    
    if(timer_10s_count == 1000) //! 10 secs waiting time
    {
        
        timer_10s_count = 0;
        SOCCER_object.event = SOCCER_EV_TIMEOUT;
    }
}

/*!
 * This static function resets the 2-second timer count.
 * @return void
 */
static void SOCCER__ResetTimer_2s()
{
    timer_2s_count=0;
}

/*!
 * This static function resets the 10-second timer count.
 * @return void
 */
static void SOCCER__ResetTimer_10s()
{
    timer_10s_count=0;
}

/*!
 * Handle the gameplay when soccer is in No ball state.
 * Update joystick and bat positions.
 * Update ball position.
 * Trigger the 10-second timer - Each call to this timer increments the counter to 1 value more
 * Update the screen and check if the ball hits the net.
 */
static void SOCCER__NoBallPlay()
{
    //SCREEN_drawSoccerNet();
    JOYSTICK_update(&SOCCER_object.joystick);  
    BAT_update_pos(&SOCCER_object.bat,&SOCCER_object.joystick);
        
    //This will also be in an action
    BALL_update_pos(&SOCCER_object.ball);
 
    SOCCER__timer_10s();

    SCREEN_update(&SOCCER_object.screen);
    SCREEN_SoccerCheckBallHitNet(&SOCCER_object.screen);

}

/*!
 * This static function displays an error message on the screen when a timeout occurs.
 * @return void
 */
static void SOCCER__show_error_msg()
{
    SCREEN_SoccerShowTimeoutMessage();
}


/*!
 * Initialise the soccer game.
 * Initialise the ring buffer.
 * Initialise the game state machine.
 * @return RC_SUCCESS if Initialisation is successful.
 */
RC_t SOCCER_init()
{
    RB_init(&soccer__ringbuffer,8);
    RC_t ret = STATE_initState(STATE_SOCCER_StateActions,STATE_SOCCER_StateActions_size,&SOCCER_object.state,SOCCER_STATEMACHINE_INIT_DATA);
    if(ret != RC_SUCCESS)
    {
    	UART_LOG_PutString(" Error in the State machine init, inside SOCCER_INIT Function");
    	return RC_ERROR;
    }

    return RC_SUCCESS;
}

/*!
 * Deinitialize the soccer game.
 * Deinitialize the ring buffer.
 * Clear the game life.
 * @return RC_SUCCESS after deinitialization.
 */
RC_t Soccer_DeInit()
{
	RC_t ret;
	ret = RB_deinit(&soccer__ringbuffer);
	if(ret != RC_SUCCESS)
	{
		UART_LOG_PutString(" Error in the Ringbuffer Deinit, Inside the Soccer_Deinit function ");
		return RC_ERROR;
	}

	SOCCER__ClearLife();

	return RC_SUCCESS;
}

/*!
 * This static function initialise the soccer game object.
 * Clears the screen.
 * Set the initial positions and speed of the ball
 * Initialise the bat, ball, and screen.
 * @return void
 */
static void SOCCER_object_init()
{
    TFT_clearScreen();
    //Creating some local values required for the init functions
    Cordinate_t pos = {10 , 35};
    SPEED_t ball_speed = {MIN_BALLSPEED,MIN_BALLSPEED};
    
    
    
    SOCCER__ResetTimer_2s();
    //Initialisaing the BAT part of the SOCCER_object
    BAT_init(&SOCCER_object.bat, 50);
    
    //Initialisaing the BALL part of the SOCCER_object
    BALL_init(&SOCCER_object.ball, pos, ball_speed);
    
    //Initialisaing the SCREEN part of the SOCCER_object
    SCREEN_init(&SOCCER_object.screen, &SOCCER_object.bat, &SOCCER_object.ball);
    SCREEN_update(&SOCCER_object.screen);    
    SCREEN_drawSoccerWall();

}

/*!
 * The main cyclic function called while playing the game.
 * Checks for button presses.
 * Handles game events based on button presses.
 * Put events into the ring buffer.
 * Calls the control function.
 * @return RC_t - RC_SUCCESS if everything works fine
 */
RC_t SOCCER_cyclic()
{
    
    uint16_t EV  = SOCCER_EV_NONE;
    RC_t ret;
    
    ret = BUTTON1_CheckShortPress(&StartButtonStateVar, &EV , SOCCER_EV_START_BUTTON);
    if(ret != RC_SUCCESS)
    {
    	UART_LOG_PutString(" Error in the ButtonCheckShortPress function call, in the SOCCER_Cyclic function ");
    	return RC_ERROR;
    }
    
    if(EV == SOCCER_EV_START_BUTTON)
    {
       ret = RB_put(&soccer__ringbuffer,SOCCER_EV_START_BUTTON);
       if(ret != RC_SUCCESS)
          {
          	UART_LOG_PutString(" Error in the RingBuffer put function call when there is "
          			" an attempt to put SOCCER_EV_START_BUTTON in the ringBuffer, in the SOCCER_Cyclic function."
          			"ALERT FOR AN EVENT MISS ");
          	return RC_ERROR;
          }

    }
    else if(SOCCER_object.event == SOCCER_EV_BALL_TRANSMIT)
    {
       RB_put(&soccer__ringbuffer,SOCCER_EV_BALL_TRANSMIT);
       if(ret != RC_SUCCESS)
          {
          	UART_LOG_PutString(" Error in the RingBuffer put function call when there is "
          			" an attempt to put SOCCER_EV_BALL_TRANSMIT in the ringBuffer, in the SOCCER_Cyclic function."
          			"ALERT FOR AN EVENT MISS ");
          	return RC_ERROR;
          }

       SOCCER_object.event = SOCCER_EV_NONE;
    }
    else if(SOCCER_object.event == SOCCER_EV_TIMEOUT)
    {
       RB_put(&soccer__ringbuffer,SOCCER_EV_TIMEOUT);
       if(ret != RC_SUCCESS)
          {
          	UART_LOG_PutString(" Error in the RingBuffer put function call when there is "
          			" an attempt to put SOCCER_EV_TIMEOUT in the ringBuffer, in the SOCCER_Cyclic function."
          			"ALERT FOR AN EVENT MISS ");
          	return RC_ERROR;
          }
       SOCCER_object.event = SOCCER_EV_NONE;
    }
    
    RB_put(&soccer__ringbuffer,SOCCER_EV_TICK);
    SOCCER__control(); 

    return RC_SUCCESS;
}


/*!
 * This static function Transmits ball information over CAN to the other board.
 * Prepares payload with ball position and speed.
 * Set up the CAN and sends the CAN message.
 * @return void
 */
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
    msg.id = CAN_ID_BALL_INFO; //CobId
    msg.ide = 0; //11bit identifier (else 29)
    msg.rtr = 0; //Normal message
    msg.dlc = 6; //Length
    msg.msg = &payload; //Data to be transmitted
    
    CAN_SendMsg(&msg);

}


/*!
 * This static function Transmits first player information (CobID: CAN_ID_PLAYER1_INFO) over CAN to the other board.
 * Set up the CAN and sends the CAN message.
 * @return void
 */
static void SOCCER__CANtransmit_player_1_info()
{
    
    CAN_DATA_BYTES_MSG payload = {0};
    
    payload.byte[0] = 1;
    
    //Set up message
    CAN_TX_MSG msg;
    msg.id = CAN_ID_PLAYER1_INFO; //CobId
    msg.ide = 0; //11bit identifier (else 29)
    msg.rtr = 0; //Normal message
    msg.dlc = 1; //Length
    msg.msg = &payload; //Data to be transmitted
        
    CAN_SendMsg(&msg);

}

/*!
 * This static function Initialises the game state without a ball, for the second player, who is waiting for the ball
 * information from the first board.
 * Clears the screen.
 * Sets initial positions and speeds.
 * Initialises the bat, ball, and screen. - ball speed is set to 0,0 so it doesnt move, and the position is given as such
 * it is not visible to the screen, this ball gets the new position information over the CAN, as soon as the other board
 * sends it and this ball is visible on the screen until it crosses the upper boundary.
 * Resets the 10-second timer.
 * @return void
 */
static void SOCCER__NoBallStateINIT()
{
    TFT_clearScreen();
    Cordinate_t pos = {300, 300};
    SPEED_t ball_speed = {0,0};

    
    //Initialisaing the BAT part of the SOCCER_object
    BAT_init(&SOCCER_object.bat, 50);
    BALL_init(&SOCCER_object.ball, pos, ball_speed);
 
    //Initialisaing the SCREEN part of the SOCCER_object
    SOCCER__ResetTimer_10s();
    SCREEN_init(&SOCCER_object.screen, &SOCCER_object.bat,&SOCCER_object.ball);
    SCREEN_update(&SOCCER_object.screen); 
    SCREEN_drawSoccerWall();

}

/*!
 * This static function Transmit a confirmation message (CobID: CAN_ID_PLAYER2_INFO) over CAN.
 * Initialises the game state without a ball.
 * Prepares payload with confirmation information.
 * Sets up and send the CAN message.
 */
static void SOCCER__CANtransmit_confirm()
{
    
    SOCCER__NoBallStateINIT();
    
    CAN_DATA_BYTES_MSG payload = {0};
    
    payload.byte[0] = 1;
    
    //Set up message
    CAN_TX_MSG msg;
    msg.id = CAN_ID_PLAYER2_INFO; //CobId
    msg.ide = 0; //11bit identifier (else 29)
    msg.rtr = 0; //Normal message
    msg.dlc = 1; //Length
    msg.msg = &payload; //Data to be transmitted
        
    CAN_SendMsg(&msg);

}

/*!
 * This static function receives CAN messages and handle different types.
 * Extracts metadata and payload.
 * CAN_ID_BALL_INFO  - The can message recieved when the ball crosses the Upper boundary in the other board
 * CAN_ID_PLAYER1_INFO - The can message recieved when the other board presses start first signifying it is a first player
 * CAN_ID_PLAYER2_INFO - The can message recieved when the other board presses start and ready to play and the current
 * 						 board is in waiting confirmation state, waiting for the message to start.
 * CAN_ID_GAMEOVER - The can message recieved when the other player is lost the round and now the current board
 * 					shows won message on screen for that round.
 * CAN_ID_GAMESTOP - The can message recieved when the other player is lost the game completely and now the current board
 * 					shows won message on screen.
 * Puts corresponding events into the ring buffer.
 * @return void
 */
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

    
    if(cobid == CAN_ID_PLAYER1_INFO)
    {

        RB_put(&soccer__ringbuffer,SOCCER_EV_CAN_CONNECTRX);
        
    }
    
    else if(cobid == CAN_ID_BALL_INFO)
    {
        //Creating some local values required for the init functions

        SCREEN_BALLInit(&SOCCER_object.screen, &SOCCER_object.ball);
        SOCCER_object.ball.previous_ball_pos.X = payload.byte[0];
        SOCCER_object.ball.previous_ball_pos.Y = 160 - payload.byte[1];
        SOCCER_object.ball.current_ball_pos.X = payload.byte[2];
        SOCCER_object.ball.current_ball_pos.Y = 160 - payload.byte[3];
        SOCCER_object.ball.ball_speed.pos.X = -payload.byte[4];
        SOCCER_object.ball.ball_speed.pos.Y = -payload.byte[5];
           
        RB_put(&soccer__ringbuffer,SOCCER_EV_CAN_BALL_RECIEVE);
    }
    
    
    else if(cobid == CAN_ID_PLAYER2_INFO)
    {
        RB_put(&soccer__ringbuffer,SOCCER_EV_CAN_ACK);
    }
    else if(cobid == CAN_ID_GAMEOVER)
    {
        RB_put(&soccer__ringbuffer,SOCCER_EV_CAN_GAMEOVERRX);
    }
    else if(cobid == CAN_ID_GAMESTOP)
    {
        RB_put(&soccer__ringbuffer,SOCCER_EV_CAN_GAMESTOPRX);
    }

    
}

/*!
 * This static function Transmits a game over message (CobID : CAN_ID_GAMEOVER)over CAN.
 * Prepares payload with game over information.
 * Sets up and send the CAN message.
 * @return void
 */
static void SOCCER__CANSend_gameover()
{
    CAN_DATA_BYTES_MSG payload = {0,0,0,0,0,0};
    
    //Set up message
    CAN_TX_MSG msg;
    msg.id = CAN_ID_GAMEOVER; //CobId
    msg.ide = 0; //11bit identifier (else 29)
    msg.rtr = 0; //Normal message
    msg.dlc = 6; //Length
    msg.msg = &payload; //Data to be transmitted    
    CAN_SendMsg(&msg);

}

/*!
 * This static function transmits a game stop message(CobID : CAN_ID_GAMESTOP)over CAN.
 * Prepares payload with game stop information.
 * Sets up and send the CAN message.
 * @return void
 */
static void SOCCER__CANSend_GameStop()
{
    CAN_DATA_BYTES_MSG payload = {0,0,0,0,0,0};
    
    //Set up message
    CAN_TX_MSG msg;
    msg.id = CAN_ID_GAMESTOP; //CobId
    msg.ide = 0; //11bit identifier (else 29)
    msg.rtr = 0; //Normal message
    msg.dlc = 6; //Length
    msg.msg = &payload; //Data to be transmitted    
    CAN_SendMsg(&msg); 
}
/*!
 * This static function calls a screen function which displays a welcome message on the screen.
 * @return void
 */
static void SOCCER__Show_welcome_message()
{
	SCREEN_SoccerShowWelcomeMessage();
}

