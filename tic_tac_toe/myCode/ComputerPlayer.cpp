/*
 * ComputerPlayer.cpp
 *
 *  Created on: 26 Nov 2023
 *      Author: suhas
 */

#include "ComputerPlayer.h"

/*! Constructor for the ComputerPlayer class.
 * @param: active_player - the type of player (X or O)
 */
ComputerPlayer::ComputerPlayer(PlayerType active_player) :
		Player(active_player)
{
	// TODO Auto-generated constructor stub

}

//< Destructor for the ComputerPlayer class.
ComputerPlayer::~ComputerPlayer()
{
	// TODO Auto-generated destructor stub
}

/*Method to set a stone on the TicTacBoard for the computer player.
 * @param: board - pointer to the TicTacBoard, userInputRow - row provided by the user (default is 0),
 *             userInputColumn - column provided by the user (default is 0).
 * @return: Result code indicating success or failure of setting the stone.
 *
 */
RC_t ComputerPlayer::setStone(TicTacBoard *board, int userInputRow,
		int userInputColumn)
{

	int bestMove_Row = 0, bestMove_column = 0;

	board->findBestMove(this, &bestMove_Row, &bestMove_column);

	printf("The Optimal Move is :\n");
	printf("ROW: %d COL: %d\n\n", bestMove_Row, bestMove_column);

	char *pBoard = board->getPBoard();

	int index = board->getIndex(bestMove_Row, bestMove_column);

	if (pBoard[index] != '.')
	{
		return RC_ERROR;
	}
	else
	{
		pBoard[index] = getSymbol();
		return RC_OK;

	}
}

