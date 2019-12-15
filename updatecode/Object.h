#pragma once
#include "Ball.h"

enum
{
	GIFT, WALL, BOX
};

class Object
{
protected:
	int _x;
	int _y;
	int _w;
	int _h;
	int _key;
public:
	Object();
	~Object();
public:
	virtual bool Collide(Ball* _ball);
};

