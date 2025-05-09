/*
 * Board.cpp
 *
 *  Created on: 17 Nov 2023
 *      Author: suhas
 */

#include "Board.h"

/*! Constructor for the Board class.
 * @param: row:int , column:int - Initial values for row and column (default is 0)
 * @return: no return type, as it is a constructor
 */
Board::Board(int row, int column)
{
	// TODO Auto-generated constructor stub

	this->row = row;
	this->column = column;

	this->pBoard = new char[row * column];

	for (int i = 0; i < row * column; i++)
	{
		pBoard[i] = '.';
	}

}

Board::~Board()
{
	// TODO Auto-generated destructor stub
}

/*! Getter method to retrieve the number of columns on the board.
 * @returns: returns the column of type int
 */
int Board::getColumn() const
{
	return column;
}

/*! Getter method to retrieve the pointer to the character array representing the board.
 *  * @returns: return value of type char*
 */
char* Board::getPBoard() const
{
	return pBoard;
}

/*! Getter method to retrieve the number of rows on the board.
 * 	@returns: return value of type int
 */
int Board::getRow() const
{
	return row;
}

/*!
 * 	Method to calculate the index in the character array based on the given row and column.
 * 	@param: u_row:int - the row index of type int, u_column:int - the column index of type int
 * 	@return: The calculated index in the character array.
 */
int Board::getIndex(int u_row, int u_column) const
{
	int index = 0;
	index = u_row * column + u_column;
	return index;

}

