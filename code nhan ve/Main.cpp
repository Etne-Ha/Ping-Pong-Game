#include "Draw.h"
#include "Pong.h"
#include <windows.h>

// cố định màn hình //
void FixConsoleWindow()
{
	HWND consoleWindow = GetConsoleWindow(); 
	RECT ConsoleRect; 
	GetWindowRect(consoleWindow, &ConsoleRect);
	MoveWindow(consoleWindow, ConsoleRect.left, ConsoleRect.top, 800, 600, TRUE);
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}


int main()
{
	Pong Game(40, 30, INTRO); // tạo một vật thể thuộc lớp game pong với chiều rộng == 40 và chiều cao == 30 với trạng thái vào game là INTRO 
	FixConsoleWindow(); // cố định màn hình chơi
	Game.start(); // bắt đầu chạy game
	return 0;
}