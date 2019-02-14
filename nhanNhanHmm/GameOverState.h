#ifndef __GameOverState__
#define __GameOverState__

#include "GameState.h"
#include "SDLGameObject.h"
#include "Game.h"
#include "MenuButton.h"
#include <vector>

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_gameOverID; }

private:
	static const std::string s_gameOverID;

	std::vector<SDLGameObject> m_gameObjects;

	static void s_gameOverToMain();
	static void s_restartPlay();

	bool p_bIsInGameOverState;
	bool loading = false;
};

#endif
