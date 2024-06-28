/*
 * OpponentGrid.cpp
 *
 *  Created on: 14 Dec 2023
 *      Author: suhas
 */

#include "OpponentGrid.h"
#include <iostream>
#include <set>

/*!
 * @brief Constructor for the OpponentGrid class.
 *
 * Initializes an OpponentGrid object with the specified number of rows and columns.
 *
 * @param rows The number of rows in the opponent's grid.
 * @param columns The number of columns in the opponent's grid.
 */
OpponentGrid::OpponentGrid(int rows, int columns)
{
	// TODO Auto-generated constructor stub
	this->rows = rows;
	this->columns = columns;

}

/*!
 * @brief Destructor for the OpponentGrid class.
 */
OpponentGrid::~OpponentGrid()
{
	// TODO Auto-generated destructor stub
}

/*!
 * @brief Gets the number of columns in the opponent's grid.
 *
 * @return The number of columns in the opponent's grid.
 */

int OpponentGrid::getColumns() const
{
	return columns;
}

/*!
 * @brief Gets the number of rows in the opponent's grid.
 *
 * @return The number of rows in the opponent's grid.
 */
int OpponentGrid::getRows() const
{
	return rows;
}

/*!
 * @brief Processes the result of a shot fired by the player.
 *
 * Updates the shot information in the opponent's grid, including hits, misses, and sunken ships.
 *
 * @param shot The Shot object representing the player's shot.
 * @param impact The Impact of the shot (HIT, NONE, SUNKEN).
 */
void OpponentGrid::shotResult(const Shot &shot, Impact impact)
{

	if (shot.getTargetPosition().isValid() && impact != SUNKEN)
		shots[shot.getTargetPosition()] = impact;

	else if (shot.getTargetPosition().isValid() && impact == SUNKEN)
	{
		std::set<GridPosition> ship_pos;

		findOpponentShip(shot.getTargetPosition(), ship_pos, 1, 0);
		findOpponentShip(shot.getTargetPosition(), ship_pos, -1, 0);
		findOpponentShip(shot.getTargetPosition(), ship_pos, 0, 1);
		findOpponentShip(shot.getTargetPosition(), ship_pos, 0, -1);

		GridPosition ShipBow = *ship_pos.begin();
		GridPosition ShipStern = *std::prev(ship_pos.end());

		sunkenShips.push_back(Ship(ShipBow, ShipStern));

	}

}

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
void OpponentGrid::findOpponentShip(GridPosition targetPosition,
		std::set<GridPosition> &ship_pos, int horizontalShift,
		int verticalShift)
{
	GridPosition local_gridPos;
	char row = targetPosition.getRow();
	int column = targetPosition.getColumn();

	auto it = shots.find(
			GridPosition(row + verticalShift, column + horizontalShift));
	local_gridPos = GridPosition(row, column);

	while (it != shots.end())
	{
		// std::cout << "Checking: (" << it->first.getRow() << ", " << it->first.getColumn() << "): " << (it->second == HIT ? "HIT" : "NONE") << std::endl;

		local_gridPos = GridPosition( it->first.getRow(),
				(*it).first.getColumn());
		if (it->second == HIT)
		{
			it = shots.find(
					GridPosition((*it).first.getRow() + verticalShift,
							(*it).first.getColumn() + horizontalShift));
		}
		else if (it->second == NONE)
		{
			ship_pos.insert(
					GridPosition((*it).first.getRow() - verticalShift,
							(*it).first.getColumn() - horizontalShift));
			break;
		}
	}
	if (it == shots.end())
	{
		ship_pos.insert(local_gridPos);
	}

}

/*!
 * @brief Gets a map of shot positions and their impacts on the opponent's grid.
 *
 * @return A map containing shot positions and their corresponding impacts.
 */
const std::map<GridPosition, Impact>& OpponentGrid::getShotsAt()
{
	return shots;
}

/*!
 * @brief Gets a vector of sunken ships on the opponent's grid.
 *
 * @return A vector containing information about sunken ships.
 */
const std::vector<Ship>& OpponentGrid::getsunkenShips()
{
	return sunkenShips;
}
