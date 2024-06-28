/*
 * ReversiConsoleView.cpp
 *
 *  Created on: 13 Nov 2023
 *      Author: suhas
 */

#include "ReversiConsoleView.h"
#include <iostream>

/*!Constructor for initialising a ReversiConsoleView instance with taking an pointer of ReversiBoard* as
 * a parameter
 * @param ReversiBoard* board: a pointer pointing to the ReversiBoard
 * @return - Does not return anything as it is a constructor
 */
ReversiConsoleView::ReversiConsoleView(ReversiBoard* board)
{
	// TODO Auto-generated constructor stub
	std::cout << " The memory is constructed at " << this << std::endl;
	this->pConsole = board;

}

/*! Destructor for deleting the pConsole pointer
 *  @return - No returntype
*/
ReversiConsoleView::~ReversiConsoleView()
{
	// TODO Auto-generated destructor stub
	delete pConsole;
	std::cout << " The memory is deleted at " << this << std::endl;
}

/*! Calculates the Index for the given rows and columns and returns it
 * @return INT - returns the index
 */
int ReversiConsoleView::getIndex(int u_row, int u_column)
{
	int index = 0;
	index = u_row * pConsole->getColumns() + u_column;
	return index;

}

/*!	This function prints the Board on the Console
 *  @return - void
 */
void ReversiConsoleView::print()
{

	char* pBoard = pConsole->getPBoard();

	for (int i = 0; i < pConsole->getRows(); i++)
	{
		for (int j = 0; j < pConsole->getColumns(); j++)
		{
			int index = getIndex(i, j); // Map 2D coordinates to 1D array index
			std::cout << pBoard[index] << "\t\t";

		}
		std::cout << std::endl;
		std::cout << std::endl;

	}

}
