#include "CustomCursor.h"
#include "InputHandler.h"

CustomCursor* CustomCursor::s_pInstance = 0;
int CustomCursor::refCounter = 0;

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
    removeRef();
    if ((0==refCounter) && (s_pInstance != nullptr)) {
        delete s_pInstance;
        s_pInstance = nullptr;
    }
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
