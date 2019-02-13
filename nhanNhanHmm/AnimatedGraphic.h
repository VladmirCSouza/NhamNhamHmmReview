#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include "SDLGameObject.h"
class AnimatedGraphic : public SDLGameObject
{
public:
	AnimatedGraphic(const LoaderParams* pParams, int animSpeed, int numFrames);
	virtual void draw();
	virtual void update();
	virtual void clean();

private:
	int m_animSpeed;
	int m_numFrames;
};

#endif