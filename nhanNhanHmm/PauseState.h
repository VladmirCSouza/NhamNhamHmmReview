#ifndef __PauseState__
#define __PauseState__

#include "GameState.h"
#include "GameObject.h"
#include "Game.h"
#include "MenuButton.h"
#include <vector>
class PauseState :
	public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_pauseID; }

private:

	static const std::string s_pauseID;

	std::vector<GameObject*> m_gameObjects;

	static void s_pauseToMain();
	static void s_resumeToPlay();

	bool p_bIsInPause;
	bool loading;
};

#endif