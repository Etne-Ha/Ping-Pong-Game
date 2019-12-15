#include "Object.h"

Object::Object()
{
}

void Object::Get_Object(int x, int y, int w, int h, int key)
{
	_x = x;
	_y = y;
	_w = w;
	_h = h;
	_key = key;
	
	if (key == GIFT)
	{
		srand((unsigned int)time(NULL));
		_giftCode = rand() % 3;
	}
}


Object::~Object()
{
}

bool Object::Collide(Ball* _ball)
{
	if (_key == DEAD)
	{
		return false;
	}
	switch (_ball->getDir()) // xét hướng di chuyển của banh
	{
	case UP: // banh đi len 
	{
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
		break;
	}
	case UPLEFT: // banh đi len sang trái 
	{
		//va cham trong thanh truot
		if (_ball->getPos().x >= _x && _ball->getPos().x <= _x + _w
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon)
		{
			_ball->setDir(DOWNLEFT); // banh dội xuong sang trái
			return true; // trả về true vì đã diễn ra va chạm
		}
		//va cham vao goc phai
		else if (_ball->getPos().x > _x + _w - epsilon && _ball->getPos().x <= _x + _w + _ball->R()
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon)
		{
			_ball->setDir(DOWNRIGHT); // banh di xuong sang phai
			return true; // trả về true vì đã diễn ra va chạm
		}
		//cham be ngang thanh truot
		else if (_ball->getPos().x > _x + _w - epsilon && _ball->getPos().x <= _x + _w + _ball->R()
			&& _ball->getPos().y < _y + _h - epsilon && _ball->getPos().y >= _y)
		{
			_ball->setDir(UPRIGHT); // banh di len sang phai
			return true; // trả về true vì đã diễn ra va chạm
		}
		break;
	}
	case UPRIGHT: // banh đi len sang phải 
	{
		//va cham trong thanh truot
		if (_ball->getPos().x >= _x && _ball->getPos().x <= _x + _w
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon)
		{
			_ball->setDir(DOWNRIGHT); // banh đi xuong sang phải
			return true; // trả về true vì đã diễn ra va chạm
		}
		//va cham vao goc trai
		else if (_ball->getPos().x > _x - _ball->R() && _ball->getPos().x <= _x + epsilon
			&& _ball->getPos().y - _ball->R() <= _y + _h && _ball->getPos().y - _ball->R() >= _y + _h - epsilon)
		{
			_ball->setDir(DOWNLEFT); // banh di xuong goc trai
			return true; // trả về true vì đã diễn ra va chạm
		}
		//cham be ngang thanh truot
		else if (_ball->getPos().x > _x - _ball->R() && _ball->getPos().x <= _x + epsilon
			&& _ball->getPos().y < _y + _h - epsilon && _ball->getPos().y >= _y)
		{
			_ball->setDir(UPLEFT); // banh di len ben phai
			return true; // trả về true vì đã diễn ra va chạm
		}
		break;
	}
	case DOWN: // banh đi xuống 
	{
		if (_ball->getPos().x >= _x && _ball->getPos().x <= _x + _w
			&& _ball->getPos().y + _ball->R() >= _y && _ball->getPos().y + _ball->R() <= _y + epsilon) // nêu không phải ngay rìa thanh trượt 
		{
			_ball->setDir(UP); // banh sẽ đi lên 
			return true; // trả về true vì đã diễn ra va chạm
		}
		else if (_ball->getPos().x < _x && _ball->getPos().x > _x - _ball->R()
			&& _ball->getPos().y + _ball->R() >= _y && _ball->getPos().y + _ball->R() <= _y + epsilon) // rìa trái thanh trượt
		{
			_ball->setDir(UPLEFT); // banh sẽ đi len sang trái 
			return true; // trả về true vì đã diễn ra va chạm
		}
		else if (_ball->getPos().x > _x + _w && _ball->getPos().x < _x + _w + _ball->R()
			&& _ball->getPos().y + _ball->R() >= _y && _ball->getPos().y + _ball->R() <= _y + epsilon) // rìa phải thanh trượt 
		{
			_ball->setDir(UPRIGHT); // banh sẽ đi lên sang phải
			return true; // trả về true vì đã diễn ra va chạm
		}
		break;
	}
	case DOWNLEFT: // banh đi xuống sang trái 
	{
		//va cham trong thanh truot
		if (_ball->getPos().x >= _x && _ball->getPos().x <= _x + _w
			&& _ball->getPos().y + _ball->R() >= _y && _ball->getPos().y + _ball->R() <= _y + epsilon)
		{
			_ball->setDir(UPLEFT); // banh dội lên sang trái
			return true; // trả về true vì đã diễn ra va chạm
		}
		//va cham vao goc phai
		else if (_ball->getPos().x > _x + _w - epsilon && _ball->getPos().x <= _x + _w + _ball->R()
			&& _ball->getPos().y + _ball->R() >= _y && _ball->getPos().y + _ball->R() <= _y + epsilon)
		{
			_ball->setDir(UPRIGHT); // banh di len sang phai
			return true; // trả về true vì đã diễn ra va chạm
		}
		//cham be ngang thanh truot ben phai
		else if (_ball->getPos().x > _x + _w - epsilon && _ball->getPos().x <= _x + _w + _ball->R()
			&& _ball->getPos().y > _y + epsilon && _ball->getPos().y <= _y + _h)
		{
			_ball->setDir(DOWNRIGHT);
			return true; // trả về true vì đã diễn ra va chạm
		}
		break;
	}
	case DOWNRIGHT: // banh đi xuống sang phải 
	{
		//va cham trong thanh truot
		if (_ball->getPos().x >= _x && _ball->getPos().x <= _x + _w
			&& _ball->getPos().y + _ball->R() >= _y && _ball->getPos().y + _ball->R() <= _y + epsilon)
		{
			_ball->setDir(UPRIGHT); // banh đi lên sang phải
			return true; // trả về true vì đã diễn ra va chạm
		}
		//va cham vao goc trai
		else if (_ball->getPos().x > _x - _ball->R() && _ball->getPos().x <= _x + epsilon
			&& _ball->getPos().y + _ball->R() >= _y && _ball->getPos().y + _ball->R() <= _y + epsilon)
		{
			_ball->setDir(UPLEFT); // banh di len goc trai
			return true; // trả về true vì đã diễn ra va chạm
		}
		//cham be ngang thanh truot
		else if (_ball->getPos().x > _x - _ball->R() && _ball->getPos().x <= _x + epsilon
			&& _ball->getPos().y > _y + epsilon
			&& _ball->getPos().y <= _y + _h)
		{
			_ball->setDir(DOWNLEFT);
			return true; // trả về true vì đã diễn ra va chạm
		}
		break;
	}
	default:
		break;
	}

	return false;
}

void Object::AfterCollide(Ball* _ball, Paddle* _paddle)
{
	if (_key == DEAD)
	{
		return;
	}

	if (_key == GIFT)
	{
		//do something


		//huy object
		_key = DEAD;
	}
	else if (_key == BOX)
	{
		//tang diem
		_paddle->SetScore(_paddle->Score() + 10);

		//huy object
		_key = DEAD;
	}

}