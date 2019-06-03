/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <iostream>

#define PI 3.14159265

//Using classes
#include "Paddle.h"
#include "Ball.h"
#include "Player.h"
#include "Score.h"

//#undef main

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;




//A background for the game
LTexture background;

//"Press SPACE to start a new game" texture
LTexture pressSpaceTexture;

//Texture to show who won the last game (with press SPRACE information)
LTexture winnerTexture;

//Version and producer texture
LTexture productionTexture;

//A paddle number one
Player player1(1);

//A paddle number 2
Player player2(2);

//A ball
Ball ball;

//A score
Score score;



//Time of last frame
Uint32 lastFrameTime = 0;

//Boolean to know what should be render -> paddles, ball and score (a match) or an information to start a new game
bool matchIsOver = true;

//Name of the winner of the last game (in the beggining it is " " so no information about the winner is showed)
std::string winnerName = " ";



//Last paddle that bounced the ball (in the beginning it is 0 so both paddles can bouce the ball -> according to "if" in bouceBall function)
//It is using playerNumber in Paddle class (which is 1 or 2)
int lastBouncingPaddle = 0;

//Constant maximum bounce angle of the ball from the paddle
const double MAX_BOUNCE_ANGLE = 5 * PI / 12;

//Bounce ball from one of the paddles
void bounceBall(Paddle &p, int playerNumber, Ball &b)
{
	//Checking collisions with paddle
	if (collision(p, b) && playerNumber!=lastBouncingPaddle) {	//if there's a collision and if this paddle bounce the ball first time

		//Increase reference velocity of the ball (becouse there was a bounce)
		ball.IncreaseVelocity();


		//Calculations:

		//Collision place (y axis) ralative to the middle of the paddle
		double relativeCollisionPlaceY = p.yPos + (double)p.height / 2.0 - (b.yPos + (double)b.height / 2.0);

		//Normalized relative collision place
		double normalizedRelativeY = relativeCollisionPlaceY / ((double)p.height / 2.0 + (double)b.height / 2.0);

		//Bounce angle
		double bounceAngle = normalizedRelativeY*MAX_BOUNCE_ANGLE;

		//Checking X axis direction of the ball before collision
		int xDirectionBefore = b.xVel / abs(b.xVel);

		//Set new velocities of the ball
		b.xVel = b.refVel*(-xDirectionBefore)*cos(bounceAngle);
		b.yVel = b.refVel*-sin(bounceAngle);



		//Update last bouncing paddle
		lastBouncingPaddle = playerNumber;
	}
}

//Friend checking collisions function
bool collision(Paddle &p, Ball &b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rectangle A
	leftA = p.xPos;
	rightA = p.xPos + p.width;
	topA = p.yPos;
	bottomA = p.yPos + p.height;

	//Calculate the sides of rectangle B
	leftB = b.xPos;
	rightB = b.xPos + b.width;
	topB = b.yPos;
	bottomB = b.yPos + b.height;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
		return false;
	if (topA >= bottomB)
		return false;
	if (rightA <= leftB)
		return false;
	if (leftA >= rightB)
		return false;

	//If none of the sides from A are outside B
	return true;
}


void checkGoals()
{
	//If a player on the right scored
	if (ball.GetX() + ball.GetWidth() < 0) {

		//Add point to right player (paddle2)
		player2.Goal();

		//New ball direction is through right player
		ball.SetPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2);
		ball.SetInitialReference();
		ball.SetDirection(PI / 4);
		lastBouncingPaddle = 0;	//zeroing; in case when last bouncing paddle would be the first in new throw
	}

	//If a player on the left scored
	if (ball.GetX() > SCREEN_WIDTH) {

		//New ball direction is through right player
		player1.Goal();

		//New ball direction is through left player
		ball.SetPosition(SCREEN_WIDTH * 3 / 4, SCREEN_HEIGHT / 2);
		ball.SetInitialReference();
		ball.SetDirection(3 * PI / 4);
		lastBouncingPaddle = 0;	//zeroing; in case when last bouncing paddle would be the first in new throw
	}
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("Pong Game  1.0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load background of the game
	if (!background.loadFromFile("images/pongGameBackground.png"))
	{
		printf("Failed to load background's image!\n");
		success = false;
	}

	//Load pressSpaceTexture
	if (!pressSpaceTexture.loadFromFile("images/PressSpace.png"))
	{
		printf("Failed to load pressSpaceTexture image!\n");
		success = false;
	}

	//Load productionTexture
	if (!productionTexture.loadFromFile("images/production.png"))
	{
		printf("Failed to load productionTexture image!\n");
		success = false;
	}

	//Open the font
	gFont = TTF_OpenFont("fonts/JosefinSans-Italic.ttf", 50);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	//Load player1's paddle texture
	if (!player1.paddle.LoadTexture("images/paddle3.png"))
	{
		printf("Failed to load player1's paddle image!\n");
		success = false;
	}

	//Load player2's paddle texture
	if (!player2.paddle.LoadTexture("images/paddle3.png"))
	{
		printf("Failed to load player2's paddle image!\n");
		success = false;
	}

	//Load ball's texture
	if (!ball.LoadTexture("images/ball2.png"))
	{
		printf("Failed to load ball's image!\n");
		success = false;
	}

	return success;
}

void close()
{
	//Free textures
	background.free();
	pressSpaceTexture.free();
	winnerTexture.free();
	productionTexture.free();

	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

//#ifdef _DEBUG
int main(int argc, char* args[])
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;


			//Set paddle1's, paddle2's and ball's position
			player1.paddle.SetPosition(10, SCREEN_HEIGHT / 2);
			player2.paddle.SetPosition(SCREEN_WIDTH - player2.paddle.GetWidth() - 10, SCREEN_HEIGHT / 2);
			ball.SetPosition(SCREEN_WIDTH / 4, SCREEN_HEIGHT / 2);

			//Set ball's direction
			ball.SetDirection(PI / 4);

			//Set score text color
			SDL_Color scoreTextColor = { 63,72,204 };
			score.SetTextColor(scoreTextColor);


			//While application is running
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//User requests quit
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Handle input for the paddles
					player1.paddle.HandleEvent(e, player1.playerNumber);
					player2.paddle.HandleEvent(e, player2.playerNumber);

					//Handle a new game press
					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
					{
						matchIsOver = false;
					}


				}




				//Update the time
				float timeFromLastFrame = float(SDL_GetTicks() - lastFrameTime) / 1000.0;
				lastFrameTime = SDL_GetTicks();

				if (!matchIsOver) {

					//Update positions
					player1.paddle.Update(timeFromLastFrame);
					player2.paddle.Update(timeFromLastFrame);
					ball.Update(timeFromLastFrame);

					//Bounce ball from paddles if there is a collision beetwen them
					bounceBall(player1.paddle, player1.playerNumber, ball);
					bounceBall(player2.paddle, player2.playerNumber, ball);

					//Check if there is any goal; if it is handle it
					checkGoals();

					//Update score to show
					score.Update(player1.GetName(), player1.GetPoints(), player2.GetName(), player2.GetPoints());

					//Checking if one of the players has achieved 11 points
					if (player1.GetPoints() >= 11 || player2.GetPoints() >= 11) {

						//Checking who won
						if (player1.GetPoints() > player2.GetPoints()) {
							winnerName = player1.GetName();
						}
						else if (player1.GetPoints() < player2.GetPoints()) {
							winnerName = player2.GetName();
						}

						//Reset each player points
						player1.ResetPoints();
						player2.ResetPoints();

						//Match is over
						matchIsOver = true;
					}
					
				}




				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Render background
				background.render(0, 0);

				if (!matchIsOver) {
					//Render objects
					player1.paddle.Show();
					player2.paddle.Show();
					ball.Show();

					//Render score
					score.Show();
				}
				else {
					//Render pressSpace information
					pressSpaceTexture.render(SCREEN_WIDTH / 2 - pressSpaceTexture.getWidth() / 2, SCREEN_HEIGHT * 3 / 4);

					//When there is a winner (not after 1st match)
					if (winnerName != " ") {
						//Render winner
						SDL_Color winnerTextColor = { 63,72,204 };
						std::string winnerText = winnerName + " wins!";
						winnerTexture.loadFromRenderedText(winnerText.c_str(), winnerTextColor);
						winnerTexture.render(SCREEN_WIDTH / 2 - winnerTexture.getWidth() / 2, SCREEN_HEIGHT / 8);
					}
					//After 1st match
					else {
						//Render version and production
						productionTexture.render(0,0);
					}
				}

				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

//#endif