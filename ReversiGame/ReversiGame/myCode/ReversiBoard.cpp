/*
 * ReversiBoard.cpp
 *
 *  Created on: 28 Oct 2023
 *      Author: suhas
 */

#include "ReversiBoard.h"
#include <stdlib.h>
#include <iostream>


//#define Testing


/*! Constructor for initialising a ReversiBoard instance with optional rows and columns
 * @param int rows, int columns - IN rows and columns as given by the user
 * @return - Does not return anything as it is a constructor
 */
ReversiBoard::ReversiBoard(int rows, int columns)
{
	this->rows = rows;
	this->columns = columns;

	int size = rows * columns;

	pBoard = new char[size];

	for (int i = 0; i < (this->rows * this->columns); i++)
	{
		pBoard[i] = EMPTY;
	}



#ifndef Testing
//To get the centre pieces ready...
	int index = 0;
	index = getIndex(this->rows / 2, this->columns / 2);
	pBoard[index] = BLACK;
	pBoard[index - 1] = WHITE;
	pBoard[index - this->columns] = WHITE;
	pBoard[index - this->columns - 1] = BLACK;

	activePlayer = Player1;


#else

	pBoard[6] = BLACK;
	pBoard[7] = WHITE;
	pBoard[10] = WHITE;
	pBoard[11] = BLACK;

#endif

	std::cout << "Allocated board of dimension x = " << this->rows;
	std::cout << " y = " << this->columns << " at address " << this
			<< std::endl;
}



/*! Destructor for deleting the memory given for the pBoard in the constructor
 * @return - No returntype
 */
ReversiBoard::~ReversiBoard()
{
	// TODO Auto-generated destructor stub
	delete pBoard;
	std::cout << " The memory is deleted at " << this << std::endl;
}

/*! Get the number of rows in the board
 * @return INT - returns the number of rows
 */
int ReversiBoard::getRows()
{
	return rows;
}

/*! Get the number of columns in the board
 * @return INT - returns the number of columns
 */
int ReversiBoard::getColumns()
{
	return columns;
}

/*! Get the char* pBoard pointer pointing to the board from the ReversiBoard class
 * @return char* - returns the pointer
 */
char* ReversiBoard::getPBoard() const
{
	return pBoard;
}

/*! Calculates the Index for the given rows and columns and returns it
 * @return INT - returns the index
 */
int ReversiBoard::getIndex(int u_row, int u_column)
{
	int index = 0;
	index = u_row * columns + u_column;
	return index;

}

/*! This functions checks for each and every Empty space '.' on the board and gives valid position
 * 	for the user to place his pawn.
 * 	@param: int* flip_directions : IN , takes in a pointer flip_directions and updates it with the
 * 	flip directions - An array which contains the directions in which the pawns should flip, after
 * 	the user has placed/choose to keep his pawn at a certain position.
 * 	@return int* validPosArray: OUT, returns a validPosArray pointer which contains all the valid
 * 	positions information, i.e, this array contains all the valid positions for the activePlayer.
 */
int* ReversiBoard::validPosition(int* flip_directions)
{
#ifndef Testing

	int *validPosArray = new int[rows * columns];
	if (validPosArray == NULL)
	{
		std::cout << " Malloc was unsuccessful " << std::endl;
		return 0;
	}
	int direction_array[rows * columns] = {0};

	int flip_pos = 0;

#else
	int *validPosArray = 0;
	int direction_array[16];
#endif


	int count = 0;
	int validPosBlack = 0;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			int index = getIndex(i, j);

			if (pBoard[index] != EMPTY)
				continue;
			else
			{

				validDirections(index, direction_array);



#ifdef Testing
				std::cout << "Array started " << index << std::endl;
				for(int l=0; direction_array[l] != ARRAY_END; l++)
				{
					std::cout << direction_array[l] << std::endl;
				}

#else

				for(int k=0; direction_array[k] != ARRAY_END; k++)
				//for(int i = 0; i < 8; i ++)
				{
					if (IsValid(index, &validPosBlack, direction_array[k], TRACE, &flip_pos))
					{

						validPosArray[count] = validPosBlack;
						flip_directions[count] = flip_pos;
						count = count + 1;
					}
				}
#endif

			}
		}
	}


	flip_directions[count] = ARRAY_END;
	validPosArray[count] = ARRAY_END;


	return validPosArray;
}

/*! This function takes in index and a pointer "direction_array" and updates this pointer with the
 *  valid directions it should trace with respect to its position on the board.
 *  @param int index - IN, takes in Index to get the row and column of the position to decide its
 *  valid trace directions (the one in the corner should not trace or look in the direction where
 *  there are no points or Empty spaces)
 *  @param int* direction_array - OUT, it takes in a pointer and updates with all the valid direction
 *  to trace with respect to its position on the board
 *  @return RC_t - returns RC_OK if the function worked properly ( if the direction_array is filled
 *  with valid directions to trace)
 */
RC_t ReversiBoard::validDirections(int index, int* direction_array)
{


#ifdef Doubts

	/* This pointer was returned with having int* has a return value, the memory was not deleted after use,
	 which resulted in complete heap usage and the malloc ( or memory creation) was not successful.
	 The strange behaviour observed: The right output was observed while debugging, but not in the
	 actual runtime*/
	int *direction_array = new int(rows * columns);
#endif

	int row_calc = 0, column_calc = 0;
	row_calc = index / rows;
	column_calc = index % columns;

	if ((row_calc == 0 && column_calc == 0)) // first position
	{
		direction_array[0] = +1;
		direction_array[1] = +rows;
		direction_array[2] = +rows + 1;
		direction_array[3] = ARRAY_END;

	}
	//! the positions excluding the last one and the first one in the first row
	else if ((row_calc == 0) && (column_calc > 0 && column_calc < columns-1))
	{
		direction_array[0] = +1;
		direction_array[1] = +rows;
		direction_array[2] = +rows + 1;
		direction_array[3] = +rows - 1;
		direction_array[4] = -1;

		direction_array[5] = ARRAY_END;

	}
	//! the last position in the first row
	else if ((row_calc == 0 && column_calc == columns-1))
	{
		direction_array[0] = -1;
		direction_array[1] = +rows;
		direction_array[2] = +rows - 1;
		direction_array[3] = ARRAY_END;

	}
	//! the positions excluding the last one and the first one  in the first column
	else if((column_calc == 0) && (row_calc > 0 && row_calc < rows-1))
	{
		direction_array[0] = +1;
		direction_array[1] = +rows;
		direction_array[2] = -rows;
		direction_array[3] = +rows + 1;
		direction_array[4] = -rows + 1;
		direction_array[5] = ARRAY_END;

	}
	//! the last position in the first column
	else if((column_calc == 0) && (row_calc == rows - 1))
	{
		direction_array[0] = +1;
		direction_array[1] = -rows;
		direction_array[2] = -rows + 1;
		direction_array[3] = ARRAY_END;

	}
	//! the positions excluding first and last positions at the last row
	else if((row_calc == rows-1) && (column_calc > 0 && column_calc < columns-1))
	{
		direction_array[0] = +1;
		direction_array[1] = -rows;
		direction_array[2] = -rows + 1;
		direction_array[3] = -rows - 1;
		direction_array[4] = -1;

		direction_array[5] = ARRAY_END;

	}
	//! the last position
	else if ((row_calc == rows-1 && column_calc == columns-1))
	{
		direction_array[0] = -1;
		direction_array[1] = -rows;
		direction_array[2] = -rows - 1;
		direction_array[3] = ARRAY_END;

	}
	//! the positions excluding first and last in the last column
	else if((column_calc == columns-1) && (row_calc > 0 && row_calc < rows-1))
	{
		direction_array[0] = -1;
		direction_array[1] = +rows;
		direction_array[2] = -rows;
		direction_array[3] = +rows - 1;
		direction_array[4] = -rows - 1;
		direction_array[5] = ARRAY_END;

	}
	//! All the positions excluding boundary
	else
	{
		direction_array[0] = +1;
		direction_array[1] = -1;
		direction_array[2] = -rows;
		direction_array[3] = +rows;
		direction_array[4] = -rows + 1;
		direction_array[5] = -rows - 1;
		direction_array[6] = +rows +1;
		direction_array[7] = +rows -1;


		direction_array[8] = ARRAY_END;

	}

	return RC_OK;

}

/*! This functions shows the valid or available positions on the board. It calls validPosition() function
 *  and put an 'x' at each valid position to indicate a valid position
 *  @param: int* validFlipDirection : IN, pass as a parameter for validPosition
 * 	@return int* result: OUT, returns a validPosArray pointer which contains all the valid
 * 	positions information, i.e, this array contains all the valid positions for the activePlayer.
 */

int* ReversiBoard::availabePosition(int* validFlipDirection)
{

	std::cout << "The available locations are marked with 'x'. Please Enter the index number "
			"where you want to place your stone " << std::endl;

	int* result = validPosition(validFlipDirection);

	if(result == NULL)
	{
		std::cout << " result is null" << std::endl;
	}

	// Need to stop the game here if the result[0] == ARRAY_END;


	for(int i=0 ; result[i] != ARRAY_END; i++)
	{

		this->pBoard[result[i]] = 'x';
	}

	return result;
}

/*!This function takes validPositions and validFlipDirection, and first prints all the validpositions
 * for the user to select and takes the userInputIndex from the list presented, and flips the pawns in
 * the required direction. The pBoard is then cleared with the indications of the valid positions and
 * replaced with normal empty positions for the other player's game. The validpositions array is also
 * cleared by the delete[] function
 * @params int *validPositions, int* validFlipDirection: IN, validpositions and validflipdirection
 * pointers.
 * @return RC_t : returns RC_OK if the player pawn is set and flip is worked
 */
RC_t ReversiBoard::setPlayerPawn(int *validPositions, int* validFlipDirection)
{
	std::cout << "The available index are: ";

		for(int i=0 ; validPositions[i] != ARRAY_END; i++)
		{
			printf("%d ", validPositions[i]);
		}

		std::cout << std::endl;

		std::cout << "Please enter the index where you want to place your stone from the above list"  << std::endl;

		int userInputIndex = 0;
		std::cin >> userInputIndex;

		for(int i =0; validPositions[i] != ARRAY_END; i++)
		{
			if(validPositions[i] == userInputIndex)
			{
				IsValid(userInputIndex,0,validFlipDirection[i],FLIP);
			}
		}


		for(int i = 0; i < rows * columns; i++)
		{
			if(pBoard[i] == 'x')
			{
				pBoard[i] = EMPTY;
			}
		}

		// Deallocate the memory when you're done with the array
		delete[] validPositions;

		return RC_OK;
}


/*!This function shows the score after there is no more validpositions to show for any one of the
 * player. The White and Black pawns are counted on the board and the count is displayed, the one
 * who has more number of pieces on board wins the game
 * @params: No params
 * @return: returns RC_OK if the score is displayed on the console
 */

RC_t ReversiBoard::show_score()
{
	std::cout << "There are no valid positions anymore" << std::endl;

					int Black_count = 0, White_count = 0;

					for(int i = 0; i < rows * columns; i++)
					{
						if(pBoard[i] == BLACK)
							Black_count = Black_count + 1 ;
						else if(pBoard[i] == WHITE)
							White_count= White_count + 1 ;

					}

					std::cout << "White count: " << White_count << std::endl;
					std::cout << "Black count: " << Black_count << std::endl;



					if(Black_count > White_count)
						std::cout << " First Player Won " << std::endl;
					else if(Black_count < White_count)
						std::cout << "Second Player Won" << std::endl;
					else if(Black_count == White_count)
						std::cout << " The game is tie" << std::endl;

					return RC_OK;

}

/*! This function traces and flips in the given direction. It is used to both calculating the valid
 * position and also flip the pawns.
 * @param int index- IN, Index is passed, used for tracing and also to flip
 * @param int* validPis - OUT, valid pos containing the valid position.
 * @param int direction - IN, direction followed to trace or flip
 * @param reversiOperatiom - IN, flip or Trace action to be carried out
 * @param int* flipped_direction - OUT, the direction which supposed to be flipped, this information is
 * taken out while tracing, which is needed while flipping.
 * @return bool - if Trace or Flip actions are carried out, this function returns true or false
 */

bool ReversiBoard::IsValid(int index, int *validPos, int direction, reversiOperation action, int* flipped_direction)
{
	int row_calc = 0, column_calc = 0;

	bool result = false;
	int original_index = 0;
	original_index = index;
	int PLAYERPAWN = 0, OPPONENTPAWN = 0;


	if(activePlayer == Player1)
	{
		PLAYERPAWN = BLACK;
		OPPONENTPAWN = WHITE;
	}
	else if(activePlayer == Player2)
	{
		PLAYERPAWN = WHITE;
		OPPONENTPAWN = BLACK;
	}

	if (pBoard[index + direction] == OPPONENTPAWN)// Opponent Player pawn
	{
		if(action == TRACE)
		{

			index = index + direction;

			row_calc = index / rows;
			column_calc = index % columns;


		}
		else if(action == FLIP)
		{
			pBoard[index] = PLAYERPAWN;	// Same pawn
			index = index + direction;

			row_calc = index / rows;
			column_calc = index % columns;

		}



		while ((pBoard[index + direction] == OPPONENTPAWN) &&
			       ((direction == -1 || direction == 1) ? (column_calc != columns - 1 && column_calc != 0) : true) &&
				   ((direction == -rows+1 || direction == -rows-1) ? (column_calc != columns - 1 && column_calc != 0) : true)&&
				   ((direction == rows+1 || direction == rows-1) ? (column_calc != columns - 1 && column_calc != 0) : true))

		{
			if(action == TRACE)
			{
				index = index + direction;
			}
			else if(action == FLIP)
			{
				pBoard[index] = PLAYERPAWN;		// same pawn
				index = index + direction;
			}

			row_calc = index / rows;
			column_calc = index % columns;

		}

		if((pBoard[index + direction] == PLAYERPAWN) &&
			    ((direction == -1 || direction == 1) ? (column_calc != columns - 1 && column_calc != 0) : true)&&
				((direction == -rows+1 || direction == -rows-1) ? (column_calc != columns - 1 && column_calc != 0) : true) &&
				((direction == rows+1 || direction == rows-1) ? (column_calc != columns - 1 && column_calc != 0) : true))
		{


			if(action == TRACE)
			{
			*validPos = original_index;
		    *flipped_direction = direction;

		    result = true;

			}
			else if(action == FLIP)
			{
				pBoard[index] = PLAYERPAWN;		// Same pawn
				result = true;
			}
		}
		else if (pBoard[index + direction] == EMPTY)
		{
			result = false;
		}
	}

	return result;
}


/*! Function to get the current Active player
 * @param - none
 * @return - Returns active Player
 */
currentPlayer ReversiBoard::getActivePlayer()
{
	return activePlayer;
}

/*! Function to set the current Active player
 * @param  currentPlayer - the current active player is passed as a parameter, which is assigned to
 * objects activePlayer.
 * @return - Returns RC_OK if the active Player is set
 */
RC_t ReversiBoard::setActivePlayer(currentPlayer activePlayer)
{
	this->activePlayer = activePlayer;
	return RC_OK;
}
