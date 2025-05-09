/*
 * TicTacScreen.cpp
 *
 *  Created on: 17 Nov 2023
 *      Author: suhas
 */

#include "TicTacScreen.h"
#include <iostream>

using namespace std;

//< Constructor for the TicTacScreen class

TicTacScreen::TicTacScreen(TicTacBoard *pConsole)
{
	// TODO Auto-generated constructor stub

	this->pConsole = pConsole;
}

//< Destructor for the TicTacScreen class

TicTacScreen::~TicTacScreen()
{
	// TODO Auto-generated destructor stub
}

//< Prints the Tic Tac Toe board on the console

void TicTacScreen::print()
{
	char *pConsoleBoard = pConsole->getPBoard();

	//< Loop through rows and columns to print the board

	for (int i = 0; i < pConsole->getRow(); i++)
	{
		for (int j = 0; j < pConsole->getColumn(); j++)
		{
			int index = pConsole->getIndex(i, j);
			cout << pConsoleBoard[index] << "\t";
		}
		cout << endl;
	}

}

//< Displays an error message for a wrong move

void TicTacScreen::Wrong_move_Error_Msg(ERROR_MSG msg)
{
	if (msg == OUTOFBOUNDS)
		cout << " The row and column you mentioned is Out of the range" << endl;
	if (msg == INVALIDMOVE)
		cout << " Invalid Position selected. Please Try again " << endl;

}

//< Displays a message indicating PlayerX's turn

void TicTacScreen::PlayerX_turn_Msg()
{
	cout
			<< " PlayerX turn. Please mention the row and column you want to place "
					"your pawn" << endl;
}

//< Displays a message indicating PlayerO's turn

void TicTacScreen::PlayerO_turn_Msg()
{
	cout
			<< " PlayerO turn. Please mention the row and column you want to place "
					"your pawn" << endl;
}

//< Displays a message indicating the winner of the game

void TicTacScreen::winner_msg(PlayerType player)
{
	if (player == PlayerX)
		cout << "PlayerX won" << endl;
	else if (player == PlayerO)
		cout << "PlayerO Won" << endl;

}

//< Displays a message indicating a draw in the game

void TicTacScreen::draw_msg()
{
	cout << " The game is draw!!" << endl;
}

//< Asks the user to choose the type of game

void TicTacScreen::user_choice(int *userInput)
{
	cout << " Please choose one of the following " << endl;
	cout << " 1. Human vs Human " << endl;
	cout << " 2. Human vs Computer " << endl;
	cout << " 3. Computer vs Human" << endl;
	cout << " 4. Computer vs Computer" << endl;

	cin >> *userInput;

}
