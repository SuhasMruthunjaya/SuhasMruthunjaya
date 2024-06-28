/*
 * GridPosition.h
 *
 *  Created on: 11 Dec 2023
 *      Author: suhas
 */

#ifndef GRIDPOSITION_H_
#define GRIDPOSITION_H_

#include <string>

/*!
 * @brief Represents a position on the game grid, identified by a row and column.
 *
 * The GridPosition class provides methods to create, manipulate, and validate positions on the game grid.
 */
class GridPosition
{

private:
	char row;		//!< The row of the grid position.
	int column;		//!< The column of the grid position
public:

	/*!
	 * @brief Constructor for the GridPosition class.
	 *
	 * Initializes a GridPosition object with the specified row and column values.
	 *
	 * @param row The row of the grid position.
	 * @param column The column of the grid position.
	 */
	GridPosition(char row = '\0', int column = 1);

	/*!
	 * @brief Destructor for the GridPosition class.
	 */
	virtual ~GridPosition();

	/*!
	 * @brief Constructor for the GridPosition class that takes a string representation.
	 *
	 * Initializes a GridPosition object based on the string representation of a position, e.g., "A1".
	 *
	 * @param position The string representation of the grid position.
	 */
	GridPosition(std::string position);

	/*!
	 * @brief Checks if the grid position is valid.
	 *
	 * A grid position is considered valid if the row is a character between 'A' and 'Z' (inclusive)
	 * and the column is greater than 0.
	 *
	 * @return True if the grid position is valid, false otherwise.
	 */

	bool isValid() const;

	/*!
	 * @brief Gets the row of the grid position.
	 *
	 * @return The character representing the row of the grid position.
	 */
	char getRow() const;

	/*!
	 * @brief Gets the column of the grid position.
	 *
	 * @return The integer representing the column of the grid position.
	 */
	int getColumn() const;

	/*!
	 * @brief Converts the grid position to its string representation.
	 *
	 * @return The string representation of the grid position (e.g., "A1").
	 */
	operator std::string();

	/*!
	 * @brief Overloaded equality operator for comparing two grid positions.
	 *
	 * @param other The GridPosition object to compare with.
	 * @return True if the grid positions are equal, false otherwise.
	 */

	bool operator==(GridPosition other) const;

	/*!
	 * @brief Overloaded less-than operator for comparing two grid positions.
	 * This is also much needed for set and map STL Containers
	 *
	 * @param other The GridPosition object to compare with.
	 * @return True if this grid position is less than the other, false otherwise.
	 */
	bool operator<(const GridPosition &other) const;

};

#endif /* GRIDPOSITION_H_ */
