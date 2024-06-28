/*
 * OpponentGrid.h
 *
 *  Created on: 14 Dec 2023
 *      Author: suhas
 */

#ifndef OPPONENTGRID_H_
#define OPPONENTGRID_H_

#include "Ship.h"
#include "Shot.h"
#include <vector>
#include <map>

/*!
 * @brief Represents the opponent's grid in the game, including shots fired and sunken ships.
 *
 * The OpponentGrid class manages information about the opponent's grid, including shot results,
 * sunken ships, and methods for processing shot outcomes.
 */
class OpponentGrid
{
private:
	int rows;					//!< The number of rows in the opponent's grid.
	int columns;			//!< The number of columns in the opponent's grid.
	std::map<GridPosition, Impact> shots;//!< Map to store shot positions and their impacts.
	std::vector<Ship> sunkenShips;//!< Vector to store information about sunken ships.

	/*!
	 * @brief Helper method to identify and record the positions of an opponent's ship.
	 *
	 * This method is called when a shot results in a sunken ship, and it helps identify the
	 * boundaries of the sunken ship based on the provided target position and shifts.
	 *
	 * @param targetPosition The target position where the shot resulted in a sunken ship.
	 * @param ship_pos A set to store the positions occupied by the sunken ship.
	 * @param horizontalShift The horizontal shift for identifying ship positions.
	 * @param verticalShift The vertical shift for identifying ship positions.
	 */
	void findOpponentShip(GridPosition targetPosition,
			std::set<GridPosition> &ship_pos, int horizontalShift,
			int verticalShift);

public:

	/*!
	 * @brief Constructor for the OpponentGrid class.
	 *
	 * Initializes an OpponentGrid object with the specified number of rows and columns.
	 *
	 * @param rows The number of rows in the opponent's grid.
	 * @param columns The number of columns in the opponent's grid.
	 */
	OpponentGrid(int rows = 0, int columns = 0);

	/*!
	 * @brief Destructor for the OpponentGrid class.
	 */
	virtual ~OpponentGrid();

	/*!
	 * @brief Gets the number of columns in the opponent's grid.
	 *
	 * @return The number of columns in the opponent's grid.
	 */
	int getColumns() const;

	/*!
	 * @brief Gets the number of rows in the opponent's grid.
	 *
	 * @return The number of rows in the opponent's grid.
	 */
	int getRows() const;

	/*!
	 * @brief Processes the result of a shot fired by the player.
	 *
	 * Updates the shot information in the opponent's grid, including hits, misses, and sunken ships.
	 *
	 * @param shot The Shot object representing the player's shot.
	 * @param impact The Impact of the shot (HIT, NONE, SUNKEN).
	 */
	void shotResult(const Shot &shot, Impact impact);

	/*!
	 * @brief Gets a map of shot positions and their impacts on the opponent's grid.
	 *
	 * @return A map containing shot positions and their corresponding impacts.
	 */
	const std::map<GridPosition, Impact>& getShotsAt();

	/*!
	 * @brief Gets a vector of sunken ships on the opponent's grid.
	 *
	 * @return A vector containing information about sunken ships.
	 */
	const std::vector<Ship>& getsunkenShips();

};

#endif /* OPPONENTGRID_H_ */
