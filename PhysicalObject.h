#pragma once

#include "LTexture.h"

class PhysicalObject
{
public:
	PhysicalObject();
	~PhysicalObject();

	//Load a texture from file and set width and height
	bool LoadTexture(std::string path);

	//Set a position
	void SetPosition(float _xPos, float _yPos);

	//Show an object on the screen
	void Show();

	//Return a width of the object
	int GetWidth();

	//Return a height of the object
	int GetHeight();

	//Return x position
	int GetX();

	//Return y position
	int GetY();

protected:
	//Position
	float xPos;
	float yPos;

	//Dimensions
	int width;
	int height;

	//Texture
	LTexture texture;
};

