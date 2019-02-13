#ifndef __HUDMeters__
#define __HUDMeters__

#include "SDLGameObject.h"
class HUDMeters : public SDLGameObject
{
public:
	HUDMeters(const LoaderParams* pParams);
	virtual void draw();
	virtual void clean();

	void setWidth(int value);
};

#endif