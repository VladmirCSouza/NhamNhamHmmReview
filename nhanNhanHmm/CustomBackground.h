#pragma once

#include "SDLGameObject.h"
class CustomBackground : public SDLGameObject
{
public:
	CustomBackground(int x, int y, float width, float height, std::string textureID);
    void draw() override;
    void clean() override;
    void update() override;
};
