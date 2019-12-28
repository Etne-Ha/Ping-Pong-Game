#include "iostream"
#include "stdio.h"
#include "Menus.h"

#undef main

using namespace std;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
 


int main()
{
	Init(window, renderer);

	Menu(window, renderer);


	return 0;
}