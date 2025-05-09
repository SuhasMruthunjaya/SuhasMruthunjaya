/*
 * TicTacBoard.cpp
 *
 *  Created on: 25 Nov 2023
 *      Author: suhas
 */

#include "TicTacBoard.h"
#include <iostream>
#include <algorithm>

#include <iostream>

/*!
 * Constructor for the TicTacBoard class.
 * @param row Number of rows in the Tic Tac Toe board.
 * @param column Number of columns in the Tic Tac Toe board.
 */
TicTacBoard::TicTacBoard(int row, int column) :
		Board(row, column)
{
	// TODO Auto-generated constructor stub

#ifdef Testing
	std::cout << "Inside board constructor" << this << std::endl;
	std::cout << "Inside board constructor, Address of the char Array" << &this->pBoard << std::endl;
#endif

}

/*!
 * Destructor for the TicTacBoard class.
 */
TicTacBoard::~TicTacBoard()
{
	// TODO Auto-generated destructor stub
}

/*!
 * Checks the Tic Tac Toe board for a win in a specific direction.
 * @param direction The direction to check for a win (1 for rows, row for columns, row+1 for left diagonal, row-1 for right diagonal).
 * @param player Array containing two Player objects representing the players.
 * @return The player type (PlayerX or PlayerO) who has won in the specified direction, or NO_Player if no winner.
 */
PlayerType TicTacBoard::checkBoard(int direction, Player *player[2])
{

	char *pBoard = getPBoard();
	int row = getRow();
	int column = getColumn();

#ifdef Testing
	for(int i = 0; i < row ; i++)
			{
				for (int j = 0; j< column; j++)
				{
					int index = getIndex(i, j);
					std::cout << Board[index] << "\t";
				}
				std::cout << std::endl;
			}


	std::cout << "Inside checkBoard function" << this << std::endl;
	std::cout << "Address of the char array" << &this->pBoard << std::endl;
	std::cout << "Adress using getBoard func" << &Board << std::endl;

#endif

	int player0_count = 0, player1_count = 0;
	int index = 0;

	if ((direction == 1) || (direction == row))
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{

				if (direction == 1)
					index = getIndex(i, j);
				else if (direction == row)
					index = getIndex(j, i);

				if (pBoard[index] == player[0]->getSymbol())
				{
					player0_count++;
				}
				else if (pBoard[index] == player[1]->getSymbol())
				{
					player1_count++;
				}
			}

			if (player0_count == row)
			{
				return PlayerX;
			}
			else if (player1_count == row)
			{
				return PlayerO;
			}

			player0_count = 0;
			player1_count = 0;
		}

	}

	else if ((direction == row + 1) || (direction == row - 1))
	{
		for (int i = 0; i < row; i++)
		{
			if ((direction == row + 1))
				index = getIndex(i, i);
			else if (direction == row - 1)
				index = getIndex(i, row - 1 - i);

			if (pBoard[index] == player[0]->getSymbol())
			{
				player0_count++;
			}
			else if (pBoard[index] == player[1]->getSymbol())
			{
				player1_count++;
			}
		}

		if (player0_count == row)
		{
			return PlayerX;

		}
		else if (player1_count == row)
		{
			return PlayerO;

		}

		player0_count = 0;
		player1_count = 0;
	}

	return NO_Player;
}

/*!
 * Checks if the Tic Tac Toe board is full.
 * @return True if the board is full, false otherwise.
 */

bool TicTacBoard::checkFullBoard()
{
	bool result = false;
	int row = getRow();
	int column = getColumn();
	char *pBoard = getPBoard();

	for (int i = 0; i < row * column; i++)
	{

		if (pBoard[i] == '.')
		{
			result = false;
			break;

		}
		else
		{
			result = true;
		}
	}

	return result;

}

/*!
 * Checks if there are any moves left on the Tic Tac Toe board.
 * @return True if there are moves left, false otherwise.
 */
bool TicTacBoard::isMovesLeft()
{
	int row = getRow();
	int column = getColumn();
	char *pBoard = getPBoard();

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			int index = getIndex(i, j);
			if (pBoard[index] == '.')
				return true;
		}
	}
	return false;
}

/*!
 * Checks rows or columns for a specific player and returns a score.
 * @param direction The direction to check for a score (1 for rows, row for columns).
 * @param player The Player object for whom the score is calculated.
 * @return The score for the player in the specified direction.
 */

int TicTacBoard::checkRowsColumns(int direction, Player *player)
{
	int row = getRow();
	int column = getColumn();
	char *pBoard = getPBoard();
	int index = 0;

	char active_player, oponent_player;
	int active_player_count, oponent_player_count;

	if (player->getActivePlayer() == PlayerX)
	{
		active_player = 'X';
		oponent_player = 'O';
	}
	else if (player->getActivePlayer() == PlayerO)
	{
		active_player = 'O';
		oponent_player = 'X';
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{

			if (direction == 1)
				index = getIndex(i, j);
			else if (direction == row)
				index = getIndex(j, i);
			if ((direction == row + 1))
				index = getIndex(i, i);
			else if (direction == row - 1)
				index = getIndex(i, row - 1 - i);

			if (pBoard[index] == active_player)
			{
				active_player_count++;
			}
			else if (pBoard[index] == oponent_player)
			{
				oponent_player_count++;
			}
		}

		if (active_player_count == row)
		{
			return +10;
		}
		else if (oponent_player_count == row)
		{
			return -10;
		}

		active_player_count = 0;
		oponent_player_count = 0;
	}
	return 0;

}
/*!
 * Evaluates the current state of the Tic Tac Toe board for a player.
 * @param player The Player object for whom the board is evaluated.
 * @return The evaluation score for the player's position on the board.
 */
int TicTacBoard::evaluate(Player *player)
{
//	int row = getRow();
	char *pBoard = getPBoard();

	char active_player, oponent_player;

	if (player->getActivePlayer() == PlayerX)
	{
		active_player = 'X';
		oponent_player = 'O';
	}
	else if (player->getActivePlayer() == PlayerO)
	{
		active_player = 'O';
		oponent_player = 'X';
	}

//======================= my code ==============================
//	int score = 0;
//
//	score = checkRowsColumns(1,player);
//	if(score == 10)
//	{
//		//std::cout << "RowScore" << score << std::endl;
//		return 10;
//	}
//	else if(score == -10)
//		return -10;
//
//	score = checkRowsColumns(row, player);
//	if(score == 10)
//	{
//		//std::cout << "ColumnScore" << score << std::endl;
//		return 10;
//	}
//	else if(score == -10)
//		return -10;
//
//	score = checkRowsColumns(row+1, player);
//	if(score == 10)
//	{
//		//std::cout << "leftBack Score" << score << std::endl;
//		return 10;
//	}
//	else if(score == -10)
//		return -10;
//
//	score = checkRowsColumns(row-1, player);
//	if(score == 10)
//	{
//		//std::cout << "RightBack Score" << score << std::endl;
//		return 10;
//	}
//	else if(score == -10)
//		return -10;
//===========================================================================

// Checking for Rows for X or O victory.
	for (int r = 0; r < 3; r++)
	{
		int index = r * 3; // Convert 2D array indices to 1D array index

		if (pBoard[index] == pBoard[index + 1]
				&& pBoard[index + 1] == pBoard[index + 2])
		{
			if (pBoard[index] == active_player)
				return +10;
			else if (pBoard[index] == oponent_player)
				return -10;
		}
	}

	//		 Checking for Columns for X or O victory.
	for (int col = 0; col < 3; col++)
	{
		int index = col; // Convert 2D array indices to 1D array index

		if (pBoard[index] == pBoard[index + 3]
				&& pBoard[index + 3] == pBoard[index + 6])
		{
			if (pBoard[index] == active_player)
				return +10;
			else if (pBoard[index] == oponent_player)
				return -10;
		}
	}

	// Checking for the left diagonal (top-left to bottom-right)
	int leftDiagonalIndex = 0;
	if (pBoard[leftDiagonalIndex] == pBoard[leftDiagonalIndex + 4]
			&& pBoard[leftDiagonalIndex + 4] == pBoard[leftDiagonalIndex + 8])
	{
		if (pBoard[leftDiagonalIndex] == active_player)
			return +10;
		else if (pBoard[leftDiagonalIndex] == oponent_player)
			return -10;
	}

	// Checking for the right diagonal (top-right to bottom-left)
	int rightDiagonalIndex = 2;
	if (pBoard[rightDiagonalIndex] == pBoard[rightDiagonalIndex + 2]
			&& pBoard[rightDiagonalIndex + 2] == pBoard[rightDiagonalIndex + 4])
	{
		if (pBoard[rightDiagonalIndex] == active_player)
			return +10;
		else if (pBoard[rightDiagonalIndex] == oponent_player)
			return -10;
	}

	return 0;
}

/*!
 * Finds the best move for the computer player using the minimax algorithm.
 * @param player The computer player for whom the best move is determined.
 * @param BestMove_Row Pointer to the variable storing the row of the best move.
 * @param BestMove_Column Pointer to the variable storing the column of the best move.
 */
void TicTacBoard::findBestMove(Player *player, int *BestMove_Row,
		int *BestMove_Column)
{
	int row = getRow();
	int column = getColumn();
	char *pBoard = getPBoard();

	int bestVal = -1000;
	Move bestMove;
	bestMove.row = -1;
	bestMove.col = -1;

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			int index = getIndex(i, j);
			// Check if cell is empty
			if (pBoard[index] == '.')
			{
				// Make the move
				pBoard[index] = player->getSymbol();

				// compute evaluation function for this
				// move.
				int moveVal = minimax(player, 0, false);

				// Undo the move
				pBoard[index] = '.';

				// If the value of the current move is
				// more than the best value, then update
				// best/
				if (moveVal > bestVal)
				{
					bestMove.row = i;
					bestMove.col = j;
					bestVal = moveVal;
				}
			}
		}
	}

	*BestMove_Row = bestMove.row;
	*BestMove_Column = bestMove.col;

}

/*!
 * The minimax algorithm to determine the best move for the computer player.
 * @param player The computer player for whom the best move is determined.
 * @param depth The current depth in the minimax tree.
 * @param isMax Indicates whether the current player is maximizing or minimizing.
 * @return The best score for the current player's move.
 */

int TicTacBoard::minimax(Player *player, int depth, bool isMax)
{

	int row = getRow();
	int column = getColumn();
	char *pBoard = getPBoard();
	int index = 0;

	int score = evaluate(player);

	// If Maximizer has won the game return his/her
	// evaluated score

	if (score == 10)
		return score;

	// If Minimizer has won the game return his/her
	// evaluated score

	if (score == -10)
		return score;

	// If there are no more moves and no winner then
	// it is a tie

	if (isMovesLeft() == false)
		return 0;

	char active_player, oponent_player;

	if (player->getActivePlayer() == PlayerX)
	{
		active_player = 'X';
		oponent_player = 'O';
	}
	else if (player->getActivePlayer() == PlayerO)
	{
		active_player = 'O';
		oponent_player = 'X';
	}

	// If this maximizer's move
	if (isMax)
	{
		int best = -1000;

		// Traverse all cells
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{

				index = getIndex(i, j);

				// Check if cell is empty
				if (pBoard[index] == '.')
				{
					// Make the move
					pBoard[index] = active_player;

					// Call minimax recursively and choose
					// the maximum value

					best = std::max(best, minimax(player, depth + 1, !isMax));

					// Undo the move
					pBoard[index] = '.';
				}
			}
		}
		return best;
	}

	// If this minimizer's move
	else
	{
		int best = 1000;

		//      Traverse all cells
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				index = getIndex(i, j);

				// Check if cell is empty
				if (pBoard[index] == '.')
				{
					// Make the move
					pBoard[index] = oponent_player;

					// Call minimax recursively and choose
					// the minimum value
					best = std::min(best, minimax(player, depth + 1, !isMax));

					// Undo the move
					pBoard[index] = '.';
				}
			}
		}
		return best;
	}
}

