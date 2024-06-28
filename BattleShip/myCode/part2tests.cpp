/*
 * part1tests.cpp
 *
 *  Created on: 15.11.2019
 *      Author: mnl
 */

#include <iostream>
#include "Board.h"
#include "ConsoleView.h"
#include <algorithm>

using namespace std;

//#define playerHas10ShipsTest
//#define shipOutOfBoardTest
//#define shipsPlacesAtGridEdge

extern void assertTrue(bool condition, string failedMessage);

void part2tests()
{

//=====================Ship Touching each other========================================
	Ship s1 = Ship
	{ GridPosition
	{ "B2" }, GridPosition
	{ "B3" } };
	Ship s2 = Ship
	{ GridPosition
	{ "E3" }, GridPosition
	{ "E4" } };

	std::set<GridPosition> intersectionSet;
	std::set<GridPosition> ship1_BlockedArea = s1.blockedArea();
	std::set<GridPosition> ship2_OccupiedArea = s2.occupiedArea();

	std::set_intersection(ship1_BlockedArea.begin(), ship1_BlockedArea.end(),
			ship2_OccupiedArea.begin(), ship2_OccupiedArea.end(),
			std::inserter(intersectionSet, intersectionSet.begin()));

	assertTrue(intersectionSet.empty(), " The ship is touching each other");

//=============== The grid fields occupied by a ship form a straight line=================

	assertTrue(
			(s1.getBow().getRow() == s1.getStern().getRow())
					|| (s1.getBow().getColumn() == s1.getStern().getColumn()),
			"The grid fields occupied by a ship is not a straight line");

//========================= Each player has 10 ships===================================

	Board board(10, 10);
	ConsoleView view(&board);

#ifdef playerHas10ShipsTest
	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('A', 1), GridPosition("A5"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('C', 1), GridPosition("F1"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('C', 3), GridPosition("F3"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('D', 7), GridPosition("F7"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('H', 8), GridPosition("H10"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('J', 1), GridPosition("J3"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('H', 1), GridPosition("H2"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('B', 9), GridPosition("C9"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('H', 6), GridPosition("I6"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('E', 9), GridPosition("E10"))),
			"The ship could not be placed on Board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('J', 9), GridPosition("J10"))),
			"The ship could not be placed on Board");

	view.print();

	assertTrue(!(board.getOwnGrid().getShip().size() > 10), " The board has more than 10 ships");

#endif

	//========================== Valid Ships going out of the board==============================

#ifdef shipOutOfBoardTest
	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('B', 0), GridPosition("B3"))),
			" The ship goes out of the board");

	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('I', 3), GridPosition("K3"))),
			" The ship goes out of the board");

	view.print();
#endif

//=============== Ships must be positioned horizontally or vertically=================

	assertTrue(
			(s1.getBow().getRow() == s1.getStern().getRow())
					|| (s1.getBow().getColumn() == s1.getStern().getColumn()),
			"The grid fields occupied by a ship is not a straight line");

//==================. Ships may be positioned at the edges of the grid ======================

#ifdef shipsPlacesAtGridEdge
	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('A', 1), GridPosition("A4"))),
			" Ships may not be positioned at the edges of the grid");
	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('D', 1), GridPosition("H1"))),
			" Ships may not be positioned at the edges of the grid");
	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('J', 6), GridPosition("J9"))),
			" Ships may not be positioned at the edges of the grid");
	assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('D', 10), GridPosition("F10"))),
			" Ships may not be positioned at the edges of the grid");


	view.print();

#endif

}

