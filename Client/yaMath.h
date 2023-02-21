#pragma once

struct Vector2
{
	float x;
	float y;

	Vector2()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	Vector2(Vector2* other)
	{
		x = other->x;
		y = other->y;
	}




};


class Math
{

};

