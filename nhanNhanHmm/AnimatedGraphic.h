#pragma once

#include "SDLGameObject.h"
class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(int x, int y, float width, float height, std::string textureID, int animSpeed, int numFrames);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_animSpeed;
	int m_numFrames;
};
