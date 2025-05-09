/*
 * Player.cpp
 *
 *  Created on: 18 Nov 2023
 *      Author: suhas
 */

#include "Player.h"
#include "TicTacGame.h"

#include <iostream>

//< Constructor for the Player class

Player::Player(PlayerType active_player)
{
	//< Initialize the player's symbol and types based on the provided active player type

	if (active_player == PlayerX)
	{
		symbol = 'X';
		this->active_player = PlayerX;
		this->opponent_player = PlayerO;
	}
	else if (active_player == PlayerO)
	{
		symbol = 'O';
		this->active_player = PlayerO;
		this->opponent_player = PlayerX;
	}

}

//< Destructor for the Player class

Player::~Player()
{
	// TODO Auto-generated destructor stub
}

//< Getter function to retrieve the symbol of the player
char Player::getSymbol() const
{
	return symbol;
}

//< Getter function to retrieve the type of the active player
PlayerType Player::getActivePlayer() const
{
	return active_player;
}
