#include "Texture.h"


Texture::Texture()
{
	//Initialize
	mTexture = NULL;
	_width = 0;
	_height = 0;
}

Texture::~Texture()
{
	//Deallocate
	Free();
}

bool Texture::LoadFromFile(std::string path, SDL_Renderer*& gRenderer)
{
	//Get rid of preexisting texture
	Free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			_width = loadedSurface->w;
			_height = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Texture::Free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		_width = 0;
		_height = 0;
	}
}

void Texture::Render(float x, float y, SDL_Renderer*& gRenderer)
{
	//Set rendering space and render to screen
	SDL_FRect renderQuad = { x, y, (float)_width, (float)_height };

	//Render to screen
	SDL_RenderCopyF(gRenderer, mTexture, NULL, &renderQuad);
}
