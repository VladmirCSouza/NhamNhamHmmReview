#ifndef __CustomBackground__
#define __CustomBackground__

#include "SDLGameObject.h"
class CustomBackground : public SDLGameObject
{
public:
	CustomBackground(int x, int y, float width, float height, std::string textureID);
    void draw() override;
    void clean() override;
    void update() override;
};

#endif
