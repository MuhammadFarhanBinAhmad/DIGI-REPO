#include "pch.h"
#include "AEEngine.h"


GameObject::GameObject(float s_x, float s_y, float s_angle, float offset_x, float offset_y)
{
		pos_x = s_x;
		pos_y = s_y;
		angle = s_angle;
		direction_x = s_x + offset_x;
		direction_y = s_y + offset_y;
}


namespace TransformObject
{
	// NEED CHANGE TO POINTER INSTEAD OF REF CAUSE OPTIMIZATION
	//Rotate facing direction of object
	void ObjectRotate(f32 *start_x, float *start_y, float *direction_x, float *direction_y, float *degree)
	{
		float radius = M_MATH::Distance(*start_x, *direction_x, *start_y, *direction_y);
		//Cmath already converted the angle to radian
		*direction_x = radius * cos(*degree);
		*direction_y = radius * sin(*degree);
	}
	//Projectile move at the current rotation it is facing
	void TransformFoward(f32 *start_x, f32 *start_y, f32 * direction_x, float* direction_y, float *speed)
	{
		float distance_x = *direction_x - *start_x;
		float distance_y = *direction_y - *start_y;
		float total_Distance = M_MATH::Distance(*start_x, *direction_x, *start_y, *direction_y);
		float normal_x = M_MATH::NormalizeValue(distance_x, total_Distance);
		float normal_y = M_MATH::NormalizeValue(distance_y, total_Distance);
		//Movement
		*start_x += normal_x *5 ;
		*start_y += normal_y *5 ;
		//Maintain offset distance value
		*direction_x += distance_x;
		*direction_y += distance_y;
	}
}

namespace TO = TransformObject;