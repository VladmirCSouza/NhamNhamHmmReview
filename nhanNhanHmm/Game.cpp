/**
THe main class off the game, manage and control all the stages from the game.

@author Vladmir C. Souza
*/


#include "Game.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "CustomCursor.h"
#include "SoundManager.h"

Game* Game::s_pInstance = 0;

/**
	Initialize the SDL framework
*/
bool Game::init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen) {
	
	int flags = 0;

	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;

	//try to initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL init success\n";

		//init the window
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, height, width, flags);

		if (m_pWindow != 0) {
			std::cout << "window creation success\n";
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) {
				std::cout << "renderer creation success\n";
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
			}
			else {
				std::cout << "renderer init fail\n";
				return false;
			}
		}
		else {
			std::cout << "window init fail\n";
			return false;
		}
	}
	else {
		std::cout << "SDL init fail\n";
		return false;
	}

	std::cout << "init success\n";
	m_bRunning = true;


    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());
	
//    m_gameObjects.push_back(TheCustomCursor::Instance());

//    TheSoundManager::Instance()->load("assets/audio/bgMenu.wav", "bgMenu", SOUND_MUSIC);
//    TheSoundManager::Instance()->load("assets/audio/btnClick.wav", "btnClick", SOUND_SFX);

//    TheSoundManager::Instance()->playMusic("bgMenu", -1);

	return true;
}

/**
Game's main loop
*/
void Game::update() {
	m_pGameStateMachine->update();

    for (std::vector<SDLGameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
        m_gameObjects[i]->update();
}

/**
	Clears the renderer and then renders again with the clear color
*/
void Game::render() {
	SDL_RenderClear(m_pRenderer);

	m_pGameStateMachine->render();

    for (std::vector<SDLGameObject*>::size_type i = 0; i != m_gameObjects.size(); i++)
        m_gameObjects[i]->draw();

	SDL_RenderPresent(m_pRenderer);
}

/**
Function that update all the inputs from the game
*/
void Game::handleEvents() {
	TheInputHandler::Instance()->update();
}

/**
Clean up the memory. Destroy the window, the render and also call the SDL_Quit
*/
void Game::clean() {
	std::cout << "cleaning the game\n";
	
	TheInputHandler::Instance()->clean();
    
    delete m_pGameStateMachine;
    m_pGameStateMachine = nullptr;
    
    for(auto& gameObject : m_gameObjects)
        gameObject->clean();

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void Game::quit()
{
	m_bRunning = false;
}

Game::Game() {
	m_pRenderer = 0;
	m_pWindow = 0;
}
