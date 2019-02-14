/**
Class that controls the Game Over screen.

@author Vladmir C. Souza
*/

#include "GameOverState.h"
#include "PlayState.h"
#include "MenuState.h"
#include "CustomCursor.h"
#include "CustomBackground.h"
#include "SoundManager.h"
#include <iostream>

const std::string GameOverState::s_gameOverID = "GAMEOVER";

const std::string BG_ID = "background";
const std::string TTL_GAME_OVER_ID = "gameOverText";
const std::string BTN_RESTART_ID = "restartbutton";
const std::string BTN_MAIN_MENU_ID = "mainMenubutton";

void GameOverState::update()
{
	if (!p_bIsInGameOverState || loading)
		return;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
//        if (m_gameObjects[i] != nullptr)
            m_gameObjects[i].update();
	}
}

void GameOverState::render()
{
	if (!p_bIsInGameOverState || loading)
		return;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
        m_gameObjects[i].draw();
	}
}

bool GameOverState::onEnter()
{
	loading = true;
	m_gameObjects.clear();

	TheSoundManager::Instance()->load("assets/audio/gameOver.wav", "gameOver", SOUND_SFX);

	p_bIsInGameOverState = true;

	std::cout << "Loading GameOverState\n";

	TheCustomCursor::Instance()->setFrame(0);


	if (!TheTextureManager::Instance()->load("assets/backgrounds/gameOver.jpg", BG_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnRestart.png", BTN_RESTART_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnMainMenu.png", BTN_MAIN_MENU_ID, TheGame::Instance()->getRenderer()))
		return false;

//    m_gameObjects.push_back(CustomBackground(0, 0, 1024, 768, BG_ID));
//    m_gameObjects.push_back(MenuButton(433, 140, 64, 64, BTN_RESTART_ID, s_restartPlay));
//    m_gameObjects.push_back(MenuButton(527, 140, 64, 64, BTN_MAIN_MENU_ID, s_gameOverToMain));

	std::cout << "Entering GameOverState\n";
	
	TheSoundManager::Instance()->stopMusic();
	TheSoundManager::Instance()->playSound("gameOver", 0);

	loading = false;
	return true;
}

bool GameOverState::onExit()
{
	p_bIsInGameOverState = false;

	TheTextureManager::Instance()->clearFromTextureMap(BG_ID);
	TheTextureManager::Instance()->clearFromTextureMap(BTN_RESTART_ID);
	TheTextureManager::Instance()->clearFromTextureMap(BTN_MAIN_MENU_ID);
	
	for (int i = 0; i < m_gameObjects.size(); i++)
	{
        m_gameObjects[i].clean();
//        m_gameObjects[i] = nullptr;
	}

	m_gameObjects.clear();

	std::cout << "exiting GameOverState\n";
	return true;
}

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(new MenuState());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState(new PlayState());
}
