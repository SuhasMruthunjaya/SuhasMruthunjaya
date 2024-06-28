/*
 * ConsoleView.cpp
 *
 *  Created on: 14 Dec 2023
 *      Author: suhas
 */

#include "ConsoleView.h"
#include <iostream>
#include <vector>

using namespace std;

/*!
 * @brief Constructor for the ConsoleView class.
 *
 * Initializes the ConsoleView with a pointer to the game board.
 *
 * @param board Pointer to the game board.
 */
ConsoleView::ConsoleView(Board *board)
{
	this->board = board;
}

/*!
 * @brief Prints the player's own grid and the opponent's grid in the console.
 */
void ConsoleView::print()
{
	int row = board->getRows();
	int column = board->getColumns();

	cout << "          1           1" << endl;
	cout << " 1234567890  1234567890" << endl;

	for (int i = 1; i < row + 1; i++)
	{
		cout << char(i + 64);
		for (int j = 1; j < column + 1; j++)
		{
			cout << funcOwnBoard(i, j);

		}

		cout << " ";
		cout << char(i + 64);
		for (int j = 1; j < column + 1; j++)
		{
			cout << funcOpponentBoard(i, j);

		}

		cout << endl;

	}
}

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

char ConsoleView::funcOwnBoard(int row, int column)
{
	char position = '~';
	if (isShipSpace(row, column))
	{
		position = '#';
	}

	set<GridPosition> shot_pos = board->getOwnGrid().getShotAt();

	for (auto const &pos : shot_pos)
	{
		if (GridPosition(char(row + 64), column) == pos)
		{
			if (isShipSpace(row, column))
				position = '0';
			else
				position = '^';
		}
	}

	return position;
}

/*!
 * @brief Checks if the specified grid position contains a ship on the player's own grid.
 *
 * @param row The row of the grid.
 * @param column The column of the grid.
 * @return True if the grid position contains a ship, false otherwise.
 */
bool ConsoleView::isShipSpace(int row, int column)
{
	vector<Ship> ownGridShips = board->getOwnGrid().getShip();

	for (auto const &ship : ownGridShips)
	{
		for (auto const &element : ship.occupiedArea())
		{
			if (GridPosition(char(row + 64), column).isValid())
			{
				if (GridPosition(char(row + 64), column) == element)
				{
					return true;
				}
			}
		}
	}

	return false;
}

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
char ConsoleView::funcOpponentBoard(int row, int column)
{
	char position = '~';

	std::map<GridPosition, Impact> shots =
			board->getOpponentGrid().getShotsAt();

	for (auto const &shot : shots)
	{
		if (GridPosition(char(row + 64), column) == shot.first)
		{
			if (shot.second == HIT)
			{
				position = '0';
			}
			else if (shot.second == NONE)
			{
				position = '^';
			}
		}
	}

	std::vector<Ship> sunkenShips = board->getOpponentGrid().getsunkenShips();

	for (auto const &ship : sunkenShips)
	{
		for (auto const &element : ship.occupiedArea())
		{
			if (GridPosition(char(row + 64), column) == element)
			{
				position = '#';
			}
		}
	}

	return position;

}
