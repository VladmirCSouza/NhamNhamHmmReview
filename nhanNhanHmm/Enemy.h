#pragma once

#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy(int x, int y, float width, float height, std::string textureID);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	void handleInput();
};
