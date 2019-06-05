#ifndef __SDLGameObject__
#define __SDLGameObject__

#include "GameObject.h"
#include "Vector2D.h"

class SDLGameObject : GameObject
{
public:
	SDLGameObject(int x, int y, float width, float height, std::string textureID);
	virtual void draw();
	virtual void update();
	virtual void clean();

	void setWidth(int value);

protected:
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	float m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	std::string m_textureID;
};

#endif
