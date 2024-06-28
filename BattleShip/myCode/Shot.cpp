/*
 * Shot.cpp
 *
 *  Created on: 19 Dec 2023
 *      Author: suhas
 */

#include "Shot.h"

/*!
 * @brief Constructor for the Shot class.
 *
 * @param targetPosition The target position of the shot.
 */

Shot::Shot(GridPosition targetPosition)
{
	// TODO Auto-generated constructor stub

	this->targetPosition = targetPosition;

}

/*!
 * @brief Destructor for the Shot class.
 */
Shot::~Shot()
{
	// TODO Auto-generated destructor stub
}

/*!
 * @brief Gets the target position of the shot.
 *
 * @return The target position.
 */
GridPosition Shot::getTargetPosition() const
{
	return targetPosition;
}

