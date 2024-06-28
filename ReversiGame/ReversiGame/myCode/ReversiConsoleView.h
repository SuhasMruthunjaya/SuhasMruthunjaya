/*
 * ReversiConsoleView.h
 *
 *  Created on: 13 Nov 2023
 *      Author: suhas
 */

#ifndef REVERSICONSOLEVIEW_H_
#define REVERSICONSOLEVIEW_H_


#include "ReversiBoard.h"

class ReversiConsoleView
{
private:

	//! pointer pointing to ReversiBoard
	ReversiBoard* pConsole;
public:

	/*!Constructor for initialising a ReversiConsoleView instance with taking an pointer of ReversiBoard* as
	 * a parameter
	 * @param ReversiBoard* board: a pointer pointing to the ReversiBoard
	 * @return - Does not return anything as it is a constructor
	 */
	ReversiConsoleView(ReversiBoard* board);

	/*! Destructor for deleting the pConsole pointer
	 *  @return - No returntype
	*/
	virtual ~ReversiConsoleView();

	/*!	This function prints the Board on the Console
	 *  @return - void
	 */
	void print();

	/*! Calculates the Index for the given rows and columns and returns it
	 * @return INT - returns the index
	 */
	int getIndex(int u_row, int u_column);
};

#endif /* REVERSICONSOLEVIEW_H_ */
