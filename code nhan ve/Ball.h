#pragma once
#include "Draw.h"
#include "Point.h"
#include "Paddle.h"

// các hướng di chuyển có thể của banh ( 8 hướng và 1 trạng thái không di chuyển == STOP ): LEFT, UPLEFT, DOWNLEFT, RIGHT, UPRIGHT, DOWNRIGHT, UP, DOWN, STOP
enum balldirection { STOP = 5, LEFT = 4, RIGHT = 6, UP = 8, DOWN = 2, UPLEFT = 7, UPRIGHT = 9, DOWNLEFT = 1, DOWNRIGHT = 3 };

class Ball: protected Draw
{
private:
	// vị trí của banh
	point _ball_pos;


	// vị trí gốc của banh
	point _ball_original_pos;


	// hướng di chuyển của banh
	balldirection _ball_dir;


	// tốc độ của banh
	float _speed;
public:


	// hàm tạo lại vị trí của banh và tạo ngẫu nhiên hướng mới cho banh
	void reset();


	// hàm gán tọa độ cho banh với giá trị đầu vào là biến cấu trúc point ( có 2 thành phần là x và y )
	void setPos(point pos); 


	// hàm lấy tọa độ của banh vói biến trả về là biến cấu trúc point mang tọa độ (x,y) hiện tại của banh
	point getPos();


	// hàm di chuyển banh ( banh sẽ di chuyển banh theo hướng hiện tại của banh )
	void move();


	// hàm vẽ trái banh lên màn hình chơi
	void draw();


	// hàm xóa trái banh khỏi màn hình chơi 
	void clear();


	// hàm lấy tốc độ hiện tại của banh với biến trả về dạng float thể hiện tốc độ hiện tại của banh
	float getSpeed();


	// hàm gán tốc độ cho banh với giá trị đầu vào là biến dạng float thể hiện tốc độ mới 
	void setSpeed(float speed);


	// hàm gán hướng cho banh với biến đầu vào là enum balldirection 
	void setDir(balldirection ball_dir);


	// hàm lấy hướng di chuyển hiện tại của banh với biến trả là một enum balldirection thể hiện hướng di chuyển của banh
	balldirection getDir();


	// constructor của lớp banh với biến đầu vào lần lượt là tọa độ (x,y) , tốc độ của banh và hướng di chuyển của banh
	Ball(int x, int y, float speed, balldirection ball_dir);


	// hàm kiểm tra va chạm của banh với thanh trượt trên với biến đầu vào là một con trỏ thuộc lớp Paddle, sau khi kiểm tra nếu đúng thì hàm sẽ thay đổi hướng của banh sao cho phù hợp sau khi va chạm 
	bool impactTop(Paddle* playerTop_info);


	// hàm kiểm tra va chạm của banh với thanh trượt dưới với biến đầu vào là một con trỏ thuộc lớp Paddle, sau khi kiểm tra nếu đúng thì hàm sẽ thay đổi hướng của banh sao cho phù hợp sau khi va chạm
	bool impactBottom(Paddle* playerBottom_info);


	// hàm kiểm tra va chạm của banh với tường của trò chơi, sau khi kiểm tra nếu đúng thì hàm sẽ thay đổi hướng của banh sao cho phù hợp sau khi va chạm ( nếu chạm tường trên và tường dưới thì hướng banh sẽ trở thành trạng thái STOP == đứng yên )
	bool impactWall(int width, int height);
};

