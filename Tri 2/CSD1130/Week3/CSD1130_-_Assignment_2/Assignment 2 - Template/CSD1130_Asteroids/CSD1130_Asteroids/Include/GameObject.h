/******************************************************************************/
/*!
\file		GameObject.h
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
#pragma once
#include "AEEngine.h"
//Contain all normal value for all moving objects
struct ObjectNormalValue
{

	f32 player_Ship_x = 0;
	f32 player_Ship_y = 0;
	f32 player_Bullet_x = 0;
	f32 player_Bullet_y = 0;
	f32 hazard_Asteroid_x = 0;
	f32 hazard_Asteroid_y = 0;
};
enum
{
	PLAYERSHIP = 0,
	PLAYERBULLET,
	ASTEROID

	
};
//HANDLE OBJECT TRANSFORMATION
void ObjectRotate(AEVec2* Origin,AEVec2* Direction, float degree);
void ResetPostion(AEVec2* Origin, AEVec2* Direction);
void SetNormal(AEVec2* Origin,AEVec2* Direction, ObjectNormalValue* ONV, int type);
void TransformFoward(AEVec2* Origin, AEVec2* Direction, ObjectNormalValue* ONV, int type, float speed);
void TransformFoward(AEVec2* Origin, AEVec2* Dir, int type, float speed);
void SetPosition(AEVec2* object, AEVec2 SetPoint);

//MATHS NEEDE FOR OBJECT TRANSFORMATION
void GetNormal();
f32 GetDistance(AEVec2* Origin, AEVec2* Direction);