/******************************************************************************/
/*!
\file		Vector2d.cpp
\author 	muhammad farhan bin ahmad(2200544)
\par    	email : b.muhammadfarhan@digipen.edu
\date   	March 11, 2023
\brief
			2 Constructor:
			Default constructor
			//Non default assignment constructor

			4 Assigment operator:
			Vector2D& operator += 
			Vector2D& operator -= 
			Vector2D& operator *= 
			Vector2D& operator /=

			1 Unary operators:
			Vector2D operator -() const

			4 Non-member operator :
			Vector2D operator + (const Vector2D &lhs, const Vector2D &rhs)
			Vector2D operator - (const Vector2D &lhs, const Vector2D &rhs)
			Vector2D operator * (const Vector2D &lhs, float rhs)
			Vector2D operator * (float lhs, const Vector2D &rhs)
			Vector2D operator / (const Vector2D &lhs, float rhs)

			7 Non - member function :
			Vector2DNormalize - Calculate and set normalize value
			Vector2DLength - Get length of vector
			Vector2DSquareLength - Get square length of vector
			Vector2DDistance - Get distance value between 2 points
			Vector2DSquareDistance - Get distance square value between 2 points
			Vector2DDotProduct - Get dot product value of 2 vector
			Vector2DCrossProductMag - Get cross product magnitrude of 2 vector

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "Vector2D.h"
#include <math.h>
namespace CSD1130
{
	//Non default assignment constructor
	Vector2D::Vector2D(float _x, float _y)
	{
		this->x = _x;
		this->y = _y;
	}

	// Assignment operators
	Vector2D& Vector2D::operator+=(const Vector2D& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}
	Vector2D& Vector2D::operator-=(const Vector2D& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}
	Vector2D& Vector2D::operator *= (float rhs)
	{
		this->x *= rhs;
		this->y *= rhs;

		return *this;
	}
	Vector2D& Vector2D::operator /= (float rhs)
	{
		this->x /= rhs;
		this->y /= rhs;

		return *this;
	}

	// Unary operators
	Vector2D Vector2D::operator-() const
	{
		return Vector2D(-x, -y);
	}

	//Binary Operator
	Vector2D operator + (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D temp{};
		temp.x = lhs.x + rhs.x;
		temp.y = lhs.y + rhs.y;
		return temp;
	}
	Vector2D operator - (const Vector2D& lhs, const Vector2D& rhs)
	{
		Vector2D temp{};
		temp.x = lhs.x - rhs.x;
		temp.y = lhs.y - rhs.y;
		return temp;
	}
	Vector2D operator * (const Vector2D& lhs, float rhs)
	{
		Vector2D temp{};
		temp.x = lhs.x * rhs;
		temp.y = lhs.y * rhs;
		return temp;
	}
	Vector2D operator * (float lhs, const Vector2D& rhs)
	{
		Vector2D temp{};
		temp.x = lhs * rhs.x;
		temp.y = lhs * rhs.y;
		return temp;
	}
	Vector2D operator / (const Vector2D& lhs, float rhs)
	{
		Vector2D temp{};
		temp.x = lhs.x / rhs;
		temp.y = lhs.y / rhs;
		return temp;
	}

	/**************************************************************************/
	/*!
		In this function, pResult will be the unit vector of pVec0
	 */
	 /**************************************************************************/
	void Vector2DNormalize(Vector2D& pResult, const Vector2D& pVec0)
	{
		float magnitude = sqrt(pVec0.x * pVec0.x + pVec0.y * pVec0.y);
		if (magnitude > 0.0f)
		{
			pResult.x = pVec0.x / magnitude;
			pResult.y = pVec0.y / magnitude;
		}
		else
		{
			pResult.x = 0.0f;
			pResult.y = 0.0f;
		}
	}

	/**************************************************************************/
	/*!
		This function returns the length of the vector pVec0
	 */
	 /**************************************************************************/
	float	Vector2DLength(const Vector2D& pVec0)
	{
		return sqrt((pVec0.x * pVec0.x) + (pVec0.y * pVec0.y));
	}

	/**************************************************************************/
	/*!
		This function returns the square of pVec0's length. Avoid the square root
	 */
	 /**************************************************************************/
	float	Vector2DSquareLength(const Vector2D& pVec0)
	{
		return pVec0.x* pVec0.x + pVec0.y * pVec0.y;
	}

	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The distance between these 2 2D points is returned
	 */
	 /**************************************************************************/
	float	Vector2DDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		float x_vector = (pVec1.x - pVec0.x);
		float y_vector = (pVec1.y - pVec0.y);

		return sqrt((x_vector * x_vector) + (y_vector * y_vector));
	}

	/**************************************************************************/
	/*!
		In this function, pVec0 and pVec1 are considered as 2D points.
		The squared distance between these 2 2D points is returned.
		Avoid the square root
	 */
	 /**************************************************************************/
	float	Vector2DSquareDistance(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		float x_vector = (pVec1.x - pVec0.x);
		float y_vector = (pVec1.y - pVec0.y);
		return (x_vector * x_vector) + (y_vector * y_vector);

	}

	/**************************************************************************/
	/*!
		This function returns the dot product between pVec0 and pVec1
	 */
	 /**************************************************************************/
	float	Vector2DDotProduct(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return (pVec0.x * pVec1.x) + (pVec0.y * pVec1.y);
	}

	/**************************************************************************/
	/*!
		This function returns the cross product magnitude
		between pVec0 and pVec1
	 */
	 /**************************************************************************/
	float	Vector2DCrossProductMag(const Vector2D& pVec0, const Vector2D& pVec1)
	{
		return pVec0.x * pVec1.y - pVec0.y * pVec1.x;
	}
}