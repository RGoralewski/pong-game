#include "Player.h"
#include <iostream>



Player::Player(int _playerNumber)
{
	playerNumber = _playerNumber;
	if (playerNumber != 1 && playerNumber != 2)
	{
		std::cout << "Wrong player number for paddle! Paddle controlling is not possible." << std::endl;
	}

	std::cout << "Type player" << playerNumber << " name:" << std::endl;
	std::cin >> name;
	std::cout << "Player name: " << name << std::endl << std::endl;
}


Player::~Player()
{
}


void Player::Goal()
{
	points++;

	std::cout << name << "'s points: " << points << std::endl;
}

void Player::ResetPoints()
{
	points = 0;
}

int Player::GetPoints()
{
	return points;
}


std::string Player::GetName()
{
	return name;
}