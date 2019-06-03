#include "PhysicalObject.h"



PhysicalObject::PhysicalObject()
{
	xPos = 0;
	yPos = 0;
	//texture = LTexture();
	width = 0;
	height = 0;
}


PhysicalObject::~PhysicalObject()
{
	texture.free();
}

bool PhysicalObject::LoadTexture(std::string path)
{
	//Load a texture
	if (!texture.loadFromFile(path.c_str())) {
		printf("Failed to load the PhysicalObject's texture");
		return false;
	}
	else
	{
		//If loaded set width and height according to texture dimensions
		width = texture.getWidth();
		height = texture.getHeight();
	}
	return true;
}

void PhysicalObject::SetPosition(float _xPos, float _yPos)
{
	xPos = _xPos;
	yPos = _yPos;
}

void PhysicalObject::Show()
{
	texture.render((int)xPos, (int)yPos);
}


int PhysicalObject::GetWidth()
{
	return width;
}


int PhysicalObject::GetHeight()
{
	return height;
}


int PhysicalObject::GetX()
{
	return xPos;
}


int PhysicalObject::GetY()
{
	return yPos;
}