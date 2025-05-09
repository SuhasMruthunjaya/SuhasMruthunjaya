/*
 * TicTacScreen.h
 *
 *  Created on: 17 Nov 2023
 *      Author: suhas
 */

#ifndef TICTACSCREEN_H_
#define TICTACSCREEN_H_

#include "TicTacBoard.h"

//< Enum to represent error messages

typedef enum
{
	OUTOFBOUNDS,	//< Error for selecting a position out of bounds
	INVALIDMOVE		//< Error for selecting an invalid position
} ERROR_MSG;

//< Class representing the Tic Tac Toe screen
class TicTacScreen
{
	TicTacBoard *pConsole;//< Pointer to the TicTacBoard object representing the console board

public:

	/*!
	 * Constructor for the TicTacScreen class.
	 * @param pConsole A pointer to the TicTacBoard object representing the console board.
	 */
	TicTacScreen(TicTacBoard *pConsole);

	/*!
	 * Destructor for the TicTacScreen class.
	 */
	virtual ~TicTacScreen();

	/*!
	 * Prints the Tic Tac Toe board on the console.
	 */
	void print();

	/*!
	 * Displays an error message for a wrong move.
	 * @param msg The type of error message (OUTOFBOUNDS or INVALIDMOVE).
	 */
	void Wrong_move_Error_Msg(ERROR_MSG msg);

	/*!
	 * Displays a message indicating PlayerX's turn.
	 */
	void PlayerX_turn_Msg();

	/*!
	 * Displays a message indicating PlayerO's turn.
	 */

	void PlayerO_turn_Msg();

	/*!
	 * Displays a message indicating the winner of the game.
	 * @param player The type of player who won (PlayerX or PlayerO).
	 */
	void winner_msg(PlayerType player);

	/*!
	 * Displays a message indicating a draw in the game.
	 */
	void draw_msg();

	/*!
	 * Asks the user to choose the type of game.
	 * @param userInput Pointer to the variable where the user's choice will be stored.
	 */
	void user_choice(int *UserInput);

};

#endif /* TICTACSCREEN_H_ */
