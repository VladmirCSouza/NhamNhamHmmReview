#include "GameStateMachine.h"
#include <iostream>

void GameStateMachine::pushState(GameState * pState)
{
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

void GameStateMachine::changeState(GameState * pState)
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->getStateID() == pState->getStateID())
			return;

		m_gameStates.back()->onExit();
		m_gameStates.pop_back();
	}

	// initialise it
	pState->onEnter();

	// push back our new state
	m_gameStates.push_back(pState);
}

void GameStateMachine::popState()
{
	if (!m_gameStates.empty()) 
	{
		if (m_gameStates.back()->onExit())
		{
			delete m_gameStates.back();
			m_gameStates.pop_back();
		}
	}
}

void GameStateMachine::update()
{
	//std::cout << "UPDATE: " << m_gameStates.size() << "\n";
	if (!m_gameStates.empty())
		m_gameStates.back()->update();
}

void GameStateMachine::render()
{
	if (!m_gameStates.empty())
		m_gameStates.back()->render();
}
