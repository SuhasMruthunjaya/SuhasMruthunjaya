/*
 * part3tests.cpp
 *
 *  Created on: 29 Dec 2023
 *      Author: suhas
 */

/*
 * part1tests.cpp
 *
 *  Created on: 15.11.2019
 *      Author: mnl
 */

#include <iostream>
#include "Board.h"
#include "ConsoleView.h"
#include "Shot.h"
#include <algorithm>

using namespace std;

extern void assertTrue(bool condition, string failedMessage);

#define Command_Line_InterPreter
//#define takeblowTest
//#define sunkenShipsTest

void part3tests()
{

	Board board(10, 10);
	ConsoleView view(&board);

//=========================Tests for takeblow===============================

#ifdef takeblowTest
assertTrue(board.getOwnGrid().placeShip(Ship(GridPosition('H', 6), GridPosition("I6"))),
			"The ship could not be placed on Board");

assertTrue(!(board.getOwnGrid().takeBlow(GridPosition("I6")) != HIT), "The ship is not hit");

assertTrue(!(board.getOwnGrid().takeBlow(GridPosition("H6")) != SUNKEN), "The ship did not sink ");

assertTrue(!(board.getOwnGrid().takeBlow(GridPosition("H4")) != NONE), "The miss hit is not working ");

view.print();

#endif

//================== Tests for sunkenShips=======================================

#ifdef sunkenShipsTest
board.getOpponentGrid().shotResult(Shot(GridPosition("B4")), HIT );
board.getOpponentGrid().shotResult(Shot(GridPosition("B3")), HIT);
board.getOpponentGrid().shotResult(Shot(GridPosition("B2")), SUNKEN);
board.getOpponentGrid().shotResult(Shot(GridPosition("B1")), NONE);


board.getOpponentGrid().shotResult(Shot(GridPosition("I1")), HIT);
board.getOpponentGrid().shotResult(Shot(GridPosition("G1")), HIT);
board.getOpponentGrid().shotResult(Shot(GridPosition("H1")), HIT);
board.getOpponentGrid().shotResult(Shot(GridPosition("J1")), SUNKEN);
board.getOpponentGrid().shotResult(Shot(GridPosition("E1")), NONE);
board.getOpponentGrid().shotResult(Shot(GridPosition("F1")), NONE);



board.getOpponentGrid().shotResult(Shot(GridPosition("G4")), NONE);
board.getOpponentGrid().shotResult(Shot(GridPosition("G5")), HIT);
board.getOpponentGrid().shotResult(Shot(GridPosition("G6")), HIT);
board.getOpponentGrid().shotResult(Shot(GridPosition("F5")), NONE);
board.getOpponentGrid().shotResult(Shot(GridPosition("I5")), NONE);


view.print();

#endif

//============================== command line interpreter =======================

#ifdef Command_Line_InterPreter
	int count = 1;

	do
	{
		string ship_bow, ship_stern;
		cout << "Please provide your" << count << " ship stern and bow" << endl;

		cout << "ship_bow: ";
		cin >> ship_bow;

		cout << "ship_stern: ";
		cin >> ship_stern;

		GridPosition ShipBow(ship_bow);
		GridPosition ShipStern(ship_stern);

		if (Ship(ShipBow, ShipStern).isValid() && ShipBow.isValid()
				&& ShipStern.isValid())
		{
			if (board.getOwnGrid().placeShip(Ship(ShipBow, ShipStern)))
				count++;
		}
		else
		{
			cout << " The ship is invalid, please provide proper GridPositions"
					<< endl;
		}

		view.print();

	} while (count < 11);

	string takeBlow, shotResult;
	int shotImpact;
	Impact shotImpactEnum;

	while (!(board.getOpponentGrid().getsunkenShips().size() == 10
			|| board.getOwnGrid().isShipsSunk()))
	{
		cout << " Please take a blow " << endl;
		cout << " Enter the GridPosition: ";
		cin >> takeBlow;

		if (GridPosition(takeBlow).isValid())
			board.getOwnGrid().takeBlow(Shot(GridPosition(takeBlow)));

		view.print();

		cout
				<< "Please enter your shot to the OpponentGrid and the Impact of it"
				<< endl;
		cout << " Enter the GridPosition: ";
		cin >> shotResult;

		cout << " Enter the Impact of the Shot: " << endl;
		cout << "0: MISS" << endl;
		cout << "1: HIT" << endl;
		cout << "2: SUNKEN" << endl;

		cin >> shotImpact;

		if (shotImpact == 0)
			shotImpactEnum = NONE;
		else if (shotImpact == 1)
			shotImpactEnum = HIT;
		else
			shotImpactEnum = SUNKEN;

		if (GridPosition(shotResult).isValid())
			board.getOpponentGrid().shotResult(Shot(GridPosition(shotResult)),
					shotImpactEnum);

		view.print();

	}

	if (board.getOpponentGrid().getsunkenShips().size() == 10)
	{
		cout << "You won !!! :-)" << endl;
	}
	else if (board.getOwnGrid().isShipsSunk())
	{
		cout << "You Lose !!! Opponent Player Won :-( " << endl;
	}

#endif

}

