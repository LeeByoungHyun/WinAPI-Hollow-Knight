#pragma once
#include <math.h>
#define PI 3.141592


struct Vector2
{
	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;

	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{

	}
	Vector2(float x, float y)
		: x(x)
		, y(y)
	{

	}
	Vector2(int x, int y)
		: x(x)
		, y(y)
	{

	}

	Vector2(const Vector2&) = default;
	Vector2& operator=(const Vector2&) = default;

	Vector2(Vector2&&) = default;
	Vector2& operator=(Vector2&&) = default;

	Vector2 operator+(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x + other.x;
		temp.y = y + other.y;

		return temp;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;

		return temp;
	}

	Vector2 operator*(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}

	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}

	float Length()
	{
		return sqrtf((x * x) + (y * y));
	}
	Vector2& Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;

		return *this;
	}
};

namespace ya::math
{
	inline static Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (degree / 180.0f) * PI;
		vector.Normalize();

		float x = vector.x * cosf(radian) - vector.y * sinf(radian);
		float y = vector.x * sinf(radian) - vector.y * cosf(radian);

		return Vector2(x, y);
	}
}

