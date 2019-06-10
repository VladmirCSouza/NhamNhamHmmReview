#pragma once

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "TextureManager.h"
#include "SDLGameObject.h"
#include "Enemy.h"
#include "GameStateMachine.h"

class Game
{
public:
	static Game* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new Game();
		return s_pInstance;
	}

	bool init(const char* title, int xpos, int ypos, int height, int width, bool fullscreen);
	void update();
	void render();
	void handleEvents();
	void clean();
	void quit();

	bool running() { return m_bRunning; }

	SDL_Renderer* getRenderer() const { return m_pRenderer; }

	GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

private:
	Game();

	SDL_Window * m_pWindow;
	SDL_Renderer* m_pRenderer;
	
	int m_currentFrame;

	bool m_bRunning;

    SDLGameObject* m_go;
    SDLGameObject* m_box;
    SDLGameObject* m_enemy;

	std::vector<SDLGameObject*> m_gameObjects;

	static Game* s_pInstance;

	GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;
