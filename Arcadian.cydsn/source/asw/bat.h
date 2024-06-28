/**
 * \file <filename>
 * \author <author-name>
 * \date <date>
 *
 * \brief File containing Functions and Attributes for the Bat model
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

#ifndef BAT_H
#define BAT_H

#include "global.h"
#include "position.h"
#include "joystick.h"

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/

//####################### Defines/Macros
/** 
 * \brief a brief description of what the define is representing
 *
 * If needed, a more detailed description can be given below */

/*!
 * Height of the bat in pixels.
 */
#define BAT_HEIGHT 40

/*!
 * Width of the bat in pixels.
 */
#define BAT_WIDTH 10
/*!
 * @brief Minimum position of the bat.
 */
#define BAT_MINPOS 0
/*!
 * @brief Maximum position of the bat.
 */
#define BAT_MAXPOS (160 - BAT_HEIGHT)
/*!
 * @brief Width of the wall in pixels.
 */
#define WALL_WIDTH 5

//####################### Enumerations
/**
 * \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
 *
 * Detailed explaination of the enumeration.
 */

//####################### Structures
/*!
 * Structure to represent the BAT in the PONG game.
 *
 * This structure holds the current position, previous position, and speed of the BAT.
 * The BAT is controlled by a JOYSTICK in the PONG game.
 */
typedef struct
{
	uint16_t current_bat_pos;
	uint16_t previous_bat_pos;
	//< since BAT_MAXPOS is less than 255, uint8_t is enough
	uint8_t BAT_speed;

} BAT_t;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/*!
 * Initialises the BAT position on the screen
 * @param *me : IN/OUT - Pointer pointing to the bat object
 * @param pos : IN - pos of type uint16_t
 * @return RC_t : returns RC_Success if the initialisation is successfull
 */
RC_t BAT_init(BAT_t *me, uint16_t pos);

/*!
 * Update the current position of the Bat based on the Joystick direction
 * @param BAT_t* me - IN/OUT Address of the bat object created
 * @param JOYSTICK_t const* const joystick_pos - IN Joystick object
 * @return RC_SUCCESS if all ok
 */
RC_t BAT_update_pos(BAT_t *me, JOYSTICK_t const *const joystick_pos);

/*! Get the bat current position
 *  @param BAT_t *me - IN/OUT pointer to the BAT object
 *  @return uint16_t pos -  returns current position of the bat, it is of type uint16_t
 */
uint16_t BAT_GetCurrentPosition(BAT_t *me);

/*! Get the bat previous position
 *  @param BAT_t *me - IN/OUT pointer to the BAT object
 *  @return uint16_t pos - returns previous position of the bat, it is of type uint16_t
 */
uint16_t BAT_GetPreviousPosition(BAT_t *me);

/*!
 * Get the Bat Speed
 * @param BAT_t const* const me - IN Address of the bat object created
 * @return uint8_t Bat_speed value
 */

uint8_t BAT_GetBatSpeed(BAT_t const *const me);

/*!
 * Calculate the speed with which the Bat should be moved based on the Joystick command
 * @param BAT_t* me - IN/OUT Address of the bat object created
 * @param JOYSTICK_t const* const joystick_pos - IN Joystick object
 * @return RC_SUCCESS if all ok
 */
RC_t BAT_UpdateSpeed(BAT_t *me, JOYSTICK_t const *const joystick_pos);

#endif /* FILE_H */
