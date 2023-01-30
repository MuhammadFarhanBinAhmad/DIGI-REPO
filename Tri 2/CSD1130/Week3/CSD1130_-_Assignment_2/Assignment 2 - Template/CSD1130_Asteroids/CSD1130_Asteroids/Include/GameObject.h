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
void ObjectRotate(AEVec2* Direction, float degree);
void ResetPostion(AEVec2* Origin, AEVec2* Direction);
void SetNormal(AEVec2* Direction, ObjectNormalValue* ONV, int type);
void TransformFoward(AEVec2* Origin, ObjectNormalValue* ONV, int type, float speed);
void UpdateSpeed(float* ship_CurrentSpeed, const float ship_Acceleration, bool is_accelerating);
void SetPosition(AEVec2* object, AEVec2 SetPoint);
//MATHS NEEDE FOR OBJECT TRANSFORMATION
void GetNormal();
f32 GetDistance();