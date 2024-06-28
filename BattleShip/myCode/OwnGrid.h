/*
 * OwnGrid.h
 *
 *  Created on: 14 Dec 2023
 *      Author: suhas
 */

#ifndef MYCODE_OWNGRID_H_
#define MYCODE_OWNGRID_H_

#include "Ship.h"
#include "Shot.h"
#include <vector>
#include <map>
#include <set>

/*!
 * @brief Represents the player's own grid in the game, including ship placement and shot outcomes.
 *
 * The OwnGrid class manages information about the player's own grid, including the placement of
 * ships, shot outcomes, and methods for processing shots and determining if all ships are sunk.
 */

class OwnGrid
{

private:
	int rows;				//!< The number of rows in the player's own grid.
	int columns;			//!< The number of columns in the player's own grid.
	std::vector<Ship> ownShips;	//!< Vector to store information about player's own ships.
	std::set<GridPosition> shotAt;//!< Set to store positions shot at by the opponent.

	std::map<int, int> shipData;//!< Map to store the count of available ships of each length.

	/*!
	 * @brief Checks if a ship placement is valid within the boundaries of the own grid.
	 *
	 * @param ship The Ship object representing the ship to be placed.
	 * @return True if the ship placement is valid, false otherwise.
	 */
	bool posIsValid(Ship const &ship) const;

	/*!
	 * @brief Checks if a ship of a specific length is still available to be placed.
	 *
	 * @param ship The Ship object representing the ship to be placed.
	 * @return True if the ship is available, false otherwise.
	 */
	bool isShipAvailable(Ship const &ship);

	/*!
	 * @brief Checks if a shot results in the final hit on a ship, indicating that it is sunk.
	 *
	 * @param ship The Ship object representing the ship being targeted.
	 * @return True if the final hit, false otherwise.
	 */
	bool IsFinalHit(Ship const &ship);

	/*!
	 * @brief Initializes the shipData map with the count of available ships of each length.
	 */
	void shipDataInit();

public:

	/*!
	 * @brief Constructor for the OwnGrid class.
	 *
	 * Initializes an OwnGrid object with the specified number of rows and columns.
	 *
	 * @param rows The number of rows in the player's own grid.
	 * @param columns The number of columns in the player's own grid.
	 */
	OwnGrid(int rows = 0, int columns = 0);

	/*!
	 * @brief Destructor for the OwnGrid class.
	 */
	virtual ~OwnGrid();

	/*!
	 * @brief Gets the number of columns in the player's own grid.
	 *
	 * @return The number of columns in the player's own grid.
	 */

	int getColumns() const;

	/*!
	 * @brief Gets the number of rows in the player's own grid.
	 *
	 * @return The number of rows in the player's own grid.
	 */
	int getRows() const;

	/*!
	 * @brief Places a ship on the player's own grid.
	 *
	 * Checks for validity, availability, and intersections with existing ships before placement.
	 *
	 * @param ship The Ship object representing the ship to be placed.
	 * @return True if the ship is successfully placed, false otherwise.
	 */
	bool placeShip(Ship const &ship);

	/*!
	 * @brief Gets a vector of ships placed on the player's own grid.
	 *
	 * @return A vector containing information about player's own ships.
	 */

	const std::vector<Ship> getShip() const;

	/*!
	 * @brief Processes the result of a shot received from the opponent.
	 *
	 * Updates shot information, checks for sunk ships, and returns the impact of the shot.
	 *
	 * @param shot The Shot object representing the shot received from the opponent.
	 * @return The Impact of the shot (HIT, NONE, SUNKEN).
	 */
	Impact takeBlow(const Shot &shot);

	/*!
	 * @brief Gets a set of positions that have been shot at by the opponent.
	 *
	 * @return A set containing positions that have been shot at.
	 */

	const std::set<GridPosition> getShotAt();

	// UserInteractive Game Console (extended requirement:Command_Line_InterPreter) method

	/*!
	 * @brief Checks if all ships on the player's own grid are sunk.
	 *
	 * @return True if all ships are sunk, false otherwise.
	 */

	bool isShipsSunk();

};

#endif /* MYCODE_OWNGRID_H_ */
