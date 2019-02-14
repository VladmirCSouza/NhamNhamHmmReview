#ifndef __GameObject__
#define __GameObject__

#include <SDL2/SDL.h>
#include "TextureManager.h"

class GameObject
{
public:
    //GameObject(int x, int y, float width, float height, std::string textureID) {}
    virtual ~GameObject() = default;
    
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	bool isDead = false;
    

};

#endif

