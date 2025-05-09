/*
 * HumanPlazer.cpp
 *
 *  Created on: 23 Nov 2023
 *      Author: suhas
 */

#include "HumanPlayer.h"

//< Constructor for HumanPlayer class
HumanPlayer::HumanPlayer(PlayerType active_player) :
		Player(active_player)
{

	// Initialize any additional member variables here

}

HumanPlayer::~HumanPlayer()
{
	// TODO Auto-generated destructor stub
}

/*!
 * Sets a stone on the board for the human player at the given row and column.
 * @param board The Tic Tac Toe board.
 * @param userInputRow The row where the user wants to place the stone.
 * @param userInputColumn The column where the user wants to place the stone.
 * @return RC_OK if the stone was successfully placed, RC_ERROR otherwise.
 */
RC_t HumanPlayer::setStone(TicTacBoard *board, int userInputRow,
		int userInputColumn)
{

	//< Get the pointer to the board
	char *pBoard = board->getPBoard();

	//< Get the index of the cell where the user wants to place the stone
	int index = board->getIndex(userInputRow, userInputColumn);

	//< If the cell is not empty, return an error
	if (pBoard[index] != '.')
	{
		return RC_ERROR;
	}
	// Otherwise, place the stone and return success
	else
	{
		pBoard[index] = getSymbol();
		return RC_OK;

	}

}
