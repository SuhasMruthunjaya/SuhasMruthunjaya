/**
 * \file <filename>
 * \author <author-name>
 * \date <date>
 *
 * \brief  File containing attributes and functions of Pong Class
 *
 * detailed description what the file does
 *
 * \note <notes>
 * Programming rules (may be deleted in the final release of the file)
 * ===================================================================
 *
 * 1. Naming conventions:
 *    - Prefix of your module in front of every function and static data.
 *    - Scope _ for public and __ for private functions / data / types, e.g.
 *       Public:  void CONTROL_straightPark_Init();
 *       Private: static void CONTROL__calcDistance();
 *       Public:  typedef enum {RED, GREEN, YELLOW} CONTROL_color_t
 *    - Own type definitions e.g. for structs or enums get a postfix _t
 *    - #define's and enums are written in CAPITAL letters
 * 2. Code structure
 *    - Be aware of the scope of your modules and functions. Provide only functions which belong to your module to your files
 *    - Prepare your design before starting to code
 *    - Implement the simple most solution (Too many if then else nestings are an indicator that you have not properly analysed your task)
 *    - Avoid magic numbers, use enums and #define's instead
 *    - Make sure, that all error conditions are properly handled
 *    - If your module provides data structures, which are required in many other files, it is recommended to place them in a file_type.h file
 *	  - If your module contains configurable parts, is is recommended to place these in a file_config.h|.c file
 * 3. Data conventions
 *    - Minimize the scope of data (and functions)
 *    - Global data is not allowed outside of the signal layer (in case a signal layer is part of your design)
 *    - All static objects have to be placed in a valid linker sections
 *    - Data which is accessed in more than one task has to be volatile and needs to be protected (e.g. by using messages or semaphores)
 *    - Do not mix signed and unsigned data in the same operation
 * 4. Documentation
 *    - Use self explaining function and variable names
 *    - Use proper indentation
 *    - Provide Javadoc / Doxygen compatible comments in your header file and C-File
 *    		- Every  File has to be documented in the header
 *			- Every function parameter and return value must be documented, the valid range needs to be specified
 *     		- Logical code blocks in the C-File must be commented
 *    - For a detailed list of doxygen commands check http://www.stack.nl/~dimitri/doxygen/index.html
 * 5. Qualification
 *    - Perform and document design and code reviews for every module
 *    - Provide test specifications for every module (focus on error conditions)
 *
 * Further information:
 *    - Check the programming rules defined in the MIMIR project guide
 *         - Code structure: https://fromm.eit.h-da.de/intern/mimir/methods/eng_codestructure/method.htm
 *         - MISRA for C: https://fromm.eit.h-da.de/intern/mimir/methods/eng_c_rules/method.htm
 *         - MISRA for C++: https://fromm.eit.h-da.de/intern/mimir/methods/eng_cpp_rules/method.htm
 *
 * \todo <todos>
 * \warning <warnings, e.g. dependencies, order of execution etc.>
 *
 *  Changelog:\n
 *  - <version; data of change; author>
 *            - <description of the change>
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

#ifndef PONG_H
#define PONG_H

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

//####################### Enumerations
/*!
 * Enumerates the possible boundary conditions for the PONG game
 */
typedef enum
{
	PONG_BOUNDARY_none,
	PONG_BOUNDARY_left,
	PONG_BOUNDARY_up,
	PONG_BOUNDARY_right,
	PONG_BOUNDARY_down,
	PONG_BOUNDARY_GAME_OVER_SPOT
} PONG_BOUNDARY;

/**
 * Enum created to mention all events related to PONG state machine
 */
typedef enum
{
	PONG_EV_NULL, PONG_EV_BUTTON_START, PONG_EV_TICK,
} PONG_event_t;

/**
 * Enum created to mention all the states related to PONG state machine
 */
typedef enum
{
	PONG_IS_STARTING, PONG_IS_PLAYING, PONG_IS_GAMEOVER,
} PONG_state_t;

#define PongStateMachine_INIT_DATA    PONG_IS_STARTING
//####################### Structures
/*!
 * Contains instances of various game components, such as joystick, bat, ball, and screen.
 */

typedef struct
{
	JOYSTICK_t joystick;			//< Instance of the joystick.
	BAT_t bat;					//< Instance of the bat.
	BALL_t ball;					//< Instance of the ball.
	SCREEN_t screen;				//< Instance of the screen.
	sint8_t life;				//< Life count for the PONG game.
	uint16_t score;				//< Score for the PONG game.
} PONG_GAME_t;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/
/**
 * This function Initialises the state of the PONG game.
 * Initialises the ring buffer for events.
 * Initialises the state machine with initial data.
 */
RC_t Pong_InitState();
/**


 /*!
 * Process events and update the PONG game state.
 * @return RC_SUCCESS on success, an error code on failure.
 */
RC_t PONG_cyclic();

/**
 * This function de-initialises the PONG game.
 * de-initialises the ring buffer for events.
 * clears the life display.
 * @return RC_Success if everything is ok
 */
RC_t Pong_DeInit();

#endif /* FILE_H */