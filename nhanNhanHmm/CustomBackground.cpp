/**
Class used manage how backgrounds should be draw.

@author Vladmir C. Souza
*/

#include "CustomBackground.h"

CustomBackground::CustomBackground(int x, int y, float width, float height, std::string textureID) :
SDLGameObject( x, y, width, height, textureID)
{
	m_currentFrame = 0;
}

void CustomBackground::update() {
    SDLGameObject::update();
}

void CustomBackground::draw()
{
	SDLGameObject::draw();
}

void CustomBackground::clean()
{
	SDLGameObject::clean();
}
