// Standard (system) header files
#include <iostream>
#include <cstdlib>
#include "ReversiBoard.h"
#include "ReversiConsoleView.h"
using namespace std;

//#define Testing

int main ()
{
    // TODO: Add your program code here
	cout << "ReversiGame started." << endl << endl;

#ifdef Testing
	ReversiBoard board(4,4);
#else
	cout << "Please enter the same even numbered size (eg.6 6) of the game: "  << endl;
	int userInputRows = 0, userInputColumns = 0;
	cin >> userInputRows >> userInputColumns;
	ReversiBoard board(userInputRows,userInputColumns);
#endif

	ReversiConsoleView board_view(&board);

	while(1)
	{

		int validFlipDirection[board.getRows() * board.getColumns()] ;

		if(board.getActivePlayer() == Player1)
		{
			std::cout <<  "Player1 Turn" << std::endl;
		}
		else if(board.getActivePlayer() == Player2)
		{
			std::cout <<  "Player2 Turn" << std::endl;
		}

		int* result = board.availabePosition(validFlipDirection);

		if(result[0] == ARRAY_END)
			{
				board.show_score();
				break;
			}

			board_view.print();

			RC_t ret = board.setPlayerPawn(result,validFlipDirection);
			if(ret != RC_OK)
			{
				cout << "Error in setting the player pawn and Flipping Logic" << endl;
			}

			board_view.print();


		if(board.getActivePlayer() == Player1)
		{
			board.setActivePlayer(Player2);
		}
		else if(board.getActivePlayer() == Player2)
		{
			board.setActivePlayer(Player1);
		}



	}


	return 0;
}
