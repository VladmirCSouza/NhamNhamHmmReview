#ifndef __LoaderParams__
#define __LoaderParams__

#include <iostream>

class LoaderParams
{
public:
	/**
	Parameters used to load game objects
		int x - the position on X axys
		int y - the position on Y axys
		int width - the width of the frame
		int height - the heght of the frame
		string textureID - the ID used to identify the texture
	*/
	LoaderParams(int x, int y, float width, float height, std::string textureID) :
		m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID) {}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	std::string getTextureID() const { return m_textureID; }
	

private:
	std::string m_textureID;

	int m_x;
	int m_y;

	int m_width;
	int m_height;
};

#endif