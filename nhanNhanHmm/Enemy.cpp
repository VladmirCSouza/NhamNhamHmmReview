#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams):SDLGameObject(pParams)
{
	m_currentFrame = 0;
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	handleInput();
}

void Enemy::clean()
{
	SDLGameObject::clean();
}

void Enemy::handleInput()
{
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_position = *vec;
}
