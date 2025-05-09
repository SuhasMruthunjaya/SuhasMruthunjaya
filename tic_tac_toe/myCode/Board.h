/*
 * Board.h
 *
 *  Created on: 17 Nov 2023
 *      Author: suhas
 */

#ifndef BOARD_H_
#define BOARD_H_

//< Board class represents a game board with rows, columns, and a character array.
class Board
{
private:

	//< Number of rows on the board.
	int row;

	//< Number of columns on the board.
	int column;

	//< Pointer to the character array representing the board.
	char *pBoard;

public:

	/*! Constructor for the Board class.
	 * @param: row:int , column:int - Initial values for row and column (default is 0)
	 * @return: no return type, as it is a constructor
	 */
	Board(int row = 0, int column = 0);

	//< Destructor for the Board class.
	virtual ~Board();

	/*! Getter method to retrieve the number of columns on the board.
	 * @returns: returns the column of type int
	 */
	int getColumn() const;

	/*! Getter method to retrieve the pointer to the character array representing the board.
	 * @returns: return value of type char*
	 */
	char* getPBoard() const;

	/*! Getter method to retrieve the number of rows on the board.
	 * 	@returns: return value of type int
	 */
	int getRow() const;

	/*!
	 * 	Method to calculate the index in the character array based on the given row and column.
	 *  @param: u_row:int - the row index of type int, u_column:int - the column index of type int
	 * 	@return: The calculated index in the character array.
	 */
	int getIndex(int u_row, int u_column) const;

};

#endif /* BOARD_H_ */
