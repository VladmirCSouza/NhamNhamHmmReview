/**
Class that controls the Pause screen.

@author Vladmir C. Souza
*/

#include "PauseState.h"
#include "MenuState.h"
#include "CustomCursor.h"
#include "CustomBackground.h"

const std::string PauseState::s_pauseID = "PAUSE";

const std::string BG_PAUSE_ID = "bgPause";
const std::string BTN_MAIN_MENU_ID = "mainMenu";
const std::string BTN_RESUME_ID = "resumeBUtton";

void PauseState::update()
{
	if (!p_bIsInPause || loading)
		return;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		if (m_gameObjects[i] != nullptr)
			m_gameObjects[i]->update();
	}
}

void PauseState::render()
{
	if (!p_bIsInPause || loading)
		return;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->draw();
	}
}

bool PauseState::onEnter()
{
	loading = true;
	m_gameObjects.clear();

	p_bIsInPause = true;

	TheCustomCursor::Instance()->setFrame(0);

	std::cout << "Loading buttons\n";

	if (!TheTextureManager::Instance()->load("assets/backgrounds/pause.jpg", BG_PAUSE_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnPlay.png", BTN_RESUME_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnMainMenu.png", BTN_MAIN_MENU_ID, TheGame::Instance()->getRenderer()))
		return false;

	GameObject* bgPause = new CustomBackground(new LoaderParams(0, 0, 1024, 768, BG_PAUSE_ID));
	GameObject* buttonResume = new MenuButton(new LoaderParams(433, 120, 64, 64, BTN_RESUME_ID), s_resumeToPlay);
	GameObject* buttonMainMenu = new MenuButton(new LoaderParams(527, 120, 64, 64, BTN_MAIN_MENU_ID), s_pauseToMain);

	m_gameObjects.push_back(bgPause);
	m_gameObjects.push_back(buttonResume);
	m_gameObjects.push_back(buttonMainMenu);

	std::cout << "entering PauseState\n";

	loading = false;
	return true;
}

bool PauseState::onExit()
{
	p_bIsInPause = false;

	TheTextureManager::Instance()->clearFromTextureMap(BG_PAUSE_ID);
	TheTextureManager::Instance()->clearFromTextureMap(BTN_RESUME_ID);
	TheTextureManager::Instance()->clearFromTextureMap(BTN_MAIN_MENU_ID);

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
		m_gameObjects[i]->clean();
		m_gameObjects[i] = nullptr;
	}

	m_gameObjects.clear();

	std::cout << "exiting PauseState\n";
	return true;
}

void PauseState::s_pauseToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void PauseState::s_resumeToPlay()
{
	TheGame::Instance()->getStateMachine()->popState();
}
