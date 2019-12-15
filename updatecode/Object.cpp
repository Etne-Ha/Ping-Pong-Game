#include "Object.h"



Object::Object()
{
}


Object::~Object()
{
}

bool Object::Collide(Ball* _ball)
{
	switch (_ball->getDir()) // xét hướng di chuyển của banh
	{
	case UP: // banh đi len 
		if (_ball->getPos().x >= _x && _ball->getPos().x <= _x + _w
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon) // nêu không phải ngay rìa thanh trượt 
		{
			_ball->setDir(DOWN); // banh sẽ đi xuong
			return true; // trả về true vì đã diễn ra va chạm
		}
		else if (_ball->getPos().x < _x && _ball->getPos().x > _x - _ball->R()
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon) // rìa trái thanh trượt
		{
			_ball->setDir(DOWNLEFT); // banh sẽ đi xuong sang trái 
			return true; // trả về true vì đã diễn ra va chạm
		}
		else if (_ball->getPos().x > _x + _w && _ball->getPos().x < _x + _w + _ball->R()
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon) // rìa phải thanh trượt 
		{
			_ball->setDir(DOWNRIGHT); // banh sẽ đi xuong sang phải
			return true; // trả về true vì đã diễn ra va chạm
		}
	case UPLEFT: // banh đi len sang trái 
	{
		//va cham trong thanh truot
		if (_ball->getPos().x >= _x && _ball->getPos().x <= _x + _w
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon)
		{
			_ball->setDir(DOWNLEFT); // banh dội xuong sang trái
		}
		//va cham vao goc phai
		else if (_ball->getPos().x > _x + _w - epsilon && _ball->getPos().x <= _x + _w + _ball->R()
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon)
		{
			_ball->setDir(DOWNRIGHT); // banh di xuong sang phai
		}
		//cham be ngang thanh truot
		else if (_ball->getPos().x > _x + _w - epsilon && _ball->getPos().x <= _x + _w + _ball->R()
			&& _ball->getPos().y < _y + _h - epsilon && _ball->getPos().y >= _y)
		{
			_ball->setDir(UPRIGHT); // banh di len sang phai
		}
		return true; // trả về true vì đã diễn ra va chạm
	}
	case UPRIGHT: // banh đi len sang phải 
	{
		//va cham trong thanh truot
		if (_ball->getPos().x >= _x && _ball->getPos().x <= _x + _w
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon)
		{
			_ball->setDir(DOWNRIGHT); // banh đi xuong sang phải
		}
		//va cham vao goc trai
		else if (_ball->getPos().x > _x - _ball->R() && _ball->getPos().x <= _x + epsilon
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon)
		{
			_ball->setDir(DOWNLEFT); // banh di xuong goc trai
		}
		//cham be ngang thanh truot
		else if (_ball->getPos().x > _x - _ball->R() && _ball->getPos().x <= _x + epsilon
			&& _ball->getPos().y < _y + _h - epsilon && _ball->getPos().y >= _y)
		{
			_ball->setDir(UPLEFT); // banh di len ben phai
		}
		return true; // trả về true vì đã diễn ra va chạm
	}
	default:
		break;
	}

	return false;
}
