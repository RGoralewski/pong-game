#include "Paddle.h"

#include <iostream>

Paddle::Paddle()
	:PhysicalObject()
{
	yVel = 0;
}


Paddle::~Paddle()
{
}


void Paddle::HandleEvent(SDL_Event& e, int playerNumber)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Check which player pressed a key
		if (playerNumber == 1) 
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: yVel -= PADDLE_VEL; break;
			case SDLK_s: yVel += PADDLE_VEL; break;
			}
		}
		else if (playerNumber == 2)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: yVel -= PADDLE_VEL; break;
			case SDLK_DOWN: yVel += PADDLE_VEL; break;
			}
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Check which player released a key
		if (playerNumber == 1)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_w: yVel += PADDLE_VEL; break;
			case SDLK_s: yVel -= PADDLE_VEL; break;
			}
		}
		else if (playerNumber == 2)
		{
			//Adjust the velocity
			switch (e.key.keysym.sym)
			{
			case SDLK_UP: yVel += PADDLE_VEL; break;
			case SDLK_DOWN: yVel -= PADDLE_VEL; break;
			}
		}
	}
}


void Paddle::Update(float time)
{
	//Calculate a distance
	float distance = yVel*time;

	//Move the paddle up or down
	yPos += distance;

	//If the paddle went too far up or down
	if (yPos <= 0)
	{
		yPos = 0;
	}
	else if (yPos + height >= SCREEN_HEIGHT)
	{
		yPos = SCREEN_HEIGHT - height;
	}
}
