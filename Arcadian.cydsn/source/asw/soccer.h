/**
 * \file <filename>
 * \author <author-name>
 * \date <date>
 *
 * \brief File containing attributes and functions of Soccer Class
 *
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
 **/

#ifndef SOCCER_H
#define SOCCER_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

#include "global.h"
#include "bat.h"
#include "ball.h"
#include "screen.h"
#include "tft.h"
#include "joystick.h"

//####################### Defines/Macros
/** 
 * \brief a brief description of what the define is representing
 *
 * If needed, a more detailed description can be given below */

//####################### Enumerations
/*!
 * Enumeration defining soccer game boundaries.
 */
typedef enum
{
	SOCCER_BOUNDARY_none,
	SOCCER_BOUNDARY_left,
	SOCCER_BOUNDARY_up,
	SOCCER_BOUNDARY_right,
	SOCCER_BOUNDARY_down,
	SOCCER_BOUNDARY_GAME_OVER_SPOT
} SOCCER_BOUNDARY;

/*!
 * Enumeration defining soccer game events.
 */
typedef enum
{
	SOCCER_EV_NONE,
	SOCCER_EV_TICK,
	SOCCER_EV_START_BUTTON,
	SOCCER_EV_CAN_ACK,
	SOCCER_EV_CAN_CONNECTRX,
	SOCCER_EV_CAN_GAMEOVERRX,
	SOCCER_EV_CAN_GAMESTOPRX,
	SOCCER_EV_BALL_TRANSMIT,
	SOCCER_EV_CAN_BALL_RECIEVE,
	SOCCER_EV_TIMEOUT

} SOCCER_Event_t;

/*!
 * Type definition for state event.
 */
typedef uint8_t STATE_event_t;

/*!
 * Enumeration defining soccer game states.
 */
typedef enum
{
	IS_STARTING,
	IS_WAITING_CONFIRMATION,
	IS_BALL_PRESENT,
	IS_BALL_NOTPRESENT,
	IS_GAME_OVER,
	IS_ERROR_STATE

} SOCCER_STATE_data_t;

/*!
 * Type definition for state.
 */
typedef uint8_t STATE_state_t;

/*!
 * Initial state for the soccer state machine.
 */
#define SOCCER_STATEMACHINE_INIT_DATA IS_STARTING

//####################### Structures
/*!
 * Structure representing the soccer game.
 */

typedef struct
{
	JOYSTICK_t joystick;
	BAT_t bat;
	BALL_t ball;
	SCREEN_t screen;
	uint8_t state;
	SOCCER_Event_t event;
	uint8_t life;
	boolean_t Flag_GameStop;

} SOCCER_GAME_t;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/*!
 * Function to initialize the soccer game.
 * @return RC_t -  RC_SUCCESS if successful.
 */
RC_t SOCCER_init();

/*!
 * Function to deinitialize the soccer game.
 * @return RC_t -  RC_SUCCESS if successful.
 */
RC_t Soccer_DeInit();
/*!
 * Function for the cyclic execution of the soccer game.
 * Generates events and puts them in the ring buffer.
 * @return RC_t - RC_SUCCESS if successful.
 */
RC_t SOCCER_cyclic();

#endif /* FILE_H */
