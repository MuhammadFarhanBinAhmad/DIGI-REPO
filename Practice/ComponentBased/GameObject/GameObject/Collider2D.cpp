#include "Collider2D.h"

Collider2D::Collider2D()
{
	vec.x = 0;
	vec.y = 0;
}
Collider2D::Collider2D(const Collider2D& vec2d)
{
	vec.x = vec2d.vec.x;
	vec.y = vec2d.vec.y;
}

Collider2D::~Collider2D()
{

}

Collider2D& Collider2D::operator=(const Collider2D& vec2d)
{
	vec.x = vec2d.vec.x;
	vec.y = vec2d.vec.y;

	return *this;
}

void Collider2D::SetDimension2D(const Vector2D &vec2d)
{
	vec.x = vec2d.x;
	vec.y = vec2d.y;
}

Vector2D Collider2D::GetDimension2D(){return vec;}
