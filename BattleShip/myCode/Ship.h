/*
 * Ship.h
 *
 *  Created on: 12 Dec 2023
 *      Author: suhas
 */

#ifndef SHIP_H_
#define SHIP_H_

#include "GridPosition.h"
#include <set>

/*!
 * @brief Represents a ship in the game with a bow and stern position.
 *
 * The Ship class manages information about a ship, including its bow and stern positions,
 * validity checks, length calculations, and methods to obtain occupied and blocked areas.
 */
class Ship
{
private:
	GridPosition bow;		//!< The position of the bow of the ship.
	GridPosition stern;		//!< The position of the stern of the ship

public:

	/*!
	 * @brief Constructor for the Ship class.
	 *
	 * @param bow The position of the bow of the ship.
	 * @param stern The position of the stern of the ship.
	 */
	Ship(const GridPosition &bow, const GridPosition &stern);

	/*!
	 * @brief Destructor for the Ship class.
	 */
	virtual ~Ship();

	/*!
	 * @brief Checks if the ship is valid based on its positions and length.
	 *
	 * @return True if the ship is valid, false otherwise.
	 */
	bool isValid() const;

	/*!
	 * @brief Gets the position of the bow of the ship.
	 *
	 * @return The position of the bow.
	 */
	GridPosition getBow() const;

	/*!
	 * @brief Gets the position of the stern of the ship.
	 *
	 * @return The position of the stern.
	 */
	GridPosition getStern() const;

	/*!
	 * @brief Calculates and returns the length of the ship.
	 *
	 * @return The length of the ship.
	 */
	int length() const;

	/*!
	 * @brief Gets the set of positions occupied by the ship.
	 *
	 * @return A set containing positions occupied by the ship.
	 */
	std::set<GridPosition> occupiedArea() const;

	/*!
	 * @brief Gets the set of positions blocked by the ship.
	 *
	 * @return A set containing positions blocked by the ship.
	 */
	std::set<GridPosition> blockedArea() const;
};

#endif /* SHIP_H_ */
