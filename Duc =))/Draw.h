#pragma once
#include <SDL.h>

class Draw
{
protected:
	// hàm dùng để vẽ tường khi kết thúc trò chơi ( có thêm hiệu ứng so với hàm vẽ tường thông thường ) với tham số đầu vào lần lượt là chiều rộng, chiều cao, tọa độ x và tọa độ y của điểm mà ở đó ta bắt đâu vẽ tường
	void drawWallEndGame(int width, int height, int x, int y);


	//  hàm dùng để vẽ tường cho trò chơi với tham số đầu vào lần lượt là chiều rộng, chiều cao, tọa độ x và tọa độ y của điểm mà ở đó ta bắt đâu vẽ tường
	void drawWall(int width, int height, int x, int y); 


	// hàm dùng để đưa con trỏ tới vị trí có tọa độ (x,y) trên màn hình
	void GotoXY(int x, int y); 


	// hàm dùng để đổi màu của chữ sang màu xanh dương
	void changeTextColorBlue();


	// hàm dùng để dổi màu của chữ sang màu đỏ 
	void changeTextColorRed(); 


	 // hàm dùng để đổi màu của chữ sang màu xanh lá
	void changeTextColorGreen(); 


	// hàm dùng để dổi màu của chữ sang màu trắng
	void changeTextColorWhite(); 

	// vẽ màn hình chơi game
	void DrawWindow();
};

