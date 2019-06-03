#include "Score.h"

#include<string>
#include<iostream>

extern const int SCREEN_WIDTH;

Score::Score()
{
	textColor = { 0,0,0 };
	posX = 0;
	posY = 20;
}


Score::~Score()
{
	texture.free();
}


void Score::SetTextColor(SDL_Color _textColor)
{
	textColor = _textColor;
}


void Score::Update(std::string firstPlayersName, int firstPlayersPoints, std::string secondPlayersName, int secondPlayersPoints)
{
	std::string scoreText = firstPlayersName + "\t" + std::to_string(firstPlayersPoints) + "\t\t\t" + std::to_string(secondPlayersPoints) + "\t" + secondPlayersName;

	if (!texture.loadFromRenderedText(scoreText.c_str(), textColor))
	{
		std::cout << "Failed to render Score texture!" << std::endl;
	}

	width = texture.getWidth();

	//Set score's X position to the middle of the screen width
	posX = SCREEN_WIDTH / 2 - width / 2;
}


void Score::Show() 
{
	texture.render(posX, posY);
}