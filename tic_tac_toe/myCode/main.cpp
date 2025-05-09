// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
// #include <string>
#include "Board.h"
#include "TicTacScreen.h"
#include "TicTacGame.h"
#include "HumanPlayer.h"

using namespace std;

// Add your project's header files here
// #include "CFraction.h"

// Main program
int main()
{
	// TODO: Add your program code here
	cout << "tic_tac_toe started." << endl << endl;

	TicTacGame game;

	game.run();

	return 0;
}
