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
 * \file BALL.c
 * \author Suhas Bangalore Mruthunjaya
 * \date 03/05/2023
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
 */

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "ball.h"
#include "screen.h"
#include "logging.h"
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

/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/*!
 * Initialises the BALL position on the screen.
 * Initialises the BALL position, previous position, and speed.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @param pos: IN - Initial position of the BALL.
 * @param speed: IN - Initial speed of the BALL.
 * @return RC_t: Returns RC_SUCCESS if the initialisation is successful.
 */

RC_t BALL_init(BALL_t *const me, Cordinate_t pos, SPEED_t speed)
{
	me->current_ball_pos = pos;
	me->previous_ball_pos = pos;
	me->ball_speed.pos.X = speed.pos.X;
	me->ball_speed.pos.Y = speed.pos.Y;

	return RC_SUCCESS;

}

/*!
 * Updates the position of the BALL based on its current speed on the screen
 * @param *me: IN/OUT Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS if the BALL position is successfully updated.
 */
RC_t BALL_update_pos(BALL_t *const me)
{
	me->previous_ball_pos = me->current_ball_pos;

	me->current_ball_pos.X = me->current_ball_pos.X
			+ me->ball_speed.pos.X / 100;
	me->current_ball_pos.Y = me->current_ball_pos.Y
			+ me->ball_speed.pos.Y / 100;

	return RC_SUCCESS;
}

/*!
 * Gets the current position of the BALL.
 * @param *me: IN - Pointer pointing to the BALL object.
 * @return Cordinate_t: Returns the current position of the BALL.
 */
Cordinate_t BALL_getcurrentballpos(BALL_t const *const me)
{
	return me->current_ball_pos;
}

/*!
 * Gets the previous position of the BALL.
 * @param *me: IN - Pointer pointing to the BALL object.
 * @return Cordinate_t: Returns the previous position of the BALL.
 */
Cordinate_t BALL_getpreviousballpos(BALL_t const *const me)
{

	return me->previous_ball_pos;

}

/*!
 * Flips the X component of the BALL speed.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS after flipping the X component of the BALL speed.
 */
RC_t BALL_flipXSpeed(BALL_t *const me)
{
	me->ball_speed.pos.X *= -1;
	return RC_SUCCESS;
}

/*!
 * Flips the Y component of the BALL speed.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS after flipping the Y component of the BALL speed.
 */
RC_t BALL_flipYSpeed(BALL_t *const me)
{
	me->ball_speed.pos.Y *= -1;
	return RC_SUCCESS;
}

/*!
 * Sets a random angle for the BALL speed.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS after setting a random angle for the BALL speed.
 */
RC_t BALL_setAngle(BALL_t *const me)
{
	me->ball_speed.pos.X += (CySysTickGetValue() % 50);
	me->ball_speed.pos.Y += (CySysTickGetValue() % 25);
	if (me->ball_speed.pos.X > MAX_BALLSPEED)
	{
		me->ball_speed.pos.X = MIN_BALLSPEED;
	}
	if (me->ball_speed.pos.Y > MAX_BALLSPEED)
	{
		me->ball_speed.pos.Y = MIN_BALLSPEED;
	}
	return RC_SUCCESS;
}

/*!
 *  Stops the BALL by setting its speed to zero.
 * @param *me: IN/OUT - Pointer pointing to the BALL object.
 * @return RC_t: Returns RC_SUCCESS after stopping the BALL.
 */
RC_t BALL_STOP(BALL_t *const me)
{
	Cordinate_t current_ball_pos = BALL_getcurrentballpos(me);
	if (current_ball_pos.X == 0)
	{
		me->ball_speed.pos.Y = 0;
		me->ball_speed.pos.X = 0;
	}
	return RC_SUCCESS;
}
