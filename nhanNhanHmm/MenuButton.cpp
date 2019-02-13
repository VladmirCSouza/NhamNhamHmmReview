/**
Class responsable for all the buttons used on menus, hud and pause.

@author Vladmir C. Souza
*/

#include "MenuButton.h"
#include "InputHandler.h"
#include "SoundManager.h"

MenuButton::MenuButton(const LoaderParams * pParams, void (*callback)()):SDLGameObject(pParams),m_callback(callback)
{
	m_currentFrame = MOUSE_OUT; //start at fram 0
}

void MenuButton::draw()
{
	SDLGameObject::draw(); //use the base class drawing
}

void MenuButton::update()
{
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();

	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		m_currentFrame = MOUSE_OVER;

		if (!m_mouseIsOver)
		{
			TheSoundManager::Instance()->playSound("btnClick", 0);
			m_mouseIsOver = true;
		}
		

		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) && m_bReleased) {
			m_currentFrame = CLICKED;
			m_callback();
			m_bReleased = false;
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT)) {
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
		m_mouseIsOver = false;
	}
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}
