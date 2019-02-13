/**
Class used manage how backgrounds should be draw.

@author Vladmir C. Souza
*/

#include "CustomBackground.h"

CustomBackground::CustomBackground(const LoaderParams * pParams) :SDLGameObject(pParams)
{
	m_currentFrame = 0;
}

void CustomBackground::draw()
{
	SDLGameObject::draw();
}

void CustomBackground::clean()
{
	SDLGameObject::clean();
}
