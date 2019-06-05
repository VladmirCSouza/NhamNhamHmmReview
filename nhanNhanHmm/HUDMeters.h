#ifndef __HUDMeters__
#define __HUDMeters__

#include "SDLGameObject.h"
class HUDMeters : public SDLGameObject
{
public:
    HUDMeters(int x, int y, float width, float height, std::string textureID);
	virtual void draw();
	virtual void clean();

	void setWidth(int value);
};

#endif
