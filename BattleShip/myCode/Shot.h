/*
 * Shot.h
 *
 *  Created on: 19 Dec 2023
 *      Author: suhas
 */

#ifndef MYCODE_SHOT_H_
#define MYCODE_SHOT_H_

#include "GridPosition.h"

/*!
 * @brief Enum representing the impact of a shot in the game.
 *
 * The Impact enum indicates the result or impact of a shot in the game, which can be one of the following values: NONE, HIT, or SUNKEN.
 */
typedef enum
{
	NONE,		//!< No impact, indicating a miss.
	HIT,		//!< Impact indicating a hit on an opponent's ship.
	SUNKEN		//!< Impact indicating that an opponent's ship has been sunk.

} Impact;

/*!
 * @brief Represents a shot in the game with a target position.
 *
 * The Shot class manages information about a shot, including its target position.
 */
class Shot
{
private:
	GridPosition targetPosition;		//!< The target position of the shot.
public:

	/*!
	 * @brief Constructor for the Shot class.
	 *
	 * @param targetPosition The target position of the shot.
	 */
	Shot(GridPosition targetPosition);

	/*!
	 * @brief Destructor for the Shot class.
	 */
	virtual ~Shot();

	/*!
	 * @brief Gets the target position of the shot.
	 *
	 * @return The target position.
	 */

	GridPosition getTargetPosition() const;

};

#endif /* MYCODE_SHOT_H_ */
