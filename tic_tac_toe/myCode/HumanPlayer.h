/*
 * HumanPlazer.h
 *
 *  Created on: 23 Nov 2023
 *      Author: suhas
 */

#ifndef HUMANPLAYER_H_
#define HUMANPLAYER_H_

#include "TicTacBoard.h"
#include "Player.h"

/*!
 * HumanPlayer class represents a human player in a Tic Tac Toe game.
 */
class HumanPlayer: public Player
{
public:
	HumanPlayer(PlayerType active_player);
	virtual ~HumanPlayer();

	/*!
	 * Sets a stone on the board for the human player at the given row and column.
	 * @param board The Tic Tac Toe board.
	 * @param userInputRow The row where the user wants to place the stone.
	 * @param userInputColumn The column where the user wants to place the stone.
	 * @return RC_OK if the stone was successfully placed, RC_ERROR otherwise.
	 */

	RC_t setStone(TicTacBoard *board, int userInputRow = 0,
			int userInputColumn = 0);

};

#endif /* HUMANPLAYER_H_ */
