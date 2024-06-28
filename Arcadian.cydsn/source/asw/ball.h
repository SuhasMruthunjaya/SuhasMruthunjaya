/**
 * \file ball.h
 * \author SUHAS BANGALORE MRUTHUNJAYA
 * \date 16/05/2023
 *
 * \brief File containing Functions and Attributes for the Ball model
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

#ifndef BALL_H
#define BALL_H

#include "global.h"
#include "position.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines/Macros
/*!
 * BALL_HEIGHT: BALL height in pixels.
 * BALL_WIDTH: BALL width in pixels.
 * MIN_BALLSPEED: Minimum speed of the BALL.
 * MAX_BALLSPEED: Maximum speed of the BALL.
 */

#define BALL_HEIGHT 9
#define BALL_WIDTH 9
#define MIN_BALLSPEED 100
#define MAX_BALLSPEED 250

//####################### Structures
/*!
 * Structure to represent the speed of the BALL.
 * Holds the X and Y components of the BALL's speed.
 */

typedef struct
{
	Cordinate_t pos;
} SPEED_t;

/*!
 * Structure to represent the BALL object.
 * Holds the current and previous positions of the BALL, as well as its speed.
 */
typedef struct
{
	Cordinate_t current_ball_pos;
	Cordinate_t previous_ball_pos;
	SPEED_t ball_speed;

} BALL_t;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/*!
 * Initialises the BALL position on the screen.
 * Initialises the BALL position, previous position, and speed.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @param pos: IN - Initial position of the BALL.
 * @param speed: IN - Initial speed of the BALL.
 * @return RC_t: Returns RC_SUCCESS if the initialisation is successful.
 */

RC_t BALL_init(BALL_t *const me, Cordinate_t pos, SPEED_t speed);

/*!
 * Updates the position of the BALL based on its current speed on the screen
 * @param *me: IN/OUT Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS if the BALL position is successfully updated.
 */
RC_t BALL_update_pos(BALL_t *const me);

/*!
 * Gets the current position of the BALL.
 * @param *me: IN - Pointer pointing to the BALL object.
 * @return Cordinate_t: Returns the current position of the BALL.
 */
Cordinate_t BALL_getcurrentballpos(BALL_t const *const me);

/*!
 * Gets the previous position of the BALL.
 * @param *me: IN - Pointer pointing to the BALL object.
 * @return Cordinate_t: Returns the previous position of the BALL.
 */
Cordinate_t BALL_getpreviousballpos(BALL_t const *const me);

/*!
 * Flips the X component of the BALL speed.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS after flipping the X component of the BALL speed.
 */
RC_t BALL_flipXSpeed(BALL_t *const me);

/*!
 * Flips the Y component of the BALL speed.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS after flipping the Y component of the BALL speed.
 */
RC_t BALL_flipYSpeed(BALL_t *const me);
/*!
 * Sets a random angle for the BALL speed.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS after setting a random angle for the BALL speed.
 */
RC_t BALL_setAngle(BALL_t *const me);
/*!
 *  Stops the BALL by setting its speed to zero.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS after stopping the BALL.
 */
RC_t BALL_STOP(BALL_t *const me);

#endif /* FILE_H */
