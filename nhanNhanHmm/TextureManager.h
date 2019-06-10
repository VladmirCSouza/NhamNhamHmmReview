#pragma once

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

class TextureManager
{
public:

	static TextureManager* Instance() {
		if (s_pInstance == 0)
			s_pInstance = new TextureManager();

		return s_pInstance;
	}

	bool load(std::string fileName, std::string id, SDL_Renderer* pRenderer);

	//draw
	void draw(std::string id, int x, int y, float width, float height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	//drawframe
	void drawframe(std::string id, int x, int y, float width, float height, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void clearFromTextureMap(std::string id);


	std::map<std::string, SDL_Texture*> m_textureMap;


private:
	TextureManager();
	~TextureManager();

	static TextureManager* s_pInstance;
};

typedef TextureManager TheTextureManager;
