#ifndef __CustomCursor__
#define __CustomCursor__

#include "SDLGameObject.h"
#include "Game.h"

class CustomCursor : public SDLGameObject
{
public:

	static CustomCursor* Instance() {
		if (s_pInstance == 0) {
            if (!TheTextureManager::Instance()->load("assets/cursor/cursor.png", "customcursor", TheGame::Instance()->getRenderer())) {
                //return NULL;
            }
			s_pInstance = new CustomCursor(new LoaderParams(0, 0, 20, 27, "customcursor"));
			s_pInstance->m_currentFrame = 0;
		}

		return s_pInstance;
	}

	//CustomCursor(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void setFrame(int frame);

private:
	CustomCursor(const LoaderParams* pParams) :SDLGameObject(pParams) {};

	void handleInput();

	static CustomCursor* s_pInstance;
};

typedef CustomCursor TheCustomCursor;

#endif
