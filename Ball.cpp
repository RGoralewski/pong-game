#include "Ball.h"



Ball::Ball()
	:PhysicalObject()
{
	xVel = 0;
	yVel = 0;
	refVel = INIT_REF_VELOCITY;
}


Ball::~Ball()
{
}


void Ball::Update(float time)
{
	//Update position of the ball (pixels per second)
	xPos += xVel*time;
	yPos += yVel*time;

	//Check if it is bounding from up or down edge of the screen
	if (yPos <= 0)
	{
		yPos = 0;
		yVel = -yVel;
	}
	else if (yPos + height >= SCREEN_HEIGHT)
	{
		yPos = SCREEN_HEIGHT - height;
		yVel = -yVel;
	}
}


void Ball::SetDirection(double angle)
{
	xVel = refVel*cos(angle);
	yVel = refVel*sin(angle);
}


void Ball::IncreaseVelocity()
{
	refVel = refVel + VELOCITY_INCREASE_STEP;
}


void Ball::SetInitialReference()
{
	refVel = INIT_REF_VELOCITY;
}