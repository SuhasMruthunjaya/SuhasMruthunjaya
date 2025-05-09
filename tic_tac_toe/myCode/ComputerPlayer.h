/*
 * ComputerPlayer.h
 *
 *  Created on: 26 Nov 2023
 *      Author: suhas
 */

#ifndef COMPUTERPLAYER_H_
#define COMPUTERPLAYER_H_

#include "TicTacBoard.h"
#include "Player.h"

//< Definition of the ComputerPlayer class, which is a derived class of the Player class.
class ComputerPlayer: public Player
{
public:
	/*! Constructor for the ComputerPlayer class.
	 * @param: active_player - the type of player (X or O)
	 */
	ComputerPlayer(PlayerType active_player);

	//< Destructor for the ComputerPlayer class.
	virtual ~ComputerPlayer();

	/*Method to set a stone on the TicTacBoard for the computer player.
	 * @param: board - pointer to the TicTacBoard, userInputRow - row provided by the user (default is 0),
	 *             userInputColumn - column provided by the user (default is 0).
	 * @return: Result code indicating success or failure of setting the stone.
	 *
	 */
	RC_t setStone(TicTacBoard *board, int userInputRow = 0,
			int userInputColumn = 0);

};

#endif /* COMPUTERPLAYER_H_ */
