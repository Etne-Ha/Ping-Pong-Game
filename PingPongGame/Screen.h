#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#define SCREEN_WIDTH 1257
#define SCREEN_HEIGHT 730


class Screen
{
private:
	//con tro Renderer cua man hinh
	SDL_Renderer* gRenderer;

	//con tro man hinh
	SDL_Window* gWindow;
public:
	Screen();
	~Screen();

	//lay con tro Renderer
	SDL_Renderer*& GRenderer() { return gRenderer; }

	//lay con tro man hinh
	SDL_Window*& GWindow() { return gWindow; }
public:
	//khoi tao man hinh
	bool Init();

	//huy man hinh
	void Close();

	//xoa man hinh
	void Clear();

	//cap nhat man hinh
	void Update();
};

