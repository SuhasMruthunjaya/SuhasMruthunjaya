/*
 * ConsoleView.h
 *
 *  Created on: 14 Dec 2023
 *      Author: suhas
 */

#ifndef MYCODE_CONSOLEVIEW_H_
#define MYCODE_CONSOLEVIEW_H_

#include "Board.h"

/*!
 * @brief Represents a console view for displaying the game board in a console.
 *
 * The ConsoleView class provides methods for printing the player's own grid and the opponent's grid
 * with appropriate symbols to represent ships, shots, and sunken ships.
 */
class ConsoleView
{
private:
	Board *board;	 //!< Pointer to the game board.

	/*!
	 * @brief Determines the symbol to be displayed on the player's own grid.
	 *
	 * This function is responsible for deciding the symbol to be displayed on the player's own grid
	 * based on whether the space contains a ship, has been shot at, or is part of a sunken ship.
	 *
	 * @param row The row of the grid.
	 * @param column The column of the grid.
	 * @return The character symbol for the specified grid position.
	 */
	char funcOwnBoard(int row, int column);

	/*!
	 * @brief Determines the symbol to be displayed on the opponent's grid.
	 *
	 * This function is responsible for deciding the symbol to be displayed on the opponent's grid
	 * based on whether the space has been shot at, hit, or is part of a sunken ship.
	 *
	 * @param row The row of the grid.
	 * @param column The column of the grid.
	 * @return The character symbol for the specified grid position on the opponent's grid.
	 */

	char funcOpponentBoard(int row, int column);

	/*!
	 * @brief Checks if the specified grid position contains a ship on the player's own grid.
	 *
	 * @param row The row of the grid.
	 * @param column The column of the grid.
	 * @return True if the grid position contains a ship, false otherwise.
	 */
	bool isShipSpace(int row, int column);

public:

	/*!
	 * @brief Constructor for the ConsoleView class.
	 *
	 * Initializes the ConsoleView with a pointer to the game board.
	 *
	 * @param board Pointer to the game board.
	 */
	ConsoleView(Board *board);

	/*!
	 * @brief Prints the player's own grid and the opponent's grid in the console.
	 */
	void print();
};

#endif /* MYCODE_CONSOLEVIEW_H_ */
