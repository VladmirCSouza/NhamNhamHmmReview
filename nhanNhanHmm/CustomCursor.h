#pragma once

#include "SDLGameObject.h"
#include "Game.h"

class CustomCursor : public SDLGameObject
{
public:

	static CustomCursor* Instance() {
		if (s_pInstance == 0) {
            if (!TheTextureManager::Instance()->load("assets/cursor/cursor.png", "customcursor", TheGame::Instance()->getRenderer())) {
                return NULL;
            }
			s_pInstance = new CustomCursor(0, 0, 20, 27, "customcursor");
			s_pInstance->m_currentFrame = 0;
            refCounter = 0;
		}
        addRef();

		return s_pInstance;
	}
    
    

	void draw() override;
    void update() override;
	void clean() override;

	void setFrame(int frame);

private:
    CustomCursor(int x, int y, float width, float height, std::string textureID) :
                                        SDLGameObject( x, y, width, height, textureID) {};
    ~CustomCursor(){}; // don't allow users to apply delete on objects. as we will force users to call clean method.
    
    static void addRef() { ++refCounter; };
    static void removeRef() { --refCounter; };
    
	void handleInput();

	static CustomCursor* s_pInstance;
    static int refCounter;
};

typedef CustomCursor TheCustomCursor;
