#ifndef __GameObject__
#define __GameObject__

#include "LoaderParams.h"
#include <SDL2/SDL.h>
#include "TextureManager.h"

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	bool isDead = false;

protected:
	virtual ~GameObject() {}
	GameObject(const LoaderParams* pParams) {}
};

#endif

