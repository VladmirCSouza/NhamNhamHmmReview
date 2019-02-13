/**
Class used to manage NPCs that are just animated and don't move.

@author Vladmir C. Souza
*/

#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic(const LoaderParams * pParams, int animSpeed, int numFrames) :SDLGameObject(pParams), m_animSpeed(animSpeed), m_numFrames(numFrames)
{
}

void AnimatedGraphic::draw()
{
	SDLGameObject::draw();
}

void AnimatedGraphic::update()
{
	m_currentFrame = int(((SDL_GetTicks() / (200 / m_animSpeed)) % m_numFrames));

	if (m_currentFrame >= m_numFrames)
		m_currentFrame = 0;
}

void AnimatedGraphic::clean()
{
	SDLGameObject::clean();
}
