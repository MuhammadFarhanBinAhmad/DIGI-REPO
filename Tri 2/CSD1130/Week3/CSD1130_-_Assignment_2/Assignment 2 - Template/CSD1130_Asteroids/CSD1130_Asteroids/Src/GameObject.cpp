/******************************************************************************/
/*!
\file		GameObject.cpp
\author 	MuhammadFarhanBinAhmad(2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	February 02, 2023
\brief		My attempt to create my own function which handles the rotation and movement
			script. I wanted to make because, while the features given are present in Alpha Engine
			I wanted to try and learn how the system and calculation works. Thus my attempt to create my
			own function. Sadly due to time, i was unable to finish this and had to use the tool AE has
			made for me to use.
			I'm keeping this however for future reference so that in the future i can reattempt this and possible
			learn where i went wrong

			GetNormal - Return a normalise value
			GetDistance - Get Distance value between 2 points(C = Sqrt(A^2+B^2))
			ObjectRotate - Handle rotation of current object
			ResetPosition - Set position of object to default position that has been set
			TransformFoward - Move foward in the direction the object is currently facing(I took the idea from Unity)

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "AEEngine.h"
#include "GameObject.h"

#include <iostream>


f32 speed_Current = 0;
f32 speed_Limit_x = 40.f;
f32 speed_Limit_y = 40.f;

//MATHS NEEDE FOR OBJECT TRANSFORMATION

f32 GetNormal(f32 value, f32 distace)
{
	return value / distace;
}
f32 GetDistance(AEVec2* Origin,AEVec2* Direction)
{
	f32 distance_x = Direction->x - Origin->x;
	f32 distance_y = Direction->y - Origin->y;
	return sqrt(pow(distance_x, 2) + pow(distance_y, 2));
}
//HANDLE OBJECT TRANSFORMATION
void ObjectRotate(AEVec2 *Origin,AEVec2* Direction, float degree)
{
	float radius = GetDistance(Origin,Direction);
	Direction->x = radius * cos(degree);
	Direction->y = radius * sin(degree);
}
void ResetPostion(AEVec2* Origin, AEVec2* Direction)
{
	//Reset pos. This is to ensure the value for rotation, direction etc. are all based on origin.
	Origin->x = 0;
	Origin->y = 0;
	//By default facing right
	Direction->x = 1;
	Direction->y = 0;
}
void SetPosition(AEVec2* object, AEVec2 SetPoint)
{
	object->x = SetPoint.x;
	object->y = SetPoint.y;
}
void SetNormal(AEVec2 *Origin,AEVec2* Direction, ObjectNormalValue* ONV, int type)
{
	float distance_x = Direction->x - Origin->x;
	float distance_y = Direction->y - Origin->y;
	float distance_Total = GetDistance(Origin,Direction);
	if (type == PLAYERSHIP)
	{
		ONV->player_Ship_x = GetNormal(distance_x, distance_Total);
		ONV->player_Ship_y = GetNormal(distance_y, distance_Total);
	}
	if (type == PLAYERBULLET)
	{
		ONV->player_Ship_x = GetNormal(distance_x, distance_Total);
		ONV->player_Ship_y = GetNormal(distance_y, distance_Total);
		ONV->player_Bullet_x = ONV->player_Ship_x;
		ONV->player_Bullet_y = ONV->player_Ship_y;
	}
}

void TransformFoward(AEVec2* Origin, AEVec2* Dir, ObjectNormalValue* ONV, int type, float speed)
{
	float distance_x = Dir->x - Origin->x;
	float distance_y = Dir->y - Origin->y;
	float distance_Total = GetDistance(Origin, Dir);
	if (type == PLAYERSHIP)
	{
		Origin->x += ONV->player_Ship_x * speed;
		Origin->y += ONV->player_Ship_y * speed;
		Dir->x += ONV->player_Ship_x * speed;
		Dir->y += ONV->player_Ship_y * speed;
	}
	if (type == PLAYERBULLET)
	{
		Origin->x += ONV->player_Bullet_x * speed;
		Origin->y += ONV->player_Bullet_y * speed;

	}
}
void TransformFoward(AEVec2* Origin, AEVec2* Dir, int type, float speed)
{
	if (type == PLAYERBULLET)
	{
		Origin->x += Dir->x * speed;
		Origin->y += Dir->y * speed;
	}
	if (type == ASTEROID)
	{
		Origin->x += Dir->x * speed;
		Origin->y += Dir->y * speed;
	}
}