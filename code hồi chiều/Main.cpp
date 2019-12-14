#include "Draw.h"
#include "Pong.h"
#include <windows.h>
#include "Menus.h"
#undef main

int main()
{
	Screen screen;
	Start_new(screen.GWindow(), screen.GRenderer(),"somebody");
	Menu(screen.GWindow(), screen.GRenderer());
	
	
	return 0;
}

//int main()
//{
//	Screen screen;
//
//	//Main loop flag
//	bool quit = false;
//
//	//Event handler
//	SDL_Event e;
//
//	Ball b(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 10, "ball.png", screen.GRenderer(), DOWN); // tạo trái banh
//	Ball* _ball = &b; // trỏ tới trái banh
//
//	Paddle p2(SCREEN_WIDTH / 2, SCREEN_HEIGHT - 200, 120, 0, SCREEN_WIDTH, "bar2.png", screen.GRenderer(), NONE); // tạo thanh trượt dưới 
//	Paddle* _playerBottom = &p2; // trỏ tới thanh trượt dưới
//
//	//While application is running
//	while (!quit && !(GetAsyncKeyState(VkKeyScan('F') && GetAsyncKeyState(VkKeyScan('f')))))
//	{
//		screen.Clear();
//		_ball->Render(_ball->getPos().x, _ball->getPos().y, screen.GRenderer());
//		_playerBottom->Render(_playerBottom->getPos().x, _playerBottom->getPos().y, screen.GRenderer());
//
//		_ball->move();
//		_playerBottom->move();
//		//Handle events on queue
//		while (SDL_PollEvent(&e) != 0)
//		{
//			//User requests quit
//			if (e.type == SDL_QUIT)
//			{
//				quit = true;
//			}
//		}
//
//		//Update the surface
//		screen.Update();
//	}
//
//	return 0;
//}