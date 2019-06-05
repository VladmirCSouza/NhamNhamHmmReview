/**
Main class of the project.
Here you can seput the window config, the FPS of our game, etc.
st
@author Vladmir C. Souza
*/

#include "Game.h"

//our Game obj
Game* g_game = 0;

//Game screen setup
const char GAME_TITLE[20] = "Nham Nham Hmmm";
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const bool IS_FULLSCREEN = false;

//GAME FPS setup
const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[]) {
		
	//Used to control the game FPS
	Uint32 frameStart, frameTime;

	std::cout << "game init attempt...\n";
	if(TheGame::Instance()->init(GAME_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, IS_FULLSCREEN))
	{
		std::cout << "game init success...\n";
		while (TheGame::Instance()->running())
		{
			//Get the time since the loop starts
			frameStart = SDL_GetTicks();

			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();

			//Get how long it took to run the game
			frameTime = SDL_GetTicks() - frameStart;

			//It itsless than the time we want a frame to take make the loop wait
			if (frameTime < DELAY_TIME) 
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}

			//SDL_ShowCursor(SDL_DISABLE);
		}
	}
	else
	{
		std::cout << "game init fail - " << SDL_GetError() << "\n";
		return -1;
	}

	SDL_ShowCursor(SDL_ENABLE);

	std::cout << "game closing...\n";
	TheGame::Instance()->clean();

	return 0;

}
