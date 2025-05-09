/*
 * TicTacBoard.h
 *
 *  Created on: 25 Nov 2023
 *      Author: suhas
 */

#ifndef TICTACBOARD_H_
#define TICTACBOARD_H_

#include "Board.h"
#include "global.h"
#include "Player.h"

//< Structure representing a move on the TicTacToe board
struct Move
{
	int row, col;
};

//< TicTacBoard class inherits the Board class and uses its member functions
class TicTacBoard: public Board
{
public:

	/*!
	 * Constructor for the TicTacBoard class.
	 * @param row Number of rows in the Tic Tac Toe board.
	 * @param column Number of columns in the Tic Tac Toe board.
	 */

	TicTacBoard(int row = 0, int column = 0);

	/*!
	 * Destructor for the TicTacBoard class.
	 */
	virtual ~TicTacBoard();

// HumanPlayer used Functions

	/*!
	 * Checks the Tic Tac Toe board for a win in a specific direction.
	 * @param direction The direction to check for a win (1 for rows, row for columns, row+1 for left diagonal, row-1 for right diagonal).
	 * @param player Array containing two Player objects representing the players.
	 * @return The player type (PlayerX or PlayerO) who has won in the specified direction, or NO_Player if no winner.
	 */
	PlayerType checkBoard(int direction, Player *player[2]);

	/*!
	 * Checks if the Tic Tac Toe board is full.
	 * @return True if the board is full, false otherwise.
	 */

	bool checkFullBoard();

// ComputerPlayer used Functions

	/*!
	 * Checks if there are any moves left on the Tic Tac Toe board.
	 * @return True if there are moves left, false otherwise.
	 */
	bool isMovesLeft();

	/*!
	 * Evaluates the current state of the Tic Tac Toe board for a player.
	 * @param player The Player object for whom the board is evaluated.
	 * @return The evaluation score for the player's position on the board.
	 */
	int evaluate(Player *player);

	/*!
	 * Finds the best move for the computer player using the minimax algorithm.
	 * @param player The computer player for whom the best move is determined.
	 * @param BestMove_Row Pointer to the variable storing the row of the best move.
	 * @param BestMove_Column Pointer to the variable storing the column of the best move.
	 */
	void findBestMove(Player *player, int *BestMove_Row, int *BestMove_Column);

	/*!
	 * The minimax algorithm to determine the best move for the computer player.
	 * @param player The computer player for whom the best move is determined.
	 * @param depth The current depth in the minimax tree.
	 * @param isMax Indicates whether the current player is maximizing or minimizing.
	 * @return The best score for the current player's move.
	 */
	int minimax(Player *player, int depth, bool isMax);

	/*!
	 * Checks rows or columns for a specific player and returns a score.
	 * @param direction The direction to check for a score (1 for rows, row for columns).
	 * @param player The Player object for whom the score is calculated.
	 * @return The score for the player in the specified direction.
	 */
	int checkRowsColumns(int direction, Player *player);

};

#endif /* TICTACBOARD_H_ */
