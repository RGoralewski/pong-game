#pragma once

#include<string>
#include "Paddle.h"

class Player
{
public:
	Player(int _playerNumber);
	~Player();

	//Increments points
	void Goal();

	//Zero points
	void ResetPoints();

	//Get points
	int GetPoints();

	//Get name
	std::string GetName();


	
	//player's paddle
	Paddle paddle;

	//number of player (class expects two players so playerNumber can be 1 or 2;
	//for player number 1 - there are w and s keys, for player 2 - up and down arrow keys)
	int playerNumber;

private:

	//player's points
	int points;

	//player's name
	std::string name;
};

