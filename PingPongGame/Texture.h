#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>

class Texture
{
protected:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int _width;
	int _height;
public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool LoadFromFile(std::string path, SDL_Renderer*& gRenderer);

	//Deallocates texture
	void Free();

	//Renders texture at given point
	void Render(float x, float y, SDL_Renderer*& gRenderer);

	//Gets image dimensions
	int Width() { return _width; }
	int Height() { return _height; }
};


