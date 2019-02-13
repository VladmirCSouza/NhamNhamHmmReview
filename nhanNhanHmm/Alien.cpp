/**
Class that manage the Alien behaviour/states
This class is mainly controled on PlayState.cpp

@author Vladmir C. Souza
*/


#include "Alien.h"
#include "InputHandler.h"
#include "Game.h"

Alien::Alien(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_currtState = IDLE;
	m_prevState = m_currtState;
	m_currentFrame = EYE_UP;
	m_currentRow = IDLE;
}

void Alien::setActive()
{
	m_currtState = IDLE;
	m_prevState = m_currtState;
	m_currentFrame = EYE_UP;
	m_currentRow = IDLE;
	isActive = true;
}

void Alien::setInactive()
{
	isActive = false;
}

Alien::~Alien()
{
}

void Alien::draw()
{
	if (!isActive)
		return;
	SDLGameObject::draw();
}

void Alien::update()
{
	if (!isActive)
		return;

	onStateUpdate();
}

void Alien::clean()
{
	SDLGameObject::clean();
}

//Update the alien states
void Alien::onStateUpdate()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	switch (m_currtState)
	{
	case IDLE:
		changeIdleEyes(pMousePos);
		break;
	case MOUSE_OVER:
		m_currentFrame = int(((SDL_GetTicks() / (200 / 1)) % 2));
		break;
	case MOUSE_OUT:
		frameCountAnimation++;
		m_currentFrame = int(frameCountAnimation / 5);
		if (m_currentFrame > 2)
			onStateChange(IDLE);
		break;
	case DYING:
		frameCountAnimation++;
		m_currentFrame = int(frameCountAnimation / 3);
		if (m_currentFrame == 5)
			isActive = false;
		break;
	default:
		break;
	}
}

void Alien::onStateChange(alienState newState)
{
	if (newState == m_currtState)
		return;

	switch (newState)
	{
	case IDLE:
		m_currentFrame = EYE_UP;
		m_currentRow = IDLE;
		break;
	case MOUSE_OVER:
		m_currentFrame = 0;
		frameCountAnimation = 0;
		m_currentRow = MOUSE_OVER;
		break;
	case MOUSE_OUT:
		m_currentFrame = 0;
		frameCountAnimation = 0;
		m_currentRow = MOUSE_OUT;
		break;
	case DYING:
		m_currentFrame = 0;
		frameCountAnimation = 0;
		m_currentRow = DYING;
		break;
	default:
		break;
	}

	m_prevState = m_currtState;
	m_currtState = newState;
}

void Alien::changeIdleEyes(Vector2D * mousePos)
{
	//ALIEN LOOKING UP LEFT
	if (mousePos->getX() <= m_position.getX()
		&& mousePos->getY() < m_position.getY()) {
		m_currentFrame = EYE_UP_LEFT;
		return;
	}
	//ALIEN LOOKING UP
	if (mousePos->getX() >= m_position.getX()
		&& mousePos->getX() <= (m_position.getX() + m_width)
		&& mousePos->getY() <= m_position.getY())
	{
		m_currentFrame = EYE_UP;
		return;
	}
	//ALIEN LOOKING UP RIGHT
	if (mousePos->getX() >= (m_position.getX() + m_width)
		&& mousePos->getY() <= m_position.getY())
	{
		m_currentFrame = EYE_UP_RIGHT;
		return;
	}
	//ALIEN LOOKING RIGHT
	if (mousePos->getX() >= (m_position.getX() + m_width)
		&& mousePos->getY() >= m_position.getY()
		&& mousePos->getY() <= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_RIGHT;
		return;
	}
	//ALIEN LOOKING RIGHT BOTTOM
	if (mousePos->getX() >= (m_position.getX() + m_width)
		&& mousePos->getY() >= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_BOTTOM_RIGHT;
		return;
	}
	//ALIEN LOOKING BOTTOM
	if (mousePos->getX() >= m_position.getX()
		&& mousePos->getX() <= (m_position.getX() + m_width)
		&& mousePos->getY() >= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_BOTTOM;
		return;
	}
	//ALIEN LOOKING BOTTOM LEFT
	if (mousePos->getX() <= m_position.getX()
		&& mousePos->getY() >= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_BOTTOM_LEFT;
		return;
	}
	//ALIEN LOOKING LEFT
	if (mousePos->getX() <= m_position.getX()
		&& mousePos->getY() >= m_position.getY()
		&& mousePos->getY() <= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_LEFT;
	}
}

void Alien::eyeDirection(eye_direction direction)
{
	m_currentFrame = direction;
}
