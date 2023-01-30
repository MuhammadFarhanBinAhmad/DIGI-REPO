#pragma once
#include "pch.h"


/******************************************************************************/
/*!
\file   GameObject.cpp
\author Muhammad Farhan Bin Ahmad(2200544)
\brief
  A script does the following:
*/
/******************************************************************************/

class GameObject
{
public:
	float pos_x;
	float pos_y;
	float angle;
	float direction_x;
	float direction_y;

	GameObject();
	GameObject(float s_x, float s_y, float s_angle, float offset_x, float offset_y);
};
class Projectile : public GameObject
{
public:
	using GameObject::GameObject;
	float speed;
};

namespace TransformObject

{
	// NEED CHANGE TO POINTER INSTEAD OF REF CAUSE OPTIMIZATION
	//Rotate facing direction of object
	void ObjectRotate(float*start_x, float*start_y, float*direction_x, float*direction_y, float*degree);
	void TransformFoward(float* start_x, float* start_y, float* direction_x, float* direction_y, float*speed);
}
//NEED PUT NAMESPACE GAMEOBJECT ITEMS HERE
namespace TO = TransformObject;