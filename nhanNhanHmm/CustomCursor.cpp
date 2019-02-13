#include "CustomCursor.h"
#include "InputHandler.h"

CustomCursor* CustomCursor::s_pInstance = 0;

void CustomCursor::draw()
{
	SDLGameObject::draw();
}

void CustomCursor::update()
{
	handleInput();
}

void CustomCursor::clean()
{
	SDLGameObject::clean();
}

void CustomCursor::setFrame(int frame)
{
	m_currentFrame = frame;
}

void CustomCursor::handleInput()
{
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_position = *vec;
}
