#include "Ball.h"
#include <time.h>
#include <iostream>
using namespace std;

Ball::Ball()
{
	//chieu rong va chieu dai qua bong
	_width = 20;
	_height = 20;
}

Ball::~Ball()
{
}

// hàm gán vị trị cho banh với giá trị đầu vào là biến cấu trúc point ( có 2 thành phần là x và y )
void Ball::setPos(point pos)
{
	this->_ball_pos = pos; // gán giá trị của pos cho biến vị trí của banh 
}


// hàm lấy vị trí của banh vói biến trả về là biến cấu trúc point mang tọa độ (x,y) hiện tại của banh
point Ball::getPos()
{
	return this->_ball_pos; // trả về biến point là tọa độ hiện tại của banh
}


// hàm di chuyển banh ( banh sẽ di chuyển banh theo hướng hiện tại của banh )
void Ball::move(Paddle* playerBottom_info, Paddle* playerTop_info)
{
	switch (this->_ball_dir) // xác định hướng di chuyển hiện tại
	{
	case DOWNLEFT: // trường hợp di chuyển xuống về phái trái
		//kiem tra va cham truoc khi di chuyen
		if (_ball_pos.y + _r + _vY >= playerBottom_info->getPos().y - playerBottom_info->Height()/2)
		{
			//trong thanh truot va goc phai
			//neu qua bong vuot qua thanh truot thi tinh toan de dung truoc khi vuot
			if ( (_ball_pos.x - _vX >= playerBottom_info->getPos().x - playerBottom_info->getSideDistance() ) && (_ball_pos.x - _vX <= playerBottom_info->getPos().x + playerBottom_info->getSideDistance() + _r) && (_ball_pos.y + _vY >= playerBottom_info->getPos().y - playerBottom_info->Height() / 2) )
			{
				float vXtemp = (playerBottom_info->getPos().y - playerBottom_info->Height() / 2 - (_ball_pos.y + _r)) * _vX / _vY;
				_ball_pos.x -= vXtemp;
				_ball_pos.y = playerBottom_info->getPos().y - playerBottom_info->Height() / 2;
				break;
			}
			//cham be ngang ben phai thanh
			else if (_ball_pos.x - _vX >= playerBottom_info->getPos().x + playerBottom_info->getSideDistance() 
				&& ( _ball_pos.x - _vX <= playerBottom_info->getPos().x + playerBottom_info->getSideDistance() + _r) 
				&& (_ball_pos.y + _vY < playerBottom_info->getPos().y - playerBottom_info->Height() / 2) 
				&& _ball_pos.y + _vY < playerBottom_info->getPos().y + playerBottom_info->Height() / 2)
			{
				float vYtemp = (_ball_pos.x - (playerBottom_info->getPos().x + playerBottom_info->getSideDistance())) * _vY / _vX;
				_ball_pos.y += vYtemp;
				_ball_pos.x = playerBottom_info->getPos().x + playerBottom_info->getSideDistance();
				break;
			}
		}
		this->_ball_pos.x = _ball_pos.x - _vX; // giảm tọa độ x của banh
		this->_ball_pos.y = _ball_pos.y + _vY; // tăng tọa dộ y của banh
		break;
	case DOWN: // trường hợp di chuyển xuống

		this->_ball_pos.y = _ball_pos.y + _vY; // tăng tọa độ y của banh
		break;
	case DOWNRIGHT: // trường hợp di chuyển xuống về phía phải 
		this->_ball_pos.x = _ball_pos.x + _vX; // tăng tọa độ x của banh
		this->_ball_pos.y = _ball_pos.y + _vY; // tăng tọa độ y của banh
		break;
	case LEFT: // trường hợp di chuyển sang trái 
		this->_ball_pos.x = _ball_pos.x - _vX; // giảm tọa độ x của banh
		break;
	case STOP: // trường hợp trạng thái di chuyển là dừng thì không thay đổi tọa độ
		break;
	case RIGHT: // trường hợp di chuyển sang phải 
		this->_ball_pos.x = _ball_pos.x + _vX; // tăng tọa độ x của banh
		break;
	case UPLEFT: // trường hợp di chuyển lên về phía trái 
		this->_ball_pos.y = _ball_pos.y - _vY; // giảm tọa độ y của banh
		this->_ball_pos.x = _ball_pos.x - _vX; // giảm tọa độ x của banh
		break;
	case UP: // trường hợp di chuyển lên
		this->_ball_pos.y = _ball_pos.y - _vY; // giảm tọa độ y của banh
		break;
	case UPRIGHT: // trường hợp di chuyển  lên về phía phải 
		this->_ball_pos.y = _ball_pos.y - _vY; // giảm tọa độ y của banh
		this->_ball_pos.x = _ball_pos.x + _vX; // tăng tọa độ x của banh
		break;
	default:
		break;
	}

}


// hàm vẽ trái banh lên màn hình chơi
void Ball::draw(SDL_Renderer*& gRenderer)
{
	//this->GotoXY(this->_ball_pos.x, this->_ball_pos.y); // di chuyển tới tọa dộ hiện tại của banh
	//cout << "O"; // in ra màn hình kí tự 'O' thể hiện trái banh trên màn hinh chơi
	Render(_ball_pos.x - _r, _ball_pos.y - _r, gRenderer);
}


// hàm lấy tốc độ hiện tại của banh với biến trả về dạng float thể hiện tốc độ hiện tại của banh
float Ball::getSpeed()
{
	return this->_speed;  // trả về về tốc độ hiện tại của banh 
}


// hàm gán tốc độ cho banh với giá trị đầu vào là biến dạng float thể hiện tốc độ mới 
void Ball::setSpeed(float speed)
{
	this->_speed = speed; // gán speed cho tốc độ hiện tại của banh
}


// hàm gán hướng cho banh với biến đầu vào là enum balldirection 
void Ball::setDir(balldirection ball_dir)
{
	this->_ball_dir = ball_dir; // gán ball_dir cho hướng di chuyển hiện tại của banh
}


// hàm lấy hướng di chuyển hiện tại của banh với biến trả là một enum balldirection thể hiện hướng di chuyển của banh
balldirection Ball::getDir()
{
	return this->_ball_dir; // trả về hướng của banh
}

// constructor của lớp banh với biến đầu vào lần lượt là tọa độ (x,y) , tốc độ của banh hướng di chuyển của banh va duong dan den hinh qua banh
Ball::Ball(float x, float y, float speed, string path, SDL_Renderer*& gRenderer, balldirection ball_dir = DOWN)
{
	this->_ball_original_pos.x = x; // gán tọa độ x cho x gốc 
	this->_ball_original_pos.y = y; // gán tọa độ y cho y gốc 
	this->_ball_pos.x = x; // gán tọa độ x cho x hiện tại
	this->_ball_pos.y = y; // gán tọa độ y cho y hiện tại
	this->_speed = speed; // gán tốc độ ( speed ) cho tốc độ hiện tại
	this->_ball_dir = ball_dir; // gán hướng di chuyển cho banh ( ball_dir ) cho hướng di chuyển hiện tại

	//random van toc qua banh
	srand((unsigned int)time(NULL));
	_vX = (float)(rand() % 11 + 10) / 10;
	_vY = (float)(rand() % 11 + 10) / 10;

	//chieu rong va chieu dai qua bong
	_width = 20;
	_height = 20;

	//Tai hinh qua bong
	LoadFromFile(path, gRenderer);
	
	//random huong
	_ball_dir = (balldirection)(rand() % 9 + 1);

	//neu huong la stop, left, right thi random lai
	while (_ball_dir == STOP || _ball_dir == LEFT || _ball_dir == RIGHT)
	{
		_ball_dir = (balldirection)(rand() % 9 + 1);
	}
	
	//ban kinh
	_r = _height / 2;
}


// hàm tạo lại vị trí của banh và tạo ngẫu nhiên hướng mới cho banh
void Ball::reset()
{
	this->_ball_pos = this->_ball_original_pos; // vị trí của banh khi được tạo lại sẽ được gán cho giá trị của vị trí banh gốc 

	//random huong
	_ball_dir = (balldirection)(rand() % 9 + 1);

	//random van toc qua banh
	srand((unsigned int)time(NULL));
	_vX = (float)(rand() % 11 + 10) / 10;
	_vY = (float)(rand() % 11 + 10) / 10;

	//neu huong la stop, left, right thi random lai
	while (_ball_dir == STOP || _ball_dir == LEFT || _ball_dir == RIGHT)
	{
		_ball_dir = (balldirection)(rand() % 9 + 1);
	}
}


// hàm xóa trái banh khỏi màn hình chơi 
void Ball::clear()
{
	//this->GotoXY(_ball_pos.x, _ball_pos.y); // tới vị trí của banh 
	//cout << " "; // in ra màn hình " " ( in đè lên 'O' đã được in trước đó )
}


// hàm kiểm tra va chạm của banh với thanh trượt trên với biến đầu vào là một con trỏ thuộc lớp Paddle, sau khi kiểm tra nếu đúng thì hàm sẽ thay đổi hướng của banh sao cho phù hợp sau khi va chạm 
bool Ball::impactTop(Paddle* playerTop_info)
{
	point paddle_pos = playerTop_info->getPos(); // lấy tọa độ của thanh trượt trên 
	if (this->_ball_pos.y - _r <= paddle_pos.y + playerTop_info->Height() / 2 && _ball_pos.y - _r >= paddle_pos.y - sqrt(_vX * _vX + _vY + _vY)) // (1) nếu tọa độ y hiện tại của banh bằng với tọa độ y của thanh trượt cộng thêm 1 thì ta tiến hành kiểm tra tọa độ x của thanh trượt ( lúc này banh đang năm ngay dưới thanh trượt nhưng tùy vào tọa độ x của thanh trượt và banh thì mới xảy ra va chạm )
	{
		int size = playerTop_info->getSize(); // lấy kích thước hiện tại của thanh trượt 
		int start_pos = paddle_pos.x - playerTop_info->getSideDistance() - 1; // nếu đã thỏa (1) thì để xảy ra va chạm thì tọa độ x của banh phải nằm trong khoảng ( biên trái thanh trượt - 1; biên phải thanh trượt + 1 ) nên ta xét từ vị trí biên trái - 1 trở qua phải
		//for (int i = 0; i < size + 2; i++) // vòng lặp for để kiểm tra từng tọa độ x từ ( biên trái thanh trượt - 1; biên phải thanh trượt + 1 )
		//{
		if (this->_ball_pos.x >= start_pos && _ball_pos.x <= start_pos + size + 1) // nếu tạo độ của banh nằm trong khoảng mà ta đã nêu trên thì va chạm xảy ra
		{
			// hướng dội ra của banh phụ thuộc vào hướng di chuyển của chính nó và của thanh trượt 
			paddledirection paddle_dir = playerTop_info->getDir(); // lấy hướng di chuyển của than trượt 
			balldirection ball_dir = this->getDir(); // lấy hướng di chuyển quả banh
			switch (paddle_dir) // xét hướng di chuyển của thanh trượt 
			{
			case PLEFT: // trường hợp thanh trượt sang trái 
				switch (ball_dir) // xét hướng di chuyển của banh 
				{
				case UP: // nếu banh đi lên 
					this->_ball_dir = DOWNLEFT; // va chạm xảy ra thì sẽ dội xuống sang trái 
					return true; // trả về true vì đã diễn ra va chạm
				case UPLEFT: // nếu banh đi lên sang trái 
					this->_ball_dir = DOWNLEFT; // va chạm xảy ra thì sẽ dội xuống sang trái 
					return true; // trả về true vì đã diễn ra va chạm
				case UPRIGHT:
					this->_ball_dir = DOWNRIGHT;
					return true; // trả về true vì đã diễn ra va chạm
				default:
					break;
				}
				break;
			case PRIGHT: // trường hợp thanh trượt sang phải
				switch (ball_dir) // xét hướng di chuyển của banh
				{
				case UP: // banh đi lên 
					this->_ball_dir = DOWNRIGHT; // sẽ dội xuống sang phải
					return true; // trả về true vì đã diễn ra va chạm
				case UPLEFT: // banh đi lên sang trái 
					this->_ball_dir = DOWNLEFT; // sẽ dội xuống sang trái 
					return true; // trả về true vì đã diễn ra va chạm
				case UPRIGHT: // banh đi lên sang phải 
					this->_ball_dir = DOWNRIGHT; // sẽ dội xuống sang phải
					return true; // trả về true vì đã diễn ra va chạm
				default:
					break;
				}
				break;
			case NONE: // trường hợp thanh trượt đứng yên
				switch (ball_dir) // xét hướng di chuyển của banh
				{
				case UP: // banh đi lên
					if (_ball_pos.x > start_pos && _ball_pos.x < start_pos + size + 1) // nêu không phải ngay rìa thanh trượt ( biên trái - 1 hoặc biên phải + 1 )
					{
						this->_ball_dir = DOWN; // banh sẽ dội xuống
						return true; // trả về true vì đã diễn ra va chạm
					}
					if (_ball_pos.x == start_pos) // nếu rìa trái 
					{
						this->_ball_dir = UPLEFT; // banh sẽ đi lên sang trái 
						return true; // trả về true vì đã diễn ra va chạm 
					}
					if (_ball_pos.x == start_pos + size + 1) // nếu rìa phải
					{
						this->_ball_dir = UPRIGHT; // banh sẽ đi lên sang phải
						return true; // trả về true vì đã diễn ra va chạm
					}
				case UPLEFT: // banh đi lên sang trái 
					this->_ball_dir = DOWNLEFT; // banh dội xuống sang trái
					return true; // trả về true vì đã diễn ra va chạm
				case UPRIGHT: // banh đi lên sang phải 
					this->_ball_dir = DOWNRIGHT; // dội xuống sang phải
					return true; // trả về true vì đã diễn ra va chạm
				default:
					break;
				}
			}
		}
	}
	return false; // trả về false vì không xảy ra va chạm
}


// hàm kiểm tra va chạm của banh với thanh trượt dưới với biến đầu vào là một con trỏ thuộc lớp Paddle, sau khi kiểm tra nếu đúng thì hàm sẽ thay đổi hướng của banh sao cho phù hợp sau khi va chạm
bool Ball::impactBottom(Paddle* playerBottom_info)
{
	point paddle_pos = playerBottom_info->getPos(); // lấy tọa độ của thanh trượt dưới
	if ( (this->_ball_pos.y + _r >= paddle_pos.y - playerBottom_info->Height()/2)
		&& _ball_pos.y + _r <= paddle_pos.y + playerBottom_info->Height() / 2)
		// (1) nếu tọa độ y hiện tại của banh bằng với tọa độ y của thanh trượt cộng trừ 1 thì ta tiến hành kiểm tra tọa độ x của thanh trượt ( lúc này banh đang năm ngay trên thanh trượt nhưng tùy vào tọa độ x của thanh trượt và banh thì mới xảy ra va chạm )
	{
		int size = playerBottom_info->getSize(); // lấy kích thước hiện tại của thanh trượt 
		//int start_pos = paddle_pos.x - playerBottom_info->getSideDistance() - 1; // nếu đã thỏa (1) thì để xảy ra va chạm thì tọa độ x của banh phải nằm trong khoảng ( biên trái thanh trượt - 1; biên phải thanh trượt + 1 ) nên ta xét từ vị trí biên trái - 1 trở qua phải
		//for (int i = 0; i < size + 2; i++) // vòng lặp for để kiểm tra từng tọa độ x từ ( biên trái thanh trượt - 1; biên phải thanh trượt + 1 )
		//{
		if (this->_ball_pos.x >= paddle_pos.x - playerBottom_info->getSideDistance() - _r
			&& _ball_pos.x <= paddle_pos.x + playerBottom_info->getSideDistance() + _r) // nếu tạo độ của banh nằm trong khoảng mà ta đã nêu trên thì va chạm xảy ra
		{
			// hướng dội ra của banh phụ thuộc vào hướng di chuyển của chính nó và của thanh trượt 
			paddledirection paddle_dir = playerBottom_info->getDir(); // lấy hướng di chuyển của than trượt 
			balldirection ball_dir = getDir(); // xét hướng di chuyển của thanh trượt 
			switch (paddle_dir) // xét hướng di chuyển của thanh trượt 
			{
			case PLEFT: // trường hợp thanh trượt sang trái 
				switch (ball_dir) // xét hướng di chuyển của banh
				{
				case DOWN: // banh đi xuống 
					this->_ball_dir = UPLEFT; // banh dội lên sang trái 
					return true; // trả về true vì đã diễn ra va chạm
				case DOWNLEFT: // banh đi xuống sang trái 
					//va cham trong thanh truot
					if (this->_ball_pos.x >= paddle_pos.x - playerBottom_info->getSideDistance()
						&& _ball_pos.x <= paddle_pos.x + playerBottom_info->getSideDistance())
					{
						this->_ball_dir = UPLEFT; // banh dội lên sang trái
					}
					//va cham vao goc
					else if (_ball_pos.x > paddle_pos.x + playerBottom_info->getSideDistance()
						&& _ball_pos.x <= paddle_pos.x + playerBottom_info->getSideDistance() + _r
						&& _ball_pos.y > paddle_pos.y - playerBottom_info->Height() / 2)
					{
						_ball_dir = UPRIGHT;
					}
					else if (_ball_pos.x <= paddle_pos.x + playerBottom_info->getSideDistance() + _r
						&& _ball_pos.y <= paddle_pos.y - playerBottom_info->Height() / 2
						&& _ball_pos.y >= paddle_pos.y + playerBottom_info->Height() / 2)
					{
						_ball_dir = DOWNRIGHT;
					}
					return true; // trả về true vì đã diễn ra va chạm
				case DOWNRIGHT: // banh đi xuống sang phải 
					this->_ball_dir = UPRIGHT; // banh dội lên sang phải 
					return true; // trả về true vì đã diễn ra va chạm
				default:
					break;
				}
				break;
			case PRIGHT: // trường hợp thanh trượt sang phải
				switch (ball_dir) // xét hướng di chuyển của banh
				{
				case DOWN: // banh đi xuống 
					this->_ball_dir = UPRIGHT; // banh đi lên sang phải 
					return true; // trả về true vì đã diễn ra va chạm
				case DOWNLEFT: // banh đi xuống sang trái 
					this->_ball_dir = UPLEFT; // banh đi lên sang trái 
					return true; // trả về true vì đã diễn ra va chạm
				case DOWNRIGHT: // banh đi xuống sang phải 
					this->_ball_dir = UPRIGHT; // banh đi lên sang phải 
					return true; // trả về true vì đã diễn ra va chạm
				default:
					break;
				}
				break;
			case NONE: // trường hợp thanh trượt đứng yên
				switch (ball_dir) // xét hướng di chuyển của banh
				{
				case DOWN: // banh đi xuống 
					if (_ball_pos.x >= paddle_pos.x - playerBottom_info->getSideDistance()
						&& _ball_pos.x <= paddle_pos.x + playerBottom_info->getSideDistance()) // nêu không phải ngay rìa thanh trượt 
					{
						this->_ball_dir = UP; // banh sẽ đi lên 
						return true; // trả về true vì đã diễn ra va chạm
					}
					else if (_ball_pos.x < paddle_pos.x - playerBottom_info->getSideDistance()
						&& _ball_pos.x > paddle_pos.x - playerBottom_info->getSideDistance() - _r) // rìa trái thanh trượt
					{
						this->_ball_dir = UPLEFT; // banh sẽ đi len sang trái 
						return true; // trả về true vì đã diễn ra va chạm
					}
					else if (_ball_pos.x > paddle_pos.x + playerBottom_info->getSideDistance()
						&& _ball_pos.x < paddle_pos.x + playerBottom_info->getSideDistance() + _r) // rìa phải thanh trượt 
					{
						this->_ball_dir = UPRIGHT; // banh sẽ đi lên sang phải
						return true; // trả về true vì đã diễn ra va chạm
					}
				case DOWNLEFT: // banh đi xuống sang trái 
					this->_ball_dir = UPLEFT; // banh đi lên sang trái 
					return true; // trả về true vì đã diễn ra va chạm
				case DOWNRIGHT: // banh đi xuống sang phải 
					this->_ball_dir = UPRIGHT; // banh đi lên sang phải
					return true; // trả về true vì đã diễn ra va chạm
				default:
					break;
				}
				break;
			}
		}
		//}
	}
	return false; // trả về false vì không có xảy ra va chạm 
}


// hàm kiểm tra va chạm của banh với tường của trò chơi, sau khi kiểm tra nếu đúng thì hàm sẽ thay đổi hướng của banh sao cho phù hợp sau khi va chạm ( nếu chạm tường trên và tường dưới thì hướng banh sẽ trở thành trạng thái STOP == đứng yên )
bool Ball::impactWall(int top, int bot, int left, int right)
{
	if (this->_ball_pos.y - _r <= top) // đụng vị trs tường trên ( tường trên y == 0 )
	{
		this->_ball_dir = STOP; // banh sẽ dừng lại 
		return true; // trả về kết quả true vì đã diễn ra va chạm
	}
	if (this->_ball_pos.y + _r >= bot) // đụng vị trí tường dưới ( tường dưới y == hieght -1 )
	{
		this->_ball_dir = STOP; // banh sẽ dừng lại
		return true; // trả về kết quả true vì đã diễn ra va chạm
	}
	if (this->_ball_pos.x - _r<= left) // đụng vị trí tường trái ( tường trái x == 0 )
	{
		if (this->_ball_dir == UPLEFT) // nếu banh đanh đi lên sang trái 
		{
			this->_ball_dir = UPRIGHT; // thì sẽ đổi hướng đi lên sang phải 
			return true; // trả về kết quả true vì đã diễn ra va chạm 
		}
		if (this->_ball_dir == DOWNLEFT) // nếu banh đi xuống sang trái 
		{
			this->_ball_dir = DOWNRIGHT; // thì sẽ đổi hướng sanh phải 
			return true; // trả về kết quả true vì đã diễn ra va chạm
		}
	}
	if (this->_ball_pos.x + _r>= right) // đụng vị trí tường phải ( tường phải x == width -1 )
	{
		if (this->_ball_dir == UPRIGHT) // nếu banh đang đi lên sang phải 
		{
			this->_ball_dir = UPLEFT; // thì đổi hướng đi lên sang trái
			return true; // trả về kết quả true vì đã diễn ra va chạm
		}
		if (this->_ball_dir == DOWNRIGHT) // nếu banh đi xuống sang phải 
		{
			this->_ball_dir = DOWNLEFT; // thì sẽ đổi hướng đi xuống sang trái
			return true; // trả về kết quả true vì đã diễn ra va chạm 
		}
	}
	return false; // trả về false vì không diễn ra va chạm
}