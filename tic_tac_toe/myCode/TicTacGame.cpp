/*
 * TicTacGame.cpp
 *
 *  Created on: 18 Nov 2023
 *      Author: suhas
 */

#include "TicTacGame.h"
#include <iostream>

#include "HumanPlayer.h"
#include "ComputerPlayer.h"

using namespace std;

/*!
 * Constructor for the TicTacGame class.
 * @param player An array of pointers to Player objects representing the players (default = nullptr).
 */
TicTacGame::TicTacGame(Player *player[2]) :
		board(tic_tac_row, tic_tac_column), screen(&board)
{
	// TODO Auto-generated constructor stub

	for (int i = 0; i < num_of_players; i++)
	{
		this->player[i] = 0;
	}

}

/*!
 * Destructor for the TicTacGame class.
 */
TicTacGame::~TicTacGame()
{
	// TODO Auto-generated destructor stub
}

/*!
 * Checks if there is a winner in the Tic Tac Toe game.
 * @return RC_CONDITIONSATISFIED if there is a winner, RC_OK otherwise.
 */
RC_t TicTacGame::checkWin()
{
	RC_t result = RC_OK;
	RC_t ret = RC_CONDITIONSATISFIED;
	PlayerType playerType = NO_Player;

	playerType = board.checkBoard(1, player);
	if (playerType == PlayerX || playerType == PlayerO)
	{
		screen.winner_msg(playerType);
		return ret;
	}

	playerType = board.checkBoard(3, player);
	if (playerType == PlayerX || playerType == PlayerO)
	{
		screen.winner_msg(playerType);
		return ret;
	}

	playerType = board.checkBoard(2, player);
	if (playerType == PlayerX || playerType == PlayerO)
	{
		screen.winner_msg(playerType);
		return ret;
	}

	playerType = board.checkBoard(4, player);
	if (playerType == PlayerX || playerType == PlayerO)
	{
		screen.winner_msg(playerType);
		return ret;
	}

	if (board.checkFullBoard())
	{
		screen.draw_msg();
		return ret;
	}

	return result;
}

/*!
 * Getter function to retrieve a player based on the player index.
 * @param playerIndex The index of the player in the array.
 * @return A pointer to the Player object if the index is valid, nullptr otherwise.
 */
Player* TicTacGame::getPlayer(int playerIndex) const
{
	if (playerIndex >= 0 && playerIndex < 2)
	{
		return player[playerIndex];
	}
	else
	{
		// Handle out-of-bounds access
		return nullptr;
	}
}

/*!
 * Handles player inputs for setting stones on the Tic Tac Toe board.
 * @param player The type of player for whom input is taken (PlayerX or PlayerO).
 * @param InputRow Reference to the variable storing the row input.
 * @param InputColumn Reference to the variable storing the column input.
 * @return RC_OK if the input is valid, RC_ERROR otherwise.
 */
RC_t TicTacGame::playerInputs(PlayerType player, int &InputRow,
		int &InputColumn)
{

	if (player == PlayerX)
	{
		screen.PlayerX_turn_Msg();
	}
	else if (player == PlayerO)
	{
		screen.PlayerO_turn_Msg();
	}

	cin >> InputRow >> InputColumn;

	if ((InputRow < 0) || (InputRow > 2) || (InputColumn < 0)
			|| (InputColumn > 2))
	{
		return RC_ERROR;
	}

	return RC_OK;

}

/*!
 * Runs the Tic Tac Toe game.
 */
void TicTacGame::run()
{
	RC_t retInvalidPos, retOutofBounds;
	screen.print();
	RC_t ret0;
	int UserInput;
	int InputRow, InputColumn;
	PlayerType first_player, second_player;

	screen.user_choice(&UserInput);
	if (UserInput == 1)
	{
		player[0] = new HumanPlayer(PlayerX);
		first_player = HUMAN_PLAYER;
		player[1] = new HumanPlayer(PlayerO);
		second_player = HUMAN_PLAYER;
	}
	else if (UserInput == 2)
	{

		player[0] = new HumanPlayer(PlayerX);
		first_player = HUMAN_PLAYER;
		player[1] = new ComputerPlayer(PlayerO);
		second_player = COMPUTER_PLAYER;
	}
	else if (UserInput == 3)
	{
		player[0] = new ComputerPlayer(PlayerX);
		first_player = COMPUTER_PLAYER;
		player[1] = new HumanPlayer(PlayerO);
		second_player = HUMAN_PLAYER;
	}
	else if (UserInput == 4)
	{
		player[0] = new ComputerPlayer(PlayerX);
		first_player = COMPUTER_PLAYER;
		player[1] = new ComputerPlayer(PlayerO);
		second_player = COMPUTER_PLAYER;
	}

	while (1)
	{
		if (first_player == COMPUTER_PLAYER)
		{
			player[0]->setStone(&board);

			screen.print();

			ret0 = checkWin();
			if (ret0 == RC_CONDITIONSATISFIED)
			{
				break;
			}
		}
		else if (first_player == HUMAN_PLAYER)
		{
			do
			{
				retOutofBounds = playerInputs(PlayerX, InputRow, InputColumn);

				if (retOutofBounds != RC_OK)
				{
					screen.Wrong_move_Error_Msg(OUTOFBOUNDS);
				}

				retInvalidPos = getPlayer(0)->setStone(&board, InputRow,
						InputColumn);
				if (retInvalidPos != RC_OK)
				{
					//Error
					screen.Wrong_move_Error_Msg(INVALIDMOVE);
				}
			} while (retInvalidPos != RC_OK || retOutofBounds != RC_OK);

			screen.print();

			ret0 = checkWin();
			if (ret0 == RC_CONDITIONSATISFIED)
			{
				break;
			}
		}

		if (second_player == COMPUTER_PLAYER)
		{
			player[1]->setStone(&board);

			screen.print();

			ret0 = checkWin();
			if (ret0 == RC_CONDITIONSATISFIED)
			{
				break;
			}
		}
		else if (second_player == HUMAN_PLAYER)
		{
			do
			{
				retOutofBounds = playerInputs(PlayerO, InputRow, InputColumn);

				if (retOutofBounds != RC_OK)
				{
					screen.Wrong_move_Error_Msg(OUTOFBOUNDS);
				}

				retInvalidPos = getPlayer(1)->setStone(&board, InputRow,
						InputColumn);
				if (retInvalidPos != RC_OK)
				{
					//Error
					screen.Wrong_move_Error_Msg(INVALIDMOVE);
				}
			} while (retInvalidPos != RC_OK || retOutofBounds != RC_OK);

			screen.print();

			ret0 = checkWin();
			if (ret0 == RC_CONDITIONSATISFIED)
			{
				break;
			}
		}
	}
}

