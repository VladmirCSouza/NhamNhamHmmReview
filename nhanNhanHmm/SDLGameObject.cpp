/**
Class that controls all the objects of the game.

@author Vladmir C. Souza
*/

#include "SDLGameObject.h"
#include "Game.h"

SDLGameObject::SDLGameObject(int x, int y, float width, float height, std::string textureID):
m_position(x,y),m_velocity(0,0),m_acceleration(0,0)
{
	m_width = width;
	m_height = height;
	m_textureID = textureID;

	m_currentRow = 1;
	m_currentFrame = 1;
}

void SDLGameObject::draw()
{
	TheTextureManager::Instance()->drawframe(m_textureID, (int)m_position.getX(), (int)m_position.getY(), m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
}

void SDLGameObject::update()
{
	/*m_velocity += m_acceleration;
	m_position += m_velocity;*/
}

void SDLGameObject::clean()
{
    delete this;
}

void SDLGameObject::setWidth(int value)
{
	m_width = value;
}
