/*
 * Player.h
 *
 *  Created on: 18 Nov 2023
 *      Author: suhas
 */

#ifndef PLAYER_H_
#define PLAYER_H_

#include "global.h"

//< Forward declaration of TicTacBoard class to avoid circular dependency
class TicTacBoard;

//< Enumeration representing different types of players
typedef enum
{
	NO_Player,			// No specific player type
	PlayerX,			// No specific player type
	PlayerO,			// Player with symbol 'O'
	COMPUTER_PLAYER,	// Computer player
	HUMAN_PLAYER		// Human player

} PlayerType;

//< Player class representing a player in the Tic Tac Toe game
class Player
{
private:
	char symbol;
	PlayerType active_player;
	PlayerType opponent_player;

public:

	/*!
	 * Constructor for the Player class.
	 * @param active_player The type of the active player (PlayerX or PlayerO).
	 */
	Player(PlayerType active_player);

	/*!
	 * Destructor for the Player class.
	 */
	virtual ~Player();

	/*!
	 * Pure virtual function to set a stone on the Tic Tac Toe board.
	 * Derived classes must implement this function.
	 * @param board The Tic Tac Toe board on which the stone is placed.
	 * @param userInputRow The row where the user wants to place the stone (default = 0).
	 * @param userInputColumn The column where the user wants to place the stone (default = 0).
	 * @return RC_OK if the stone was successfully placed, RC_ERROR otherwise.
	 */
	virtual RC_t setStone(TicTacBoard *board, int userInputRow = 0,
			int userInputColumn = 0) = 0;

	/*!
	 * Getter function to retrieve the symbol of the player.
	 * @return The symbol of the player ('X' or 'O').
	 */
	char getSymbol() const;

	/*!
	 * Getter function to retrieve the type of the active player.
	 * @return The type of the active player (PlayerX or PlayerO).
	 */
	PlayerType getActivePlayer() const;

};

#endif /* PLAYER_H_ */
