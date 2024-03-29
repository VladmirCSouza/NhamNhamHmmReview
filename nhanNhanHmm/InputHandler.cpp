/**
Class responsable to manage and control the inputs of the game.

@author Vladmir C. Souza
*/

#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

bool InputHandler::isKeyDown(SDL_Scancode key) const
{
	if (m_keystates != 0)
	{
		if (m_keystates[key] == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

InputHandler::InputHandler() : m_mousePosition(new Vector2D(0,0))
{
	for (int i = 0; i < 3; i++)
	{
		m_mouseButtonStates.push_back(false);
	}
}

void InputHandler::update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->quit();
			break;
		case SDL_MOUSEBUTTONDOWN:
			onMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			onMouseButtonUp(event);
			break;
		case SDL_MOUSEMOTION:
			onMouseMove(event);
			break;
		default:
			break;
		}
	}
}

void InputHandler::clean()
{
    s_pInstance = nullptr;
    delete s_pInstance;
}

void InputHandler::onMouseMove(SDL_Event & event)
{
	m_mousePosition->setX(event.motion.x);
	m_mousePosition->setY(event.motion.y);
}

void InputHandler::onMouseButtonDown(SDL_Event & event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
		m_mouseButtonStates[LEFT] = true;

	if (event.button.button == SDL_BUTTON_MIDDLE)
		m_mouseButtonStates[MIDDLE] = true;

	if (event.button.button == SDL_BUTTON_RIGHT)
		m_mouseButtonStates[RIGHT] = true;
}

void InputHandler::onMouseButtonUp(SDL_Event & event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
		m_mouseButtonStates[LEFT] = false;

	if (event.button.button == SDL_BUTTON_MIDDLE)
		m_mouseButtonStates[MIDDLE] = false;

	if (event.button.button == SDL_BUTTON_RIGHT)
		m_mouseButtonStates[RIGHT] = false;
}
