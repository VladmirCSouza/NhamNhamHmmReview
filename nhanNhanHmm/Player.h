#pragma once

#include "SDLGameObject.h"
class Player : public SDLGameObject
{
public:
	Player(int x, int y, float width, float height, std::string textureID);

	virtual void draw();
	virtual void update();
	virtual void clean();
};
