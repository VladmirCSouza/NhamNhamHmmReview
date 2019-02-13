#include "TextureManager.h"

TextureManager* TextureManager::s_pInstance = 0;

/**
	Loads the desired texture
*/
bool TextureManager::load(std::string fileName, std::string id, SDL_Renderer* pRenderer) {
	SDL_Surface* pTempSurface = IMG_Load(fileName.c_str());

	if (pTempSurface == 0) {
		std::cout << "Fail to load " << fileName.c_str()  << "\n";
		return false;
	}

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

	SDL_FreeSurface(pTempSurface);
	if (pTexture != 0) {
		m_textureMap[id] = pTexture;
		return true;
	}

	std::cout << "Fail to create SDL_Texture with " << fileName.c_str() << "\n";
	return false;
}

/**
	Used to draw a static texture
*/
void TextureManager::draw(std::string id, int x, int y, float width, float height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) {
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

/**
	Used to draw animated spritesheets
*/
void TextureManager::drawframe(std::string id, int x, int y, float width, float height, int currentRow, int currentFrame, SDL_Renderer * pRenderer, SDL_RendererFlip flip){
	SDL_Rect srcRect;
	SDL_Rect destRect;
	
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow - 1);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;

	SDL_RenderCopyEx(pRenderer, m_textureMap[id], &srcRect, &destRect, 0, 0, flip);
}

void TextureManager::clearFromTextureMap(std::string id)
{
	m_textureMap.erase(id);
}


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}
