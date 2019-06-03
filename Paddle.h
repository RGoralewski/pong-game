#pragma once
#include "PhysicalObject.h"

class Ball;

extern const int SCREEN_HEIGHT;


class Paddle :
	public PhysicalObject
{
public:

	//Maximum axis velocity of the paddle (pixels per second)
	static const int PADDLE_VEL = 800;

	Paddle();
	~Paddle();

	//Takes key presses and adjusts the paddle's velocity (require playerNumber to know which keys handle)
	void HandleEvent(SDL_Event& e, int playerNumber);

	//Updates paddle's position and doesn't let paddle out of the screen
	void Update(float time);

	//Friend checking collisions function
	friend bool collision(Paddle &p, Ball &b);

	//Bounce ball from one of the paddles
	friend void bounceBall(Paddle &p, int playerNumber, Ball &b);

private:
	//Y direction velocity
	float yVel;
};

