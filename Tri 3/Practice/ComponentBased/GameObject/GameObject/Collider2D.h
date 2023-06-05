#pragma once

#include "Vector.h"

class Collider2D
{
private:
	enum Type : int { TwoDimension, ThreeDimension } Dimension;
	Vector2D vec;
public:
	Collider2D();
	Collider2D(const Collider2D& vec2d);
	~Collider2D();

	Collider2D& operator=(const Collider2D& vec2d);

	void SetDimension2D(const Vector2D& vec2d);
	Vector2D GetDimension2D();
};