#pragma once
#include "PhysicalObject.h"

class Paddle;

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

class Ball :
	public PhysicalObject
{
public:

	Ball();
	~Ball();

	//Update the position and bound from up and down edges of the screen
	void Update(float time);

	//Set ball's velocity direction (angle in radians)
	void SetDirection(double angle);

	//Increase velocity
	void IncreaseVelocity();

	//Bring back initial reference velocity
	void SetInitialReference();

	//Friend checking collisions function
	friend bool collision(Paddle &p, Ball &b);

	//Bounce ball from one of the paddles
	friend void bounceBall(Paddle &p, int playerNumber, Ball &b);

private:
	//x and y velocities
	float xVel, yVel;

	//reference velocity (changing with every ball bounce)
	int refVel;

	//Velocity increase single step (adding with every bounce to refVel)
	static const int VELOCITY_INCREASE_STEP = 10;

	//Initial reference velocity
	static const int INIT_REF_VELOCITY = 500;
};

