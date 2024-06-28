/*
 * Ship.cpp
 *
 *  Created on: 12 Dec 2023
 *      Author: suhas
 */

#include "Ship.h"
#include <iostream>
#include "GridPosition.h"

using namespace std;

/*!
 * @brief Constructor for the Ship class.
 *
 * @param bow The position of the bow of the ship.
 * @param stern The position of the stern of the ship.
 */
Ship::Ship(const GridPosition &bow, const GridPosition &stern) :
		bow(bow), stern(stern)
{

}

Ship::~Ship()
{
	// TODO Auto-generated destructor stub
}

/*!
 * @brief Checks if the ship is valid based on its positions and length.
 *
 * @return True if the ship is valid, false otherwise.
 */

bool Ship::isValid() const
{
	if ((bow.getRow() == stern.getRow() || bow.getColumn() == stern.getColumn())
			&& (2 <= length() && length() <= 5) && bow.isValid()
			&& stern.isValid())
	{
		return true;
	}
	else
		return false;

}

/*!
 * @brief Gets the position of the bow of the ship.
 *
 * @return The position of the bow.
 */

GridPosition Ship::getBow() const
{
	return bow;
}

/*!
 * @brief Gets the position of the stern of the ship.
 *
 * @return The position of the stern.
 */
GridPosition Ship::getStern() const
{
	return stern;
}

/*!
 * @brief Calculates and returns the length of the ship.
 *
 * @return The length of the ship.
 */
int Ship::length() const
{
	int length = 0;
	char bow_row = bow.getRow(), stern_row = stern.getRow();
	int bow_column = bow.getColumn(), stern_column = stern.getColumn();

	if (bow_row != stern_row)
	{
		if (bow_row < stern_row)
		{
			length = stern_row - bow_row + 1;
		}
		else if (bow_row > stern_row)
		{
			length = bow_row - stern_row + 1;
		}

	}
	else if (bow_row == stern_row)
	{
		if (bow_column < stern_column)
		{
			length = stern_column - bow_column + 1;
		}
		else if (bow_column > stern_column)
		{
			length = bow_column - stern_column + 1;
		}
	}

	return length;

}

/*!
 * @brief Gets the set of positions occupied by the ship.
 *
 * @return A set containing positions occupied by the ship.
 */

set<GridPosition> Ship::occupiedArea() const
{

	set<GridPosition> ship_pos;

	char bow_row = bow.getRow(), stern_row = stern.getRow();
	int bow_column = bow.getColumn(), stern_column = stern.getColumn();

	if (bow_row != stern_row)
	{
		if (bow_row < stern_row)
		{
			while (bow_row <= stern_row)
			{
				ship_pos.insert(GridPosition(bow_row, bow_column));
				bow_row++;
			}
		}
		else if (bow_row > stern_row)
		{
			while (bow_row >= stern_row)
			{
				ship_pos.insert(GridPosition(bow_row, bow_column));
				bow_row--;
			}
		}
	}
	else if (bow_row == stern_row)
	{
		if (bow_column < stern_column)
		{
			while (bow_column <= stern_column)
			{
				ship_pos.insert(GridPosition(bow_row, bow_column));
				bow_column++;
			}
		}
		else if (bow_column > stern_column)
		{
			while (bow_column >= stern_column)
			{
				ship_pos.insert(GridPosition(bow_row, bow_column));
				bow_column--;
			}
		}

	}

	return ship_pos;

}

/*!
 * @brief Gets the set of positions blocked by the ship.
 *
 * @return A set containing positions blocked by the ship.
 */

set<GridPosition> Ship::blockedArea() const
{
	set<GridPosition> result;

	set<GridPosition> occupied_pos = occupiedArea();

	for (auto const &element : occupied_pos)
	{
		char row = element.getRow();
		int column = element.getColumn();

		if (GridPosition(row, column + 1).isValid())
			result.insert(GridPosition(row, column + 1));
		if (GridPosition(row, column - 1).isValid())
			result.insert(GridPosition(row, column - 1));
		if (GridPosition(row - 1, column).isValid())
			result.insert(GridPosition(row - 1, column));
		if (GridPosition(row - 1, column - 1).isValid())
			result.insert(GridPosition(row - 1, column - 1));
		if (GridPosition(row - 1, column + 1).isValid())
			result.insert(GridPosition(row - 1, column + 1));
		if (GridPosition(row + 1, column).isValid())
			result.insert(GridPosition(row + 1, column));
		if (GridPosition(row + 1, column - 1).isValid())
			result.insert(GridPosition(row + 1, column - 1));
		if (GridPosition(row + 1, column + 1).isValid())
			result.insert(GridPosition(row + 1, column + 1));

		result.insert(element);

	}

	return result;
}
