#ifndef __PlayState__
#define __PlayState__

#include "GameState.h"
#include "SDLGameObject.h"
#include "Game.h"
#include "MenuButton.h"
#include <vector>
#include <map>
#include "Alien.h"
#include "HUDMeters.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();

	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return s_playID; }

	Alien* m_aliensType01[10][14];
	Alien* m_aliensType02[10][14];
	Alien* m_aliensType03[10][14];
	Alien* m_aliensType04[10][14];

	void updateAliensAccordingToMap();
	void changeAlienState(int row, int col, int alienType, alienState newState);

private:

	int currAlienRow = -1;
	int currAlienCol = -1;
	
	void findAdjacents(int row, int col);

	bool m_rightBtnMouseRelease = true;

	static const std::string s_playID;

	std::vector<SDLGameObject> m_gameObjects;

	bool mouseOver(Vector2D* mousePos, int targetPosX, int targetPosY);

	//push controll
	int timerDelay = 1000;
	int timer;
	float seconds  = 1.0;
	float pushDelay = 10;

	//scoreControl
	float points = 0;
	int level = 10;
	int comboMult = 0;

	void pushControl();
	void pushMatrix();

	SDLGameObject* hudLevelMeter;
	SDLGameObject* hudPushMeter;

	bool p_bIsInPlayState;
	bool loading = false;

	int p_currentSelectionType = 0;
	static void s_playToPause();
};

#endif
