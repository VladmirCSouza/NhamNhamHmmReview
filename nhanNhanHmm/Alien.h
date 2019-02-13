#ifndef __Alien__
#define __Alien__

#include "SDLGameObject.h"

enum alienState
{
	IDLE = 1,
	MOUSE_OVER = 2,
	MOUSE_OUT = 3,
	DYING = 4
};

enum alienType
{
	BLUE = 1,
	GREEN = 2,
	ORANGE = 3,
	RED = 4
};

class Alien :
	public SDLGameObject
{
public:

	Alien(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
		
	void onStateUpdate();
	void onStateChange(alienState newState);
	alienState m_currtState;
	alienState m_prevState;

	bool adjacentMatch = false;
	int getCurrentState() { return m_currtState; }
	int getPrevState() { return m_prevState; }
	void setNewState(alienState newState) { onStateChange(newState); }
	
	void setActive();
	bool getActive() { return isActive; }
	void setInactive();

private:
	~Alien();

	bool isActive = false;

	int frameCountAnimation = 0;

	enum eye_direction
	{
		EYE_UP = 0,
		EYE_UP_RIGHT = 1,
		EYE_RIGHT = 2,
		EYE_BOTTOM_RIGHT = 3,
		EYE_BOTTOM = 4,
		EYE_BOTTOM_LEFT = 5,
		EYE_LEFT = 6,
		EYE_UP_LEFT = 7
	};

	void changeIdleEyes(Vector2D* mousePos);
	void eyeDirection(eye_direction direction);
};

#endif