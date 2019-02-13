#ifndef __Game__
#define __Game__

#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

#include "TextureManager.h"
#include "GameObject.h"
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

	GameObject* m_go;
	GameObject* m_box;
	GameObject* m_enemy;

	std::vector<GameObject*> m_gameObjects;

	static Game* s_pInstance;

	GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;

#endif
