#include "AlienMainMenu.h"
#include "InputHandler.h"
#include "Vector2D.h"

AlienMainMenu::AlienMainMenu(int x, int y, float width, float height, std::string textureID) :
SDLGameObject( x, y, width, height,textureID)
{
	m_currentFrame = 0;
	m_currentRow = 1;

	Vector2D* mousePos = TheInputHandler::Instance()->getMousePosition();

	prevMouseX = mousePos->getX();
	prevMouseY = mousePos->getX();
}

void AlienMainMenu::draw()
{
	SDLGameObject::draw();
}

void AlienMainMenu::update()
{
	SDLGameObject::update();

	Vector2D* mousePos = TheInputHandler::Instance()->getMousePosition();

	//If mouse parado
	if (mousePos->getX() == prevMouseX && mousePos->getX() == prevMouseY) {
		delay++;
		if ((delay / 4) == 4) {
			m_currentFrame = 0;
			m_currentRow = 1;
		}
	}
	else {
		delay = 0;

		prevMouseX = mousePos->getX();
		prevMouseY = mousePos->getX();
		m_currentRow = 2;
		changeIdleEyes(mousePos);
	}
}

void AlienMainMenu::clean()
{
	SDLGameObject::clean();
}

AlienMainMenu::~AlienMainMenu()
{
}

void AlienMainMenu::changeIdleEyes(Vector2D * mousePos)
{
	//ALIEN LOOKING UP LEFT
	if (mousePos->getX() <= m_position.getX()
		&& mousePos->getY() < m_position.getY()) {
		m_currentFrame = EYE_UP_LEFT;
		return;
	}
	//ALIEN LOOKING UP
	if (mousePos->getX() >= m_position.getX()
		&& mousePos->getX() <= (m_position.getX() + m_width)
		&& mousePos->getY() <= m_position.getY())
	{
		m_currentFrame = EYE_UP;
		return;
	}
	//ALIEN LOOKING UP RIGHT
	if (mousePos->getX() >= (m_position.getX() + m_width)
		&& mousePos->getY() <= m_position.getY())
	{
		m_currentFrame = EYE_UP_RIGHT;
		return;
	}
	//ALIEN LOOKING RIGHT
	if (mousePos->getX() >= (m_position.getX() + m_width)
		&& mousePos->getY() >= m_position.getY()
		&& mousePos->getY() <= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_RIGHT;
		return;
	}
	//ALIEN LOOKING RIGHT BOTTOM
	if (mousePos->getX() >= (m_position.getX() + m_width)
		&& mousePos->getY() >= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_BOTTOM_RIGHT;
		return;
	}
	//ALIEN LOOKING BOTTOM
	if (mousePos->getX() >= m_position.getX()
		&& mousePos->getX() <= (m_position.getX() + m_width)
		&& mousePos->getY() >= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_BOTTOM;
		return;
	}
	//ALIEN LOOKING BOTTOM LEFT
	if (mousePos->getX() <= m_position.getX()
		&& mousePos->getY() >= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_BOTTOM_LEFT;
		return;
	}
	//ALIEN LOOKING LEFT
	if (mousePos->getX() <= m_position.getX()
		&& mousePos->getY() >= m_position.getY()
		&& mousePos->getY() <= (m_position.getY() + m_height)) {
		m_currentFrame = EYE_LEFT;
	}
}

void AlienMainMenu::eyeDirection(eye_direction direction)
{
	m_currentFrame = direction;
}
