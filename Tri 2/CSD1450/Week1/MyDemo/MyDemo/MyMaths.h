#pragma once
/******************************************************************************/
/*!
\file   MyMath.hpp
\author Muhammad Farhan Bin Ahmad(2200544)
\brief
  A script does the following:
*/
/******************************************************************************/
namespace M_MATH
{
	float Clamp(float min, float max, float I_value);
	float LinearLerp(float s, float e, float p);
	float EaseInSineLerp(float s, float e, float p);
	float NormalizeValue(float value, float distance);
	float DegreeToRadian(float angle);
	float Distance(float const& start_x, float const& end_x, float const& start_y, float const& end_y);
}


namespace MM = M_MATH;


