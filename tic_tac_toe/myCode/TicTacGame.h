/*
 * TicTacGame.h
 *
 *  Created on: 18 Nov 2023
 *      Author: suhas
 */

#ifndef TICTACGAME_H_
#define TICTACGAME_H_

#include "Board.h"
#include "Player.h"
#include "global.h"
#include "TicTacScreen.h"
#include "TicTacBoard.h"

#define tic_tac_row 3
#define tic_tac_column 3
#define num_of_players 2

//< Class representing the Tic Tac Toe game
class TicTacGame
{
private:
	TicTacBoard board;
	Player *player[2];
	TicTacScreen screen;

private:


	/*!
	 * Checks if there is a winner in the Tic Tac Toe game.
	 * @return RC_CONDITIONSATISFIED if there is a winner, RC_OK otherwise.
	 */
	RC_t checkWin();

	/*!
	 * Getter function to retrieve a player based on the player index.
	 * @param playerIndex The index of the player in the array.
	 * @return A pointer to the Player object if the index is valid, nullptr otherwise.
	 */
	Player* getPlayer(int playerIndex) const;

	/*!
	 * Handles player inputs for setting stones on the Tic Tac Toe board.
	 * @param player The type of player for whom input is taken (PlayerX or PlayerO).
	 * @param InputRow Reference to the variable storing the row input.
	 * @param InputColumn Reference to the variable storing the column input.
	 * @return RC_OK if the input is valid, RC_ERROR otherwise.
	 */
	RC_t playerInputs(PlayerType player, int &InputRow, int &InputColumn);
public:
	/*!
	 * Constructor for the TicTacGame class.
	 * @param player An array of pointers to Player objects representing the players (default = nullptr).
	 */
	TicTacGame(Player *player[2] = nullptr);

	/*!
	 * Destructor for the TicTacGame class.
	 */
	virtual ~TicTacGame();
	/*!
	 * Runs the Tic Tac Toe game.
	 */
	void run();

};

#endif /* TICTACGAME_H_ */
