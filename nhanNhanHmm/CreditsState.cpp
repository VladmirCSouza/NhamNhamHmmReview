/**
Class that controls the Credits screen.

@author Vladmir C. Souza
*/

#include "CreditsState.h"
#include "MenuState.h"
#include "CustomBackground.h"

const std::string CreditsState::s_creditsID = "CREDITS";

void CreditsState::update()
{
	if (!p_bIsInCredits || loading)
		return;
	
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i] != nullptr)
			m_gameObjects[i]->update();
	}
}

void CreditsState::render()
{
	if (!p_bIsInCredits || loading)
		return;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool CreditsState::onEnter()
{
	p_bIsInCredits = true;
	loading = true;

	if (!TheTextureManager::Instance()->load("assets/backgrounds/credits.jpg", "background", TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnMainMenu.png", "btnMainMenu", TheGame::Instance()->getRenderer()))
		return false;

	GameObject* background = new CustomBackground(new LoaderParams(0, 0, 1024, 768, "background"));
	GameObject* buttonMainMenu = new MenuButton(new LoaderParams(10, 10, 64, 64, "btnMainMenu"),s_creditsToMenu);

	m_gameObjects.push_back(background);
	m_gameObjects.push_back(buttonMainMenu);


	std::cout << "Loading buttons\n";

	loading = false;
	return true;
}

bool CreditsState::onExit()
{
	p_bIsInCredits = false;

	TheTextureManager::Instance()->clearFromTextureMap("background");
	TheTextureManager::Instance()->clearFromTextureMap("btnMainMenu");

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		m_gameObjects[i] = nullptr;
	}

	m_gameObjects.clear();

	return false;
}

void CreditsState::s_creditsToMenu()
{
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}
