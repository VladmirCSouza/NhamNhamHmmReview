/**
Class that controls the In Game screen.

@author Vladmir C. Souza
*/

#include "PlayState.h"
#include <iostream>
#include "InputHandler.h"
#include "PauseState.h"
#include "GameOverState.h"
#include "CustomBackground.h"
#include "CustomCursor.h"
#include "Alien.h"
#include "AnimatedGraphic.h"
#include "AlienMap.h"
#include "SoundManager.h"
#include <algorithm>

const std::string PlayState::s_playID = "PLAY";

#pragma region Texutre IDs
const std::string BG_ID = "background";
const std::string BTN_PUSH_ID = "push";
const std::string BTN_PAUSE_ID = "pause";
const std::string ASTRONAUT_ID = "astronaut";
const std::string BG_HUD_ID = "hudBG";
const std::string HUD_LEVEL_METER_ID = "levelMeter";
const std::string HUD_PUSH_METER_ID = "pushMeter";
const std::string ALIEN_BLUE_ID = "alienBlue";
const std::string ALIEN_GREEN_ID = "alienGreen";
const std::string ALIEN_ORANGE_ID = "alienOrange";
const std::string ALIEN_RED_ID = "alienRed";
#pragma endregion

std::vector<AlienMap::node>adjacentAliens;
bool mouseOutsideBoard = true;
bool mousePressed = false;

bool PlayState::onEnter()
{
	loading = true;
	p_bIsInPlayState = true;

	TheSoundManager::Instance()->load("assets/audio/bgGame.wav", "bgGame", SOUND_MUSIC);
	TheSoundManager::Instance()->load("assets/audio/no.wav", "no", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/audio/uhu.wav", "uhu", SOUND_SFX);
	TheSoundManager::Instance()->load("assets/audio/what.wav", "what", SOUND_SFX);

	TheSoundManager::Instance()->stopMusic();
	TheSoundManager::Instance()->playMusic("bgGame", -1);

	TheCustomCursor::Instance()->setFrame(0);

	if (!TheTextureManager::Instance()->load("assets/backgrounds/gameBG.jpg", BG_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/hud/hud.png", BG_HUD_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/personas/astronaut.png", ASTRONAUT_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/buttons/btnPause.png", BTN_PAUSE_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/hud/levelMeter.png", HUD_LEVEL_METER_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/hud/pushMeter.png", HUD_PUSH_METER_ID, TheGame::Instance()->getRenderer()))
		return false;

//    m_gameObjects.push_back(CustomBackground(0, 0, 1024, 768, BG_ID));
//    m_gameObjects.push_back(CustomBackground(10, 10, 1005, 32, BG_HUD_ID));
//    m_gameObjects.push_back(HUDMeters(320, 16, 256, 20, HUD_LEVEL_METER_ID));
//    m_gameObjects.push_back(HUDMeters(704, 16, 0, 20, HUD_PUSH_METER_ID));
//    m_gameObjects.push_back(MenuButton(20, 15, 20, 22, BTN_PAUSE_ID, s_playToPause));
//    m_gameObjects.push_back(AnimatedGraphic(896, 640, 64, 64, ASTRONAUT_ID, 1, 4));

	std::cout << "entering PlayState\n";

	TheAlienMap::Instance()->init();

	if (!TheTextureManager::Instance()->load("assets/personas/alienBlue.png", ALIEN_BLUE_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/personas/alienGreen.png", ALIEN_GREEN_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/personas/alienOrange.png", ALIEN_ORANGE_ID, TheGame::Instance()->getRenderer()))
		return false;
	if (!TheTextureManager::Instance()->load("assets/personas/alienRed.png", ALIEN_RED_ID, TheGame::Instance()->getRenderer()))
		return false;

	for (int y = 0; y < TheAlienMap::Instance()->numRows; y++)
	{
		for (int x = 0; x < TheAlienMap::Instance()->numCols; x++)
		{
			int posX = 64 * x;
			int posY = (64 * y) + 64;

			//Use the initial load to instantiate all possible aliens objects
			//That way we don't need to instantiate objects during the game
//            m_aliensType01[y][x] = new Alien(posX, posY, 64, 64, ALIEN_BLUE_ID);
//            m_gameObjects.push_back(m_aliensType01[y][x]);
//
//            m_aliensType02[y][x] = new Alien(posX, posY, 64, 64, ALIEN_GREEN_ID);
//            m_gameObjects.push_back(m_aliensType02[y][x]);
//
//            m_aliensType03[y][x] = new Alien(posX, posY, 64, 64, ALIEN_ORANGE_ID);
//            m_gameObjects.push_back(m_aliensType03[y][x]);
//
//            m_aliensType04[y][x] = new Alien(posX, posY, 64, 64, ALIEN_RED_ID);
//            m_gameObjects.push_back(m_aliensType04[y][x]);
		}
	}

	updateAliensAccordingToMap();
	timer = SDL_GetTicks();
	hudLevelMeter->setWidth(0);
	loading = false;
	return true;
}

void PlayState::update()
{
	if (!p_bIsInPlayState || loading)
		return;

	pushControl();		

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
//        if (m_gameObjects[i].isDead)
            m_gameObjects[i].clean();
//        else
            m_gameObjects[i].update();
	}

	//Get the mouse position and converts to board coordinates
	Vector2D* pMousePos = TheInputHandler::Instance()->getMousePosition();
	int mouseRow, mouseCol;
	mouseCol = (int)pMousePos->getX() / 64;
	mouseRow = (int)(pMousePos->getY() / 64) - 1;

	//prevent to get values outside the matrix
	if (mouseRow < 0) mouseRow = 0;
	if (mouseRow > (TheAlienMap::Instance()->numRows - 1)) mouseRow = (TheAlienMap::Instance()->numRows - 1);
	if (mouseCol < 0) mouseCol = 0;
	if (mouseCol > (TheAlienMap::Instance()->numCols - 1)) mouseCol = (TheAlienMap::Instance()->numCols - 1);

	//Runs through the Board
	for (int row = 0; row < TheAlienMap::Instance()->numRows; row++)
	{
		for (int col = 0; col < TheAlienMap::Instance()->numCols; col++)
		{
			int matrixValue;
			//Check if the mouse position is outside the Alien board:
			if (((int)(pMousePos->getY() / 64) - 1) < 0 || ((int)pMousePos->getY() / 64) > 10)
				matrixValue = 0;//... if true set 0 to value
			else//else get the Alien board value
				matrixValue = TheAlienMap::Instance()->getValue(mouseRow, mouseCol);

			//If find any adjacend Alien
			if (adjacentAliens.size() > 1) {
				//If the player pressed the left button of the mouse do the kill alien logic
				if (InputHandler::Instance()->getMouseButtonState(LEFT) && !mousePressed) {
					mousePressed = true; //prevents that the loop enter here more the one time
					TheSoundManager::Instance()->playSound("what", 0);
					std::vector<int> cols;
					//runs through all the adjacend aliens and remove them
					for (int i = 0; i < adjacentAliens.size(); i++) {
						TheAlienMap::Instance()->setValue(adjacentAliens[i].row, adjacentAliens[i].col, 0);
						if(!(std::find(cols.begin(), cols.end(), adjacentAliens[i].col) != cols.end()))
							cols.push_back(adjacentAliens[i].col);
					}

					TheAlienMap::Instance()->removeEmptySpaces(cols);
					
					//Run though the columns to pull them
					TheAlienMap::Instance()->hasPolled = false;
					for (int i = 0; i < TheAlienMap::Instance()->numCols; i++)
					{
						TheAlienMap::Instance()->pullMatrix(i);
					}
					
					//If removed any column play a sound
					if(TheAlienMap::Instance()->hasPolled)
						TheSoundManager::Instance()->playSound("no", 0);

					updateAliensAccordingToMap();

					//Score logic
					points += cols.size();
					float meterScale = points / level;
					if (points > level) {
						points = level;
						level *= 2.5;
						pushDelay -= 1;
					}

					hudLevelMeter->setWidth(256 * meterScale);
				}

				//Reset the mouse state if player release the button
				if (!InputHandler::Instance()->getMouseButtonState(LEFT) && mousePressed) {
					mousePressed = false;
				}
			}
			
			//If mouse change alien type or is over the first Alien
			if (matrixValue != p_currentSelectionType && matrixValue != 0) {
				mouseOutsideBoard = false;
				//If has previous Aliens return to previous theirs state
				if (adjacentAliens.size() != 0) {
					for (int i = 0; i < adjacentAliens.size(); i++)
						changeAlienState(adjacentAliens[i].row, adjacentAliens[i].col, p_currentSelectionType, MOUSE_OUT);
				}
				//Find new adjacents Aliens
				findAdjacents(mouseRow, mouseCol);
				//CHance their state to "panic"
				for (int i = 0; i < adjacentAliens.size(); i++)
				{
					changeAlienState(adjacentAliens[i].row, adjacentAliens[i].col, matrixValue, MOUSE_OVER);
				}
				p_currentSelectionType = matrixValue;
			}
			//If mouse runs outside the Alien Board return the aliens to Idle state
			else if (matrixValue == 0 && !mouseOutsideBoard) 
			{
				mouseOutsideBoard = true;
				if (adjacentAliens.size() != 0) {
					for (int i = 0; i < adjacentAliens.size(); i++)
					{
						changeAlienState(adjacentAliens[i].row, adjacentAliens[i].col, p_currentSelectionType, MOUSE_OUT);
					}
					adjacentAliens.clear();
					p_currentSelectionType = 0;
				}
			}
		}
	}
}

void PlayState::render()
{
	if (!p_bIsInPlayState || loading)
		return;

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
        m_gameObjects[i].draw();
	}
}

bool PlayState::onExit()
{
	p_bIsInPlayState = false;

	TheTextureManager::Instance()->clearFromTextureMap(BG_ID);
	TheTextureManager::Instance()->clearFromTextureMap(ASTRONAUT_ID);
	TheTextureManager::Instance()->clearFromTextureMap(ALIEN_BLUE_ID);
	TheTextureManager::Instance()->clearFromTextureMap(ALIEN_GREEN_ID);
	TheTextureManager::Instance()->clearFromTextureMap(ALIEN_ORANGE_ID);
	TheTextureManager::Instance()->clearFromTextureMap(ALIEN_RED_ID);

	for (int i = 0; i < m_gameObjects.size(); i++)
	{
        m_gameObjects[i].clean();
	}

	m_gameObjects.clear();

	std::cout << "exiting PlayState\n";
	return true;
}

void PlayState::updateAliensAccordingToMap()
{
	for (int row = 0; row < TheAlienMap::Instance()->numRows; row++)
	{
		for (int col = 0; col < TheAlienMap::Instance()->numCols; col++)
		{
			int alienType = TheAlienMap::Instance()->getValue(row, col);
			switch (alienType)
			{
			case BLUE:
				m_aliensType01[row][col]->setActive();
				m_aliensType02[row][col]->setInactive();
				m_aliensType03[row][col]->setInactive();
				m_aliensType04[row][col]->setInactive();
				break;
			case GREEN:
				m_aliensType01[row][col]->setInactive();
				m_aliensType02[row][col]->setActive();
				m_aliensType03[row][col]->setInactive();
				m_aliensType04[row][col]->setInactive();
				break;
			case ORANGE:
				m_aliensType01[row][col]->setInactive();
				m_aliensType02[row][col]->setInactive();
				m_aliensType03[row][col]->setActive();
				m_aliensType04[row][col]->setInactive();
				break;
			case RED:
				m_aliensType01[row][col]->setInactive();
				m_aliensType02[row][col]->setInactive();
				m_aliensType03[row][col]->setInactive();
				m_aliensType04[row][col]->setActive();
				break;
			default://It means zero position so we need to turn off all aliens
				m_aliensType01[row][col]->setInactive();
				m_aliensType02[row][col]->setInactive();
				m_aliensType03[row][col]->setInactive();
				m_aliensType04[row][col]->setInactive();
				break;
			}
		}
	}
}

void PlayState::changeAlienState(int row, int col, int alienType, alienState newState)
{
	switch (alienType)
	{
	case BLUE:
		m_aliensType01[row][col]->setNewState(newState);
		break;
	case GREEN:
		m_aliensType02[row][col]->setNewState(newState);
		break;
	case ORANGE:
		m_aliensType03[row][col]->setNewState(newState);
		break;
	case RED:
		m_aliensType04[row][col]->setNewState(newState);
		break;
	default:
		break;
	}
}

void PlayState::findAdjacents(int row, int col)
{
	adjacentAliens.clear();
	adjacentAliens = TheAlienMap::Instance()->findAdjacent(row, col);
}

bool PlayState::mouseOver(Vector2D* pMousePos, int targetPosX, int targetPosY)
{
	if (pMousePos->getX() > (targetPosX * 64)
		&& pMousePos->getX() < ((targetPosX * 64) + 64)
		&& pMousePos->getY() > ((targetPosY * 64) + 64)
		&& pMousePos->getY() < ((targetPosY * 64) + 64))
	{
		return true;
	}

	return false;
}

void PlayState::pushMatrix()
{
	if (TheAlienMap::Instance()->pushMatrix()) {
		updateAliensAccordingToMap();
		TheSoundManager::Instance()->playSound("uhu", 0);
	}
	else {
		TheGame::Instance()->getStateMachine()->pushState(new GameOverState());
	}

}

void PlayState::pushControl()
{
	if (TheInputHandler::Instance()->getMouseButtonState(RIGHT) && m_rightBtnMouseRelease) {
		m_rightBtnMouseRelease = false;
		pushMatrix();
		timer = SDL_GetTicks();
		seconds = 1;
		hudPushMeter->setWidth(0);
	}
	else if (!TheInputHandler::Instance()->getMouseButtonState(RIGHT))
	{
		m_rightBtnMouseRelease = true;
	}

	if ((SDL_GetTicks() - timer) > timerDelay) {
		hudPushMeter->setWidth(256 * (seconds / pushDelay));
		timer = SDL_GetTicks();
		seconds++;

		if (seconds > pushDelay) {
			seconds = 1;
			pushMatrix();
			hudPushMeter->setWidth(0);
		}
	}
}

void PlayState::s_playToPause()
{
	TheGame::Instance()->getStateMachine()->pushState(new PauseState());
}
