
/******************************************************************************/
/*!
\file   MyMath.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\brief
  A script does the following:
*/
/******************************************************************************/

#define PI 3.141592653589793238

#include <cmath>

namespace M_MATH
{
	float Clamp(float min, float max, float I_value)
	{
		if (I_value >= max)
		{
			I_value = max;
		}
		if (I_value <= min)
		{
			I_value = min;
		}
		return I_value;
	}
	float LinearLerp(float s, float e, float p)
	{
		return (1.f - p) * s + p * e;
	}
	float EaseInSineLerp(float s, float e, float p)
	{
		e -= s;
		return -e * cos(p * (PI * 0.4f) + e + s);
	}
	//Normalize value
	float NormalizeValue(float value,float distance)
	{
		return value / distance;
	}
	//Convert degree to radian
	float DegreeToRadian(float angle)
	{
		return angle * (PI / 180);
	}
	//Return distance value of 2 points
	float Distance(float const& start_x, float const& end_x, float const& start_y, float const& end_y)
	{
		float distance_x = end_x - start_x;
		float distance_y = end_y - start_y;
		return sqrt(pow(distance_x, 2) + pow(distance_y, 2));
	}
}