/*
 * GridPosition.cpp
 *
 *  Created on: 11 Dec 2023
 *      Author: suhas
 */

#include "GridPosition.h"
#include <iostream>
#include <sstream>

using namespace std;

/*!
 * @brief Constructor for the GridPosition class.
 *
 * Initializes a GridPosition object with the specified row and column values.
 *
 * @param row The row of the grid position.
 * @param column The column of the grid position.
 */
GridPosition::GridPosition(char row, int column)
{

	this->row = row;
	this->column = column;

}

/*!
 * @brief Constructor for the GridPosition class that takes a string representation.
 *
 * Initializes a GridPosition object based on the string representation of a position, e.g., "A1".
 *
 * @param position The string representation of the grid position.
 */
GridPosition::GridPosition(string position)
{
	this->row = position[0];
	this->column = std::stoi(position.substr(1));

}

/*!
 * @brief Destructor for the GridPosition class.
 */
GridPosition::~GridPosition()
{
	// TODO Auto-generated destructor stub
}

/*!
 * @brief Checks if the grid position is valid.
 *
 * A grid position is considered valid if the row is a character between 'A' and 'Z' (inclusive)
 * and the column is greater than 0.
 *
 * @return True if the grid position is valid, false otherwise.
 */
bool GridPosition::isValid() const
{
	if (('A' <= row && row <= 'Z') && (column > 0))
		return true;
	else
		return false;
}

/*!
 * @brief Gets the row of the grid position.
 *
 * @return The character representing the row of the grid position.
 */
char GridPosition::getRow() const
{
	return row;
}

/*!
 * @brief Gets the column of the grid position.
 *
 * @return The integer representing the column of the grid position.
 */
int GridPosition::getColumn() const
{
	return column;
}

/*!
 * @brief Overloaded equality operator for comparing two grid positions.
 *
 * @param other The GridPosition object to compare with.
 * @return True if the grid positions are equal, false otherwise.
 */
bool GridPosition::operator ==(GridPosition other) const
{
	if ((this->row == other.row) && (this->column == other.column))
		return true;
	else
		return false;

}

/*!
 * @brief Converts the grid position to its string representation.
 *
 * @return The string representation of the grid position (e.g., "A1").
 */
GridPosition::operator std::string()
{
	return this->row + std::to_string(this->column);
}

/*!
 * @brief Overloaded less-than operator for comparing two grid positions.
 * This is also much needed for set and map STL Containers
 *
 * @param other The GridPosition object to compare with.
 * @return True if this grid position is less than the other, false otherwise.
 */
bool GridPosition::operator <(const GridPosition &other) const
{
	if ((this->row < other.row)
			|| ((this->row == other.row) && (this->column < other.column)))
		return true;
	else
		return false;

}
