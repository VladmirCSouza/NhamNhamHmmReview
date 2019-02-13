#include "Player.h"

Player::Player(const LoaderParams * pParams) : SDLGameObject(pParams)
{
	m_currentFrame = 0;
}

void Player::draw()
{
	SDLGameObject::draw(); //use the base class drawing
}

void Player::update()
{
}

void Player::clean()
{
	SDLGameObject::clean();
}
