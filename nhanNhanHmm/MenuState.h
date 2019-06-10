#pragma once

#include "GameState.h"
#include "SDLGameObject.h"
#include "Game.h"
#include "MenuButton.h"
#include <vector>

class MenuState : public GameState
{
public:
    void update() override;
    void render() override;
	bool onEnter() override;
    bool onExit() override;

	std::string getStateID() const override { return s_menuID; }

private:
	static const std::string s_menuID;

	std::vector<SDLGameObject*> m_gameObjects;
	
	//callback functions for menu items
	static void s_menuToPlay();
	static void s_menuToCredits();
	static void s_exitFromMenu();

	bool p_bIsInMainMenu;
	bool loading;
};
