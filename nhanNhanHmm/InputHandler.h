#ifndef __InputHandler__
#define __InputHandler__

#include <SDL2/SDL.h>
#include <vector>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (s_pInstance == 0)
			s_pInstance = new InputHandler();

		return s_pInstance;
	}

	void update();
	void clean();

	bool getMouseButtonState(int buttonNumber) 
	{
		return m_mouseButtonStates[buttonNumber];
	}

	Vector2D* getMousePosition() 
	{
		return m_mousePosition;
	}

	// keyboard events
	bool isKeyDown(SDL_Scancode key) const;
	
private:
	InputHandler();

	Vector2D* m_mousePosition;

	static InputHandler* s_pInstance;

	// keyboard specific
	const Uint8* m_keystates;

	std::vector<bool> m_mouseButtonStates;

	//functions that handles the mouse events
	void onMouseMove(SDL_Event& event);
	void onMouseButtonDown(SDL_Event& event);
	void onMouseButtonUp(SDL_Event& event);
};
typedef InputHandler TheInputHandler;

#endif
