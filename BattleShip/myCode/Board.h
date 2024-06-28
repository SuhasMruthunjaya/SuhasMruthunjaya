/*
 * Board.h
 *
 *  Created on: 14 Dec 2023
 *      Author: suhas
 */

#ifndef MYCODE_BOARD_H_
#define MYCODE_BOARD_H_

#include "OwnGrid.h"
#include "OpponentGrid.h"

/*!
 * @brief Represents a game board consisting of an OwnGrid and an OpponentGrid.
 *
 * The Board class serves as the container for both the player's own grid and the opponent's grid in a game.
 * It provides access to grid-related functionalities and dimensions.
 *
 * @note The board is initialized with specified rows and columns for the OwnGrid and OpponentGrid.
 */

class Board
{
private:
	OwnGrid ownGrid;			//!< The player's own grid.
	OpponentGrid opponentGrid;	//!< The opponent's grid.

public:

	/*!
	 * @brief Constructor for the Board class.
	 *
	 * Initializes the Board with the specified number of rows and columns for the OwnGrid and OpponentGrid.
	 *
	 * @param rows The number of rows for both grids.
	 * @param columns The number of columns for both grids.
	 */
	Board(int rows = 0, int columns = 0);

	/*!
	 * @brief Destructor for the Board class.
	 */
	virtual ~Board();

	/*!
	 * @brief Gets a reference to the player's own grid.
	 * @return Reference to the OwnGrid.
	 */
	OwnGrid& getOwnGrid();

	/*!
	 * @brief Gets a reference to the opponent's grid.
	 * @return Reference to the OpponentGrid.
	 */
	OpponentGrid& getOpponentGrid();

	/*!
	 * @brief Gets the number of rows in the OwnGrid.
	 * @return The number of rows.
	 */
	int getRows();

	/*!
	 * @brief Gets the number of columns in the OwnGrid.
	 * @return The number of columns.
	 */
	int getColumns();
};

#endif /* MYCODE_BOARD_H_ */
