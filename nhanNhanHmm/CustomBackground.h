#ifndef __CustomBackground__
#define __CustomBackground__

#include "SDLGameObject.h"
class CustomBackground : public SDLGameObject
{
public:
	CustomBackground(const LoaderParams* pParams);
	virtual void draw();
	virtual void clean();
};

#endif