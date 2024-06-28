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
 * \brief  File containing attributes and functions of Pong Class
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
#include "pong.h"
#include "button.h"
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

static PONG_GAME_t PONG_object =
{ };
STATE_state_t Pong_StateVar;

static RB_t PONG_EV_Ringbuffer;

static PONG_BOUNDARY PONG__BallReachedBoundary();

/* Action */
static void PONG__init();
static void PONG__play();
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
static const STATE_stateInnerTransitionTable_t PONG_IS_STARTING_Transitions =
{
		/*    Event                      ToState                 Guard               Action */
		{ PONG_EV_BUTTON_START, 	PONG_IS_PLAYING, 				0, 				PONG__init }, };

/**  ===== PONG_IS_PLAYING ====   */
static const STATE_stateInnerTransitionTable_t PONG_IS_PLAYING_Transitions =
{
		/*    Event                  		 ToState                 Guard                      	 Action  */
		{ PONG_EV_TICK, 				PONG_IS_PLAYING, 			NotGameOver,			 		PONG__play },
		{ PONG_EV_TICK, 				PONG_IS_GAMEOVER, 		GameOverAndLifeRemain,			PONG__ShowLoosingMessage },
		{ PONG_EV_TICK, 				PONG_IS_GAMEOVER, 		GameOverAndNoLifeRemain,		PONG__ShowGameScore }, };

/**  ===== PONG_IS_GAMEOVER ====   */
static const STATE_stateInnerTransitionTable_t PONG_IS_GAMEOVER_Transitions =
{
		/*    Event                   ToState                 Guard                       Action */
		{ PONG_EV_BUTTON_START, 	PONG_IS_PLAYING, 		LifeRemain, 				PONG__init },
		{ PONG_EV_BUTTON_START, 	PONG_IS_STARTING, 		NoLifeRemain, 			PONG__ClearLife }, };

static const STATE_stateOuterTransitionTable_t PongStateMachine_Transitions =
{
		/*      fromState                 Pointer to table                        Size of table [Elements] */
		{ PONG_IS_STARTING, 		&PONG_IS_STARTING_Transitions,			sizeof(PONG_IS_STARTING_Transitions)/ sizeof(STATE_stateInnerTransition_t) },
		{ PONG_IS_PLAYING, 			&PONG_IS_PLAYING_Transitions,			sizeof(PONG_IS_PLAYING_Transitions)/ sizeof(STATE_stateInnerTransition_t) },
		{ PONG_IS_GAMEOVER, 		&PONG_IS_GAMEOVER_Transitions,			sizeof(PONG_IS_GAMEOVER_Transitions)/ sizeof(STATE_stateInnerTransition_t) }, };

static const uint16_t PongStateMachine_Transitions_size =	sizeof(PongStateMachine_Transitions)/ sizeof(STATE_stateOuterTransition_t);

/** ---------------------------------- Action ------------------------------------------- **/

static const STATE_stateActionTable_t PongStateMachine_StateActions =
{
		/*  fromState               Entry                    		Exit    */
		{ PONG_IS_STARTING,		 PONG__ShowWelcomeMsg, 		PONG__LifeScoreInit },
		{ PONG_IS_PLAYING, 			0, 								0 },
		{ PONG_IS_GAMEOVER, 		0, 								0 }, };
static const uint16_t PongStateMachine_StateActions_size =	sizeof(PongStateMachine_StateActions) / sizeof(STATE_stateAction_t);


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/*********************** State machine Actions ******************************************/
/*!
 * This static function clears the life display (initialise seven-segment display).
 * @return void
 */
static void PONG__ClearLife()
{
	SEVEN_Init();
}

/*!
 * This static function decrements the life count and update the seven-segment display.
 * @return void
 */
static void PONG__DecrementLife()
{
	PONG_object.life--;
	SEVEN_Set(SEVEN_1, PONG_object.life);
}

/*!
 * This static function displays the welcome message on the PONG screen.
 * @return void
 */
static void PONG__ShowWelcomeMsg()
{
	SCREEN_PongShowWelcomeMessage();
}

/*!
 * This static function displays the losing message on the PONG screen.
 * Decrement life count.
 * Show a losing life message on the screen.
 * @return void
 */
static void PONG__ShowLoosingMessage()
{
	PONG__DecrementLife();
	SCREEN_PongShowLoosingLife();
}

/*!
 * This static function displays the game score on the PONG screen.
 * Decrement life count.
 * Adjust the score value (divide by 6 as explained in the code).
 * Show the updated score on the screen
 * @return void
 */
static void PONG__ShowGameScore()
{
	PONG__DecrementLife();
	//> Before the ball leaves the bat, the program is ran for a couple of times and the count is 6
	PONG_object.score = PONG_object.score / 6;
	SCREEN_PongShowGameScore(PONG_object.score);
}

/*!
 * This static function Initialises life and score for the PONG game.
 * Set life count.
 * Initialise the seven-segment display with the initial life count.
 * Set the initial score to 0.
 */
static void PONG__LifeScoreInit()
{
	PONG_object.life = PongGameLife;
	SEVEN_Set(SEVEN_1, PONG_object.life);
	PONG_object.score = 0;
}
/*********************** State machine Actions ******************************************/

/*********************** State machine Gaurds ******************************************/

/*!
 * This static function checks if the game is not over by verifying the ball's position.
 * @return boolean_t - False, if Ball is in the Game over spot (excluding the bat area)
 * True, otherwise
 */
static boolean_t NotGameOver()
{

	if (PONG__BallReachedBoundary() == PONG_BOUNDARY_GAME_OVER_SPOT)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

/*!
 * This static function checks if the game is over, but there are remaining lives.
 * @return boolean_t - True, if ball is in the game over spot and the life is more than one, False otherwise
 */
static boolean_t GameOverAndLifeRemain()
{

	if (PONG__BallReachedBoundary() == PONG_BOUNDARY_GAME_OVER_SPOT
			&& PONG_object.life > 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*!
 * This static function checks if the game is over, and there are no remaining lives.
 * @return boolean_t - True, if the ball is in the game over spot and the life is equal to 1, False otherwise
 */
static boolean_t GameOverAndNoLifeRemain()
{

	if (PONG__BallReachedBoundary() == PONG_BOUNDARY_GAME_OVER_SPOT
			&& PONG_object.life == 1)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

/*!
 * Check if there are remaining lives.
 * @return boolean_t - True, if the life is more than 0, False otherwise
 */
static boolean_t LifeRemain()
{

	if (PONG_object.life > 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}

/*!
 * Check if there are no remaining lives.
 * @return boolean_t - True, if the life is equal to 0, False otherwise
 */
static boolean_t NoLifeRemain()
{
	if (PONG_object.life == 0)
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
 * This static function Implements the logic for ball bouncing and collision detection.
 * Flips ball speed accordingly when reaching boundaries.
 * Stops the ball when reaching the game over spot.
 * @return RC_SUCCESS on success, an error code on failure.
 */
static RC_t PONG__BallBounceLogic();

/**
 * Updates the position of the bat, ball, and performs game logic.
 * @return RC_SUCCESS on success, an error code on failure.
 */
static RC_t PONG__logic();

/**
 * Process events and update the PONG game state. Takes the events from the ringBuffer and sends it to state_processEvent
 * (statemachine) function
 * @return RC_SUCCESS on success, an error code on failure.
 */
static RC_t PONG__Control();

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * This static function initialises the PONG game.
 * Clears the screen.
 * Initialises local values for bat and ball.
 * Initialises the screen, bat, and ball.
 * Draws the PONG wall on the screen.
 * @return void
 */
static void PONG__init()
{
	TFT_clearScreen(); //can be moved to screen file?
	//Creating some local values required for the init functions

	Cordinate_t pos =
	{ 10, 20 };
	SPEED_t ball_speed =
	{ MIN_BALLSPEED, MIN_BALLSPEED };

	//Initialisaing the BAT part of the PONG_object
	BAT_init(&PONG_object.bat, 50);

	//Initialisaing the BALL part of the PONG_object
	BALL_init(&PONG_object.ball, pos, ball_speed);

	//Initialisaing the SCREEN part of the PONG_object
	SCREEN_init(&PONG_object.screen, &PONG_object.bat, &PONG_object.ball);
	SCREEN_update(&PONG_object.screen);
	SCREEN_drawPongWall();
	//The joystick part will be updated by the driver, so no need for an explizit initialisation
}

/**
 * This static function Plays a tick of the PONG game.
 * Executes game logic.
 * Updates the screen.
 * @return void
 */
static void PONG__play()
{
	RC_t ret = PONG__logic();
	if (ret != RC_SUCCESS)
	{
		UART_LOG_PutString(" Error in Pong__logic function");
	}
	SCREEN_update(&PONG_object.screen);
}

/**
 * Updates the position of the bat, ball, and performs game logic.
 * @return RC_SUCCESS on success, an error code on failure.
 */
static RC_t PONG__logic()
{

	JOYSTICK_update(&PONG_object.joystick);
	BAT_update_pos(&PONG_object.bat, &PONG_object.joystick);

	PONG__BallBounceLogic();

	BALL_update_pos(&PONG_object.ball);

	return RC_SUCCESS;
}

/**
 * Process events and update the PONG game state.
 * @return RC_SUCCESS on success, an error code on failure.
 */
RC_t PONG_cyclic()
{

	//Prepare events
	static ButtonPressStates_t StartButtonStateVar = IDLE;
	uint16 EV = PONG_EV_NULL;
	RC_t ret;

	ret = BUTTON1_CheckShortPress(&StartButtonStateVar, &EV,
			PONG_EV_BUTTON_START);
	if (ret != RC_SUCCESS)
	{
		UART_LOG_PutString(" Error in Button press, PONG__cyclic function");
		return RC_ERROR;
	}

	//put in ring buffer
	if (EV == PONG_EV_BUTTON_START)
	{
		ret = RB_put(&PONG_EV_Ringbuffer, (uint8_t) PONG_EV_BUTTON_START);//write into the buffer
		if (ret != RC_SUCCESS)
		{
			UART_LOG_PutString(" Error in RB_put, in PONG__cyclic function");
			return RC_ERROR;
		}
	}

	ret = RB_put(&PONG_EV_Ringbuffer, (uint8_t) PONG_EV_TICK);//write into the buffer
	if (ret != RC_SUCCESS)
	{
		UART_LOG_PutString(" Error in RB_put, in PONG__cyclic function");
		return RC_ERROR;
	}

	//call process event until ringbuffer is empty
	ret = PONG__Control();
	if (ret != RC_SUCCESS)
	{
		UART_LOG_PutString(" Error in PONG__Control, in PONG__cyclic function");
		return RC_ERROR;
	}

	return RC_SUCCESS;
}

/**
 * Process events and update the PONG game state. Takes the events from the ringBuffer and sends it to state_processEvent
 * (statemachine) function
 * @return RC_SUCCESS on success, an error code on failure.
 */
static RC_t PONG__Control()
{
	uint8_t EV;
	//call process event until ringbuffer is empty
	while (RB_prots_available(&PONG_EV_Ringbuffer))	//read all the remaining protocols available in the RingBuffer
	{
		RC_t ret = RB_get(&PONG_EV_Ringbuffer, &EV);
		switch (EV)
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
					PongStateMachine_StateActions_size, (PONG_event_t) EV,
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
 * This function Initialises the state of the PONG game.
 * Initialises the ring buffer for events.
 * Initialises the state machine with initial data.
 */
RC_t Pong_InitState()
{
	RC_t ret;
	ret = RB_init(&PONG_EV_Ringbuffer, 50);
	if (ret != RC_SUCCESS)
	{
		UART_LOG_PutString("Error in RB_init, in Pong_InitState function");
		return RC_ERROR;
	}
	ret = STATE_initState(PongStateMachine_StateActions,
			PongStateMachine_StateActions_size, &Pong_StateVar,
			PongStateMachine_INIT_DATA);
	if (ret != RC_SUCCESS)
	{
		UART_LOG_PutString(
				"Error in statemachine initialisation, in Pong_InitState function");
		return RC_ERROR;
	}

	return RC_SUCCESS;
}

/**
 * Check if the ball has reached a specific boundary and determine the result.
 * @return Result indicating the specific boundary reached by the ball.
 */
PONG_BOUNDARY PONG__BallReachedBoundary()
{
	PONG_BOUNDARY res = PONG_BOUNDARY_none;
	//Checking for a normal boundary situation
	if (PONG_object.ball.current_ball_pos.Y
			>= (SCREEN_WIDTH - WALL_WIDTH - BALL_WIDTH))
	{
		res = PONG_BOUNDARY_right;
	}
	else if (PONG_object.ball.current_ball_pos.X
			>= (SCREEN_HEIGHT - WALL_WIDTH - BALL_WIDTH))
	{
		//LOG_I("ball cordinates","%d,%d,%d,%d,%d,%d", PONG_object.ball.previous_ball_pos.X,PONG_object.ball.previous_ball_pos.Y,
		//PONG_object.ball.current_ball_pos.X,PONG_object.ball.current_ball_pos.Y, PONG_object.ball.ball_speed.pos.X, PONG_object.ball.ball_speed.pos.Y);

		res = PONG_BOUNDARY_up;
	}
	else if (PONG_object.ball.current_ball_pos.Y <= WALL_WIDTH)
	{
		res = PONG_BOUNDARY_left;
	}
	else if ((PONG_object.ball.current_ball_pos.X <= BALL_WIDTH)
			&& (PONG_object.bat.current_bat_pos
					<= PONG_object.ball.current_ball_pos.Y + BALL_WIDTH)
			&& ((PONG_object.bat.current_bat_pos + BAT_HEIGHT)
					>= PONG_object.ball.current_ball_pos.Y))
	{
		PONG_object.score++;
		res = PONG_BOUNDARY_down;
	}

	//Check for special cases, overwriting the normal boundary
	if ((PONG_object.ball.current_ball_pos.X <= BALL_WIDTH)
			&& ((PONG_object.bat.current_bat_pos
					> (PONG_object.ball.current_ball_pos.Y + BALL_WIDTH))
					|| ((PONG_object.bat.current_bat_pos + BAT_HEIGHT)
							< PONG_object.ball.current_ball_pos.Y)))
	{
		res = PONG_BOUNDARY_GAME_OVER_SPOT;

	}
	return res;
}

/**
 * This static function Implements the logic for ball bouncing and collision detection.
 * Flips ball speed accordingly when reaching boundaries.
 * Stops the ball when reaching the game over spot.
 * @return RC_SUCCESS on success, an error code on failure.
 */
static RC_t PONG__BallBounceLogic()
{
	RC_t ret;
	if (PONG__BallReachedBoundary() == PONG_BOUNDARY_right)
	{
		ret = BALL_flipYSpeed(&PONG_object.ball);
		if (ret != RC_SUCCESS)
		{
			return RC_ERROR;
		}

	}
	if (PONG__BallReachedBoundary() == PONG_BOUNDARY_left)
	{
		ret = BALL_flipYSpeed(&PONG_object.ball);
		if (ret != RC_SUCCESS)
		{
			return RC_ERROR;
		}

	}
	if (PONG__BallReachedBoundary() == PONG_BOUNDARY_up)
	{
		ret = BALL_flipXSpeed(&PONG_object.ball);
		if (ret != RC_SUCCESS)
		{
			return RC_ERROR;
		}

	}
	if (PONG__BallReachedBoundary() == PONG_BOUNDARY_down)
	{
		ret = BALL_flipXSpeed(&PONG_object.ball);
		if (ret != RC_SUCCESS)
		{
			return RC_ERROR;
		}

	}
	if (PONG__BallReachedBoundary() == PONG_BOUNDARY_GAME_OVER_SPOT)
	{

		ret = BALL_STOP(&PONG_object.ball);
		if (ret != RC_SUCCESS)
		{
			return RC_ERROR;
		}

	}
	return RC_SUCCESS;
}

/**
 * This function de-initialises the PONG game.
 * de-initialises the ring buffer for events.
 * clears the life display.
 * @return RC_Success if everything is ok
 */
RC_t Pong_DeInit()
{
	RC_t ret = RB_deinit(&PONG_EV_Ringbuffer);
	if (ret != RC_SUCCESS)
	{
		return RC_ERROR;
	}
	PONG__ClearLife();
	return RC_SUCCESS;
}

