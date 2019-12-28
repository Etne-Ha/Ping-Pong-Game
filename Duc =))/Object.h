#pragma once
#include "Ball.h"
#include <time.h>

enum
{
	DEAD = 0, GIFT = 2, WALL = 3, BOX = 1
};

class Object
{
protected:
	int _x;
	int _y;
	int _w;
	int _h;
	int _key;
	int _giftCode;
public:
	void Get_Object(int x, int y, int w, int h, int key);
	Object();
	~Object();
	int getKey() { return _key; }
public:
	bool Collide(Ball* _ball);
	void AfterCollide(Ball* _ball, Paddle* _paddle);
};

