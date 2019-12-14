#include "SDL_ttf.h"
#include "SDL.h"
#include "SDL_image.h"
#include "stdio.h"
#include "iostream"
#include "fstream"
#include "string"

using namespace std;


void Init(SDL_Window*& window, SDL_Renderer*& renderer);

void Del_Init(SDL_Window*& gWindow, SDL_Renderer*& gRenderer);

int Menu(SDL_Window*& window, SDL_Renderer*& renderer);

int pre_start(SDL_Window*& window, SDL_Renderer*& renderer);

void score(SDL_Window*& window, SDL_Renderer*& renderer);

string EnterPlayerName(SDL_Window*& window, SDL_Renderer*& renderer);

void load(SDL_Window*& window, SDL_Renderer*& renderer);

void exit(SDL_Window*& window, SDL_Renderer*& renderer);

void Start_new(SDL_Window*& window, SDL_Renderer*& renderer, string name);

void Start_classic();

void Save(SDL_Window*& window, SDL_Renderer*& renderer, string name);