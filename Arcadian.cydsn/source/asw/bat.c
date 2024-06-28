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
 * \file BAT.c
 * \author Suhas Bangalore Mruthunjaya
 * \date 03/05/2023
 *
 * \brief File containing Functions and Attributes for the Bat model
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

#include "bat.h"

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
 * Initialises the BAT position on the screen
 * @param *me : IN/OUT - Pointer pointing to the bat object
 * @param pos : IN - pos of type uint16_t
 * @return RC_t : returns RC_Success if the initialisation is successfull
 */

RC_t BAT_init(BAT_t *me, uint16_t pos)
{
	me->current_bat_pos = pos;
	me->previous_bat_pos = pos;

	me->BAT_speed = 1;

	return RC_SUCCESS;

}

/*!
 * Update the current position of the Bat based on the Joystick direction
 * @param BAT_t* me - IN/OUT Address of the bat object created
 * @param JOYSTICK_t const* const joystick_pos - IN Joystick object
 * @return RC_SUCCESS if all ok
 */

RC_t BAT_update_pos(BAT_t *me, JOYSTICK_t const *const joystick_pos)
{

	BAT_UpdateSpeed(me, joystick_pos);

	if ((JOYSTICK_GetYCordinate(joystick_pos) > 10)
			&& ((me->current_bat_pos - me->BAT_speed)
					> (BAT_MINPOS + WALL_WIDTH)))
	{

		me->previous_bat_pos = me->current_bat_pos + BAT_HEIGHT - me->BAT_speed;
		me->current_bat_pos -= me->BAT_speed;

	}

	else if ((JOYSTICK_GetYCordinate(joystick_pos) < -10)
			&& ((me->current_bat_pos + me->BAT_speed)
					< (BAT_MAXPOS - WALL_WIDTH)))
	{

		me->previous_bat_pos = me->current_bat_pos;
		me->current_bat_pos += me->BAT_speed;

	}

	return RC_SUCCESS;
}

/*! Get the bat current position
 *  @param BAT_t *me - IN/OUT pointer to the BAT object
 *  @return uint16_t pos -  returns current position of the bat, it is of type uint16_t 
 */
uint16_t BAT_GetCurrentPosition(BAT_t *me)
{
	uint16_t pos;
	pos = me->current_bat_pos;
	return pos;

}

/*! Get the bat previous position
 *  @param BAT_t *me - IN/OUT pointer to the BAT object
 *  @return uint16_t pos - returns previous position of the bat, it is of type uint16_t
 */

uint16_t BAT_GetPreviousPosition(BAT_t *me)
{
	uint16_t pos;
	pos = me->previous_bat_pos;
	return pos;

}

/*!
 * Calculate the speed with which the Bat should be moved based on the Joystick command
 * @param BAT_t* me - IN/OUT Address of the bat object created
 * @param JOYSTICK_t const* const joystick_pos - IN Joystick object
 * @return RC_SUCCESS if all ok
 */
RC_t BAT_UpdateSpeed(BAT_t *me, JOYSTICK_t const *const joystick_pos)
{
	sint8_t JoystickYCordinate = 0;

	JoystickYCordinate = JOYSTICK_GetYCordinate(joystick_pos);

	if (JoystickYCordinate > -50 && JoystickYCordinate < 50)
	{
		me->BAT_speed = 1;

	}
	else if ((JoystickYCordinate > -110 && JoystickYCordinate < -50)
			|| (JoystickYCordinate > 50 && JoystickYCordinate < 110))
	{
		me->BAT_speed = 2;

	}

	else if (JoystickYCordinate < -110 || JoystickYCordinate > 110)
	{
		me->BAT_speed = 4;

	}
	return RC_SUCCESS;
}

/*!
 * Get the Bat Speed
 * @param BAT_t const* const me - IN Address of the bat object created
 * @return uint8_t Bat_speed value
 */

uint8_t BAT_GetBatSpeed(BAT_t const *const me)
{
	return me->BAT_speed;

}

