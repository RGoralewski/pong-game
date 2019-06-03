#pragma once

#include "Player.h"

#include <string>

class Score
{
public:
	Score();
	~Score();

	//Sets text color
	void SetTextColor(SDL_Color _textColor);

	//Takes in players' names and points and makes a texture to Show
	void Update(std::string firstPlayersName, int firstPlayersPoints, std::string secondPlayersName, int secondPlayersPoints);

	//Shows a score on the screen
	void Show();

private:
	//Score texture from font
	LTexture texture;

	//Text color
	SDL_Color textColor;

	//Score position
	int posX, posY;

	//Score dimensions
	int width;
};

