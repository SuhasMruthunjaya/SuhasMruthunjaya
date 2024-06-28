/*
 * OwnGrid.cpp
 *
 *  Created on: 14 Dec 2023
 *      Author: suhas
 */

#include "OwnGrid.h"
#include "iostream"

#include <set>
#include <algorithm>

/*!
 * @brief Constructor for the OwnGrid class.
 *
 * Initializes an OwnGrid object with the specified number of rows and columns.
 *
 * @param rows The number of rows in the player's own grid.
 * @param columns The number of columns in the player's own grid.
 */
OwnGrid::OwnGrid(int rows, int columns)
{
	// TODO Auto-generated constructor stub
	this->rows = rows;
	this->columns = columns;

	shipDataInit();

}

/*!
 * @brief Destructor for the OwnGrid class.
 */
OwnGrid::~OwnGrid()
{
	// TODO Auto-generated destructor stub
}

/*!
 * @brief Gets the number of columns in the player's own grid.
 *
 * @return The number of columns in the player's own grid.
 */
int OwnGrid::getColumns() const
{
	return columns;
}

/*!
 * @brief Gets the number of rows in the player's own grid.
 *
 * @return The number of rows in the player's own grid.
 */

int OwnGrid::getRows() const
{
	return rows;
}

/*!
 * @brief Places a ship on the player's own grid.
 *
 * Checks for validity, availability, and intersections with existing ships before placement.
 *
 * @param ship The Ship object representing the ship to be placed.
 * @return True if the ship is successfully placed, false otherwise.
 */
bool OwnGrid::placeShip(const Ship &ship)
{

	bool result = false;

	if (ship.isValid() && posIsValid(ship))
	{
		std::set<GridPosition> intersectionSet;

		for (auto &element : ownShips)
		{

			std::set<GridPosition> occupied_area = ship.occupiedArea();
			std::set<GridPosition> blocked_area = element.blockedArea();

			std::set_intersection(occupied_area.begin(), occupied_area.end(),
					blocked_area.begin(), blocked_area.end(),
					std::inserter(intersectionSet, intersectionSet.begin()));

		}

		if (intersectionSet.empty() && isShipAvailable(ship))
		{
			ownShips.push_back(ship);
			result = true;
		}
		else
		{
			std::cout << " The ship of length " << ship.length()
					<< " is not available or it is touching"
							" another ship" << std::endl;
			result = false;
		}
	}
	else
	{
		std::cout << " The ship is not valid " << std::endl;
		result = false;
	}

	return result;
}

/*!
 * @brief Checks if a ship placement is valid within the boundaries of the own grid.
 *
 * @param ship The Ship object representing the ship to be placed.
 * @return True if the ship placement is valid, false otherwise.
 */
bool OwnGrid::posIsValid(const Ship &ship) const
{
	if (ship.getBow().getRow() - 64 <= rows
			&& ship.getBow().getColumn() <= columns
			&& ship.getStern().getRow() - 64 <= rows
			&& ship.getStern().getColumn() <= columns)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*!
 * @brief Checks if a ship of a specific length is still available to be placed.
 *
 * @param ship The Ship object representing the ship to be placed.
 * @return True if the ship is available, false otherwise.
 */
bool OwnGrid::isShipAvailable(const Ship &ship)
{

	if (shipData[ship.length()] > 0)
	{
		shipData[ship.length()]--;
		return true;

	}
	else
		return false;

}

/*!
 * @brief Initializes the shipData map with the count of available ships of each length.
 */
void OwnGrid::shipDataInit()
{
	shipData[5] = 1;
	shipData[4] = 2;
	shipData[3] = 3;
	shipData[2] = 4;
}

/*!
 * @brief Checks if a shot results in the final hit on a ship, indicating that it is sunk.
 *
 * @param ship The Ship object representing the ship being targeted.
 * @return True if the final hit, false otherwise.
 */

bool OwnGrid::IsFinalHit(Ship const &ship)
{
	std::set<GridPosition> occupied_area = ship.occupiedArea();
	std::set<GridPosition> intersectionSet;

	std::set_intersection(occupied_area.begin(), occupied_area.end(),
			shotAt.begin(), shotAt.end(),
			std::inserter(intersectionSet, intersectionSet.begin()));

	if ((int) intersectionSet.size() == ship.length() - 1)
	{
		return true;
	}

	return false;
}

/*!
 * @brief Gets a set of positions that have been shot at by the opponent.
 *
 * @return A set containing positions that have been shot at.
 */

const std::set<GridPosition> OwnGrid::getShotAt()
{
	return shotAt;
}

/*!
 * @brief Gets a vector of ships placed on the player's own grid.
 *
 * @return A vector containing information about player's own ships.
 */

const std::vector<Ship> OwnGrid::getShip() const
{
	return ownShips;
}

/*!
 * @brief Processes the result of a shot received from the opponent.
 *
 * Updates shot information, checks for sunk ships, and returns the impact of the shot.
 *
 * @param shot The Shot object representing the shot received from the opponent.
 * @return The Impact of the shot (HIT, NONE, SUNKEN).
 */
Impact OwnGrid::takeBlow(const Shot &shot)
{
	GridPosition shot_gridpos = shot.getTargetPosition();

	for (auto const &ship : ownShips)
	{
		for (auto const &element : ship.occupiedArea())
		{
			if (shot_gridpos == element)
			{
				if (IsFinalHit(ship))
				{
					shotAt.insert(shot_gridpos);
					return SUNKEN;
				}
				else
				{
					shotAt.insert(shot_gridpos);
					return HIT;
				}
			}
		}
	}
	shotAt.insert(shot_gridpos);
	return NONE;
}

/*!
 * @brief Checks if all ships on the player's own grid are sunk.
 *
 * @return True if all ships are sunk, false otherwise.
 */
bool OwnGrid::isShipsSunk()
{

	std::set<GridPosition> allShipsOccupiedArea;
	std::set<GridPosition> intersectionSet;

	for (auto const &ship : ownShips)
	{
		for (auto const &position : ship.occupiedArea())
		{
			allShipsOccupiedArea.insert(position);
		}
	}

	std::set_intersection(allShipsOccupiedArea.begin(),
			allShipsOccupiedArea.end(), shotAt.begin(), shotAt.end(),
			std::inserter(intersectionSet, intersectionSet.begin()));

	if (intersectionSet.size() == 30)
	{
		return true;
	}
	else
		return false;

}
