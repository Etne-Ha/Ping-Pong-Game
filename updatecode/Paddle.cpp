#include "Paddle.h"
#include <iostream>
using namespace std;

// hàm gán vị trí cho thanh trượt với biến đầu vào có cấu trúc point ( chứ tọa độ (x,y) )
void Paddle::setPos(point pos)
{
	this->_paddle_pos = pos; // gán pos cho tọa độ giữa hiện tại của thanh trượt 
}


// hàm lấy tọa độ của thanh trượt 
point Paddle::getPos()
{
	return this->_paddle_pos; // trả về tọa độ giữa hiện tại của thanh trượt
}


// hàm di chuyển thanh trượt dựa và hướng di chuyển hiện tại của thanh trượt
void Paddle::move()
{
	switch (this->_paddle_dir) // kiểm tra hướng di chuyển hiện tại của thanh trượt 
	{
	case PLEFT: // trường hợp hướng di chuyển là về bên trái 
		if (this->_paddle_pos.x - this->_side_distance - _v > this->_left_limit) // nếu khoảng cách từ biên trái thanh trượt ( lấy tọa độ giữa thanh trượt trừ cho khoảng cách tới biên thì được tọa độ biên trái ) tới giới hạn trái của nó > 1 tức là còn đủ 1 đơn vị khoảng cách để di chuyển sang trái thì mới tiến hành di chuyển thanh trượt sang trái
		{
			this->_paddle_pos.x -= _v; // giảm x của thanh trượt 
		}
		break;
	case PRIGHT: // trường hợp hướng di chuyển là về bên phải 
		if (this->_paddle_pos.x + this->_side_distance + _v < this->_right_limit) // nếu khoảng cách từ biên phải thanh trượt ( lấy tọa độ giữa thanh trượt cộng cho khoảng cách tới biên thì được tọa độ biên phải ) tới giới hạn phải của nó > 1 tức là còn đủ 1 đơn vị khoảng cách để di chuyển sang phải thì mới tiến hành di chuyển thanh trượt sang phải
		{
			this->_paddle_pos.x += _v; // tăng x của thanh trượt
		}
	case NONE: // trường hợp NONE thì không di chuyển
		break;
	}
}


// hàm vẽ thanh trượt lên màn hình chơi
void Paddle::draw(SDL_Renderer*& gRenderer)
{
	//GotoXY(this->_paddle_pos.x - this->_side_distance, this->_paddle_pos.y); // tới vị trí biên trái của thanh trượt 
	//for (int i = 0; i < this->_size; i++) // vòng for chạy hết kích thước của thanh trượt ( từ i == 0 là x của biên trái tới i == _size - 1 là x của biên phải )
	//{
		//cout << "="; // in ra kí tự '=' vì thanh trượt là 1 dãy '=' nằm kề nhau
	//}
	Render(_paddle_pos.x - _width / 2, _paddle_pos.y - _height / 2, gRenderer);
}


// hàm xóa thanh trượt khỏi màn hình chơi
void Paddle::clear()
{
	//GotoXY(this->_paddle_pos.x - this->_side_distance, this->_paddle_pos.y); // tới vị trí biên trái của thanh trượt
	//for (int i = 0; i < this->_size; i++) // vòng for chạy hết kích thước của thanh trượt ( từ i == 0 là x của biên trái tới i == _size - 1 là x của biên phải )
	//{
	//	cout << " "; // in ra kí tự " " để đè lên kí tự '=' 
	//}
}


// hàm lấy hướng di chuyển của thanh trượt với biến trả về là một enum paddledirection thể hiện hướng di chuyển của thanh trượt
paddledirection Paddle::getDir()
{
	return this->_paddle_dir; // trả về hướng di chuyển hiện tại của thanh trượt 
}


// gán vị trí cho thanh trượt với biến đầu vào là một enum paddledirection thể hiện hướng di chuyển của thanh trượt
void Paddle::setDir(paddledirection paddle_dir)
{
	this->_paddle_dir = paddle_dir; // gán paddle_dir cho hướng di chuyển hiện tại của than trượt 
}


// hàm gán kích thước cho thanh trượt 
void Paddle::setSize(int size)
{
	this->_size = size; // gán size cho kich thước của thanh trượt
}


// hàm lấy kích thước của thanh trượt 
int Paddle::getSize()
{
	return this->_size; // trả về kích thước của thanh trượt 
}


// constructor của lớp Paddle với biến đầu vào lần lượt là tọa độ (x,y), kích thước thanh trượt, giới hạn trái, giới hạn phải, hướng di chuyển của thanh trượt 
Paddle::Paddle(int x, int y, int size, int left_limit, int right_limit, string path, SDL_Renderer*& gRenderer, paddledirection paddle_dir = NONE)
{
	this->_paddle_original_pos.x = (float)x; // gán x cho x gốc 
	this->_paddle_original_pos.y = (float)y; // gán y cho y gốc
	this->_paddle_pos.x = (float)x; // gán x cho x hiện tại
	this->_paddle_pos.y = (float)y; // gán y cho y hiện tại
	this->_size = size; // gán size cho kích thước hiện tại
	this->_side_distance = this->_size / 2; // khoảng cách biên sẽ bằng kích thước hiện tại chia 2 
	this->_paddle_dir = paddle_dir; // gán paddle_dỉ cho hướng di chuyển hiện tại
	this->_left_limit = left_limit; // gán left_limit cho giới hạn trái 
	this->_right_limit = right_limit; // gán right_limit cho giới hạn phải 

	//chieu cao va chieu rong thanh truot
	_width = 120;
	_height = 32;

	//Khoi tao van toc thanh truot
	_v = 4;

	//Khoi tao diem
	_score = 0;

	//load hinh paddle
	LoadFromFile(path, gRenderer);
}


// hàm tạo lại thanh trượt 
void Paddle::reset()
{
	_v = 4;
	this->_paddle_pos.x = this->_paddle_original_pos.x; // gán x bằng x gốc 
	this->_paddle_pos.y = this->_paddle_original_pos.y; // gán y bằng y gốc 
	this->_paddle_dir = NONE;
}


// hàm lấy khoảng cách từ biên thanh trượt tới vị trí giữa thanh trượt 
int Paddle::getSideDistance()
{
	return this->_side_distance; // trả về khoảng cách tới biên
}


// hàm lấy giới hạn phải 
int Paddle::getRightLimit()
{
	return this->_right_limit;
}


// hàm lấy giới hạn trái
int Paddle::getLeftLimit()
{
	return this->_left_limit;
}

