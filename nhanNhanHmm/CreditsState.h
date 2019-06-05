#ifndef __CreditsState__
#define __CreditsState__

#include "GameState.h"
#include "SDLGameObject.h"
#include "Game.h"
#include "MenuButton.h"
#include <vector>

class CreditsState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_creditsID; }

private:
	static const std::string s_creditsID;

	std::vector<SDLGameObject> m_gameObjects;

	//callback functions for menu items
	static void s_creditsToMenu();

	bool p_bIsInCredits;
	bool loading = false;
};

#endif
