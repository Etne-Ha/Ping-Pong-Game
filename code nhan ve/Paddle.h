#pragma once
#include "Draw.h"
#include "Point.h"

// các hướng di chuyển của thanh trượt ( có 2 hướng di chuyển và 1 trại thái NONE == đứng yên ): PLFET, PRIGHT, NONE
enum paddledirection { NONE = 0, PLEFT = 1, PRIGHT = 2 };

class Paddle : protected Draw
{
private:
	// vị trí của thanh trượt ( tọa độ (x,y) ngay giữa thanh trượt )
	point _paddle_pos;


	// vị trí gốc của thanh trượt ( tọa độ (x,y) ngay giữa thanh trượt )
	point _paddle_original_pos;


	// kích thước của thanh trượt 
	int _size;


	// hướng di chuyển của thanh trượt 
	paddledirection _paddle_dir;


	// giới hạn trái màn hình mà thanh trượt có thể di chuyển tới 
	int _left_limit;


	// giới hạn phải màn hình mà thanh trượt có thể di chuyển tới 
	int _right_limit;


	// khoảng cách từ tọa độ (x,y) cuối cùng hoặc đầu tiên của thanh trượt tới tọa độ (x,y) giữa của thanh trượt 
	int _side_distance;
public:


	// hàm gán vị trí cho thanh trượt với biến đầu vào có cấu trúc point ( chứ tọa độ (x,y) )
	void setPos(point pos);


	// hàm lấy tọa độ của thanh trượt 
	point getPos();


	// hàm di chuyển thanh trượt dựa và hướng di chuyển hiện tại của thanh trượt
	void move();


	// hàm vẽ thanh trượt lên màn hình chơi
	void draw();


	// hàm xóa thanh trượt khỏi màn hình chơi
	void clear();


	// hàm lấy hướng di chuyển của thanh trượt với biến trả về là một enum paddledirection thể hiện hướng di chuyển của thanh trượt
	paddledirection getDir();


	// gán vị trí cho thanh trượt với biến đầu vào là một enum paddledirection thể hiện hướng di chuyển của thanh trượt
	void setDir(paddledirection paddle_dir);


	// hàm gán kích thước cho thanh trượt 
	void setSize(int size);


	// hàm lấy kích thước của thanh trượt 
	int getSize();


	// constructor của lớp Paddle với biến đầu vào lần lượt là tọa độ (x,y), kích thước thanh trượt, giới hạn trái, giới hạn phải, hướng di chuyển của thanh trượt 
	Paddle(int x, int y, int size, int left_limit, int right_limit, paddledirection paddle_dir);


	// hàm tạo lại thanh trượt về vị trí gốc và hướng mặc định 
	void reset();


	// hàm lấy khoảng cách từ biên thanh trượt tới vị trí giữa thanh trượt 
	int getSideDistance();


	// hàm lấy giới hạn phải 
	int getRightLimit();


	// hàm lấy giới hạn trái
	int getLeftLimit();
};

