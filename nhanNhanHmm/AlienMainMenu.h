#ifndef __AlienMainMenu__
#define __AlienMainMenu__

#include "SDLGameObject.h"
class AlienMainMenu :
	public SDLGameObject
{
public:
	AlienMainMenu(int x, int y, float width, float height, std::string textureID);
	virtual void draw();
	virtual void update();
    virtual void clean();
    
    ~AlienMainMenu();

private:

	enum alienState
	{
		SLEEPING = 0,
		MOUSE_MOVE = 1
	};

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

	float prevMouseX;
	float prevMouseY;

	int delay = 0;
};

#endif
