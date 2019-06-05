#include "Player.h"

Player::Player(int x, int y, float width, float height, std::string textureID) :
SDLGameObject( x, y, width, height, textureID)
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
