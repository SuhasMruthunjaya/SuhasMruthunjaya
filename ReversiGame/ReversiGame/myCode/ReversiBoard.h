/*
 * ReversiBoard.h
 *
 *  Created on: 28 Oct 2023
 *      Author: suhas
 */

#ifndef REVERSIBOARD_H_
#define REVERSIBOARD_H_

#include "global.h"
#define ARRAY_END -99


typedef enum
{
	EMPTY = '.',
	WHITE = 'W',
	BLACK = 'B',

}BoardState;

typedef enum
{
	RIGHT,
	LEFT,
	UP,
	DOWN,
	UP_RIGHT,
	UP_LEFT,
	DOWN_LEFT,
	DOWN_RIGHT
}Directions;

typedef enum
{
	TRACE,
	FLIP
}reversiOperation;

typedef enum
{
	Player1,
	Player2
}currentPlayer;

class ReversiBoard
{
private:

	//! Number of rows in the ReversiBoard
	int rows;
	//! Number of columns in the ReversiBoard
	int columns;
	//! Dynamic array representing the board
	char* pBoard;
	//! The current active player in the game
	currentPlayer activePlayer;

public:
	/*! Constructor for initialising a ReversiBoard instance with optional rows and columns
	 * @param int rows, int columns - IN rows and columns as given by the user
	 * @return - Does not return anything as it is a constructor
	 */
	ReversiBoard(int rows = 0, int columns = 0);

	/*! Destructor for deleting the memory given for the pBoard in the constructor
	 * @return - No returntype
	*/
	virtual ~ReversiBoard();

	/*! Calculates the Index for the given rows and columns and returns it
	 * @return INT - returns the index
	 */
	int getIndex(int u_row, int u_column);

	/*! This functions checks for each and every Empty space '.' on the board and gives valid position
	 * 	for the user to place his pawn.
	 * 	@param: int* flip_directions : IN , takes in a pointer flip_directions and updates it with the
	 * 	flip directions - An array which contains the directions in which the pawns should flip, after
	 * 	the user has placed/choose to keep his pawn at a certain position.
	 * 	@return int* validPosArray: OUT, returns a validPosArray pointer which contains all the valid
	 * 	positions information, i.e, this array contains all the valid positions for the activePlayer.
	 */
	int* validPosition(int* validFlipDirection);

	/*! This functions shows the valid or available positions on the board. It calls validPosition() function
	 *  and put an 'x' at each valid position to indicate a valid position
	 *  @param: int* validFlipDirection : IN, pass as a parameter for validPosition
	 * 	@return int* result: OUT, returns a validPosArray pointer which contains all the valid
	 * 	positions information, i.e, this array contains all the valid positions for the activePlayer.
	 */
	int* availabePosition(int* validFlipDirection);

	/*!This function takes validPositions and validFlipDirection, and first prints all the validpositions
	 * for the user to select and takes the userInputIndex from the list presented, and flips the pawns in
	 * the required direction. The pBoard is then cleared with the indications of the valid positions and
	 * replaced with normal empty positions for the other player's game. The validpositions array is also
	 * cleared by the delete[] function
	 * @params int *validPositions, int* validFlipDirection: IN, validpositions and validflipdirection
	 * pointers.
	 * @return RC_t : returns RC_OK if the player pawn is set and flip is worked
	 */
	RC_t setPlayerPawn(int* validPositions, int* validFlipDirection);

	/*!This function shows the score after there is no more validpositions to show for any one of the
	 * player. The White and Black pawns are counted on the board and the count is displayed, the one
	 * who has more number of pieces on board wins the game
	 * @params: No params
	 * @return: returns RC_OK if the score is displayed on the console
	 */
	RC_t show_score();


	/*! Function to get the current Active player
	 * @param - none
	 * @return - Returns active Player
	 */
	currentPlayer getActivePlayer();

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
	RC_t validDirections(int index, int* direction_array = 0);

	/*! Get the number of rows in the board
	 * @return INT - returns the number of rows
	 */
	int getRows();

	/*! Get the number of columns in the board
	 * @return INT - returns the number of columns
	 */
	int getColumns();

	/*! Get the char* pBoard pointer pointing to the board from the ReversiBoard class
	 * @return char* - returns the pointer
	 */
	char* getPBoard()const;

	/*! Function to set the current Active player
	 * @param  currentPlayer - the current active player is passed as a parameter, which is assigned to
	 * objects activePlayer.
	 * @return - Returns RC_OK if the active Player is set
	 */
	RC_t setActivePlayer(currentPlayer activePlayer);



private:

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
	bool IsValid(int index, int* validPosBlack, int direction, reversiOperation action, int* flipped_direction = 0 );
};


#endif /* REVERSIBOARD_H_ */
