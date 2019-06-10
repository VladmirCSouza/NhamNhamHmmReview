/**
Class that controls the Main Menu screen.

@author Vladmir C. Souza
*/

#include "MenuState.h"
#include "PlayState.h"
#include "CreditsState.h"
#include "CustomBackground.h"
#include "CustomCursor.h"
#include <iostream>
#include "SoundManager.h"
#include "AlienMainMenu.h"

const std::string MenuState::s_menuID = "MENU";

const std::string BG_ID = "background";
const std::string BTN_PLAY_ID = "playbutton";
const std::string BTN_CRED_ID = "creditsbutton";
const std::string BTN_EXIT_ID = "exitbutton";
const std::string BLUE_ALIEN_ID = "alienBlueMainMenuID";

void MenuState::update()
{
	if (!p_bIsInMainMenu || loading || m_gameObjects.empty())
		return;
    
    for (int i = 0; i < m_gameObjects.size(); i++)
    {
            m_gameObjects[i]->update();
    }
}

void MenuState::render()
{
	if (!loading && !m_gameObjects.empty())
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
            m_gameObjects[i]->draw();
		}
	}
}

bool MenuState::onEnter()
{
	loading = true;
	p_bIsInMainMenu = true;

	TheSoundManager::Instance()->stopMusic();
	TheSoundManager::Instance()->playMusic("bgMenu", -1);

	TheCustomCursor::Instance()->setFrame(0);

	std::cout << "Loading buttons\n";

	if (!TheTextureManager::Instance()->load("assets/backgrounds/mainMenu.jpg", BG_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnPlay.png", BTN_PLAY_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnCredits.png", BTN_CRED_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnExit.png", BTN_EXIT_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/Personas/alienBlueMainMenu.png", BLUE_ALIEN_ID, TheGame::Instance()->getRenderer()))
		return false;
    
    m_gameObjects.push_back(new CustomBackground(0, 0, 1024, 768, BG_ID));
    m_gameObjects.push_back(new MenuButton(386, 250, 64, 64, BTN_PLAY_ID, s_menuToPlay));
    m_gameObjects.push_back(new MenuButton(480, 250, 64, 64, BTN_CRED_ID, s_menuToCredits));
    m_gameObjects.push_back(new MenuButton(574, 250, 64, 64, BTN_EXIT_ID, s_exitFromMenu));
    m_gameObjects.push_back(new AlienMainMenu(448, 640, 64, 64, BLUE_ALIEN_ID));

	loading = false;
	std::cout << "entering MenuState\n";
	return true;
}

bool MenuState::onExit()
{
	p_bIsInMainMenu = false;
	
	TheTextureManager::Instance()->clearFromTextureMap(BG_ID);
	TheTextureManager::Instance()->clearFromTextureMap(BTN_PLAY_ID);
	TheTextureManager::Instance()->clearFromTextureMap(BTN_CRED_ID);
	TheTextureManager::Instance()->clearFromTextureMap(BTN_EXIT_ID);
	TheTextureManager::Instance()->clearFromTextureMap(BLUE_ALIEN_ID);

    for (auto& gameObject : m_gameObjects)
	{
        delete gameObject;
	}

	m_gameObjects.clear();

	std::cout << "exiting MenuState\n";
	return true;
}

void MenuState::s_menuToPlay()
{
	std::cout << "PLAY button Clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}

void MenuState::s_menuToCredits()
{
	std::cout << "CREDITS button Clicked\n";
	TheGame::Instance()->getStateMachine()->changeState(new CreditsState());
}

void MenuState::s_exitFromMenu()
{
	std::cout << "EXIT button Clicked\n";
	TheGame::Instance()->quit();
}
