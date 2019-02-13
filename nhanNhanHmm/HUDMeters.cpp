/**
Class that controls the sprite from hud level and push.

@author Vladmir C. Souza
*/

#include "HUDMeters.h"

HUDMeters::HUDMeters(const LoaderParams * pParams) : SDLGameObject(pParams)
{
	m_currentFrame = 0;
}

void HUDMeters::draw()
{
	SDLGameObject::draw();
}

void HUDMeters::clean()
{
	SDLGameObject::clean();
}

void HUDMeters::setWidth(int value)
{
	m_width = value;
}
