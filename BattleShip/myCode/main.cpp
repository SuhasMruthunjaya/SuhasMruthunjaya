// Standard (system) header files
#include <iostream>
#include <cstdlib>
// Add more standard header files as required
#include <string>

using namespace std;

// Add your project's header files here

#include "Board.h"
#include "ConsoleView.h"

#include "Shot.h"

//extern void assertTrue(bool condition, string failedMessage);
extern void part1tests();
extern void part2tests();
extern void part3tests();

// Main program
int main()
{
	cout << "BattleShip started." << endl << endl;

	Board board(10, 10);
	ConsoleView view(&board);

	view.print();

	part1tests();

	part2tests();

	part3tests();

	return 0;
}
