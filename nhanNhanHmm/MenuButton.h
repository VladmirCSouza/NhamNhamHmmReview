#pragma once

#include "SDLGameObject.h"
class MenuButton : public SDLGameObject
{
public:
	MenuButton(int x, int y, float width, float height, std::string textureID, void (*callback)());

	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	enum button_state
	{
		MOUSE_OUT = 0,
		MOUSE_OVER = 1,
		CLICKED = 2
	};

	void(*m_callback)();

	bool m_bReleased;
	bool m_mouseIsOver = false;
};
