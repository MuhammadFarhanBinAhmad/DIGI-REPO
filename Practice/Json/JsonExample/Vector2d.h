#pragma once
class Vec2D
{
public:
	int x, y;

	Vec2D& operator=(const Vec2D& other)
	{
		x = other.x;
		y = other.y;

		return *this;
	}
};