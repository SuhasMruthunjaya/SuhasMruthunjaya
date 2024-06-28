/*
 * Board.cpp
 *
 *  Created on: 14 Dec 2023
 *      Author: suhas
 */

#include "Board.h"

/*!
 * @brief Constructor for the Board class.
 *
 * Initializes the Board with the specified number of rows and columns for the OwnGrid and OpponentGrid.
 *
 * @param rows The number of rows for both grids.
 * @param columns The number of columns for both grids.
 */
Board::Board(int rows, int columns) :
		ownGrid(rows, columns), opponentGrid(rows, columns)
{
	// TODO Auto-generated constructor stub
}

Board::~Board()
{
	// TODO Auto-generated destructor stub
}

/*!
 * @brief Gets a reference to the player's own grid.
 * @return Reference to the OwnGrid.
 */
OwnGrid& Board::getOwnGrid()
{
	return ownGrid;
}

/*!
 * @brief Gets a reference to the opponent's grid.
 * @return Reference to the OpponentGrid.
 */
OpponentGrid& Board::getOpponentGrid()
{
	return opponentGrid;
}

/*!
 * @brief Gets the number of rows in the OwnGrid.
 * @return The number of rows.
 */
int Board::getRows()
{
	return this->ownGrid.getRows();
}

/*!
 * @brief Gets the number of columns in the OwnGrid.
 * @return The number of columns.
 */
int Board::getColumns()
{
	return this->ownGrid.getColumns();
}
