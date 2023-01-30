#include "AEEngine.h"
#include "GameObject.h"

#include <iostream>

f32 static friction = 0.90f;
f32 speed_Current = 0;
f32 speed_Limit_x = 40.f;
f32 speed_Limit_y = 40.f;

//MATHS NEEDE FOR OBJECT TRANSFORMATION
f32 GetNormal(f32 value, f32 distace)
{
	return value / distace;
}
f32 GetDistance(AEVec2* Direction)
{
	f32 distance_x = Direction->x - 0;
	f32 distance_y = Direction->y - 0;
	return sqrt(pow(distance_x, 2) + pow(distance_y, 2));
}
//HANDLE OBJECT TRANSFORMATION
void ObjectRotate(AEVec2* Direction, float degree)
{
	float radius = GetDistance(Direction);
	Direction->x = radius * cos(degree);
	Direction->y = radius * sin(degree);
}
void ResetPostion(AEVec2* Origin, AEVec2* Direction)
{
	//Reset pos. This is to ensure the value for rotation, direction etc. are all based on origin.
	Origin->x = 0;
	Origin->y = 0;
	//By default facing right
	Direction->x = 10;
	Direction->y = 0;
}
void SetPosition(AEVec2* object, AEVec2 SetPoint)
{
	object->x = SetPoint.x;
	object->y = SetPoint.y;
}
void SetNormal(AEVec2* Direction, ObjectNormalValue* ONV, int type)
{
	float distance_x = Direction->x - 0;
	float distance_y = Direction->y - 0;
	float distance_Total = GetDistance(Direction);
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
void UpdateSpeed(float * ship_CurrentSpeed,const float ship_Acceleration,bool is_accelerating)
{
	f32 static friction = 0.90f;
	f32 static speed_Limit = 40.f;


	if (*ship_CurrentSpeed > speed_Limit)
	{
		*ship_CurrentSpeed = speed_Limit;//cap speed
	}
	if (*ship_CurrentSpeed < -speed_Limit)
	{
		*ship_CurrentSpeed = -speed_Limit;//cap speed
	}
	if (*ship_CurrentSpeed < speed_Limit && is_accelerating)
	{
		*ship_CurrentSpeed += ship_Acceleration * (float)(AEFrameRateControllerGetFrameTime());
	}
	/*if (*ship_CurrentSpeed > 0 && !AEInputCheckCurr(AEVK_DOWN))
	{
		*ship_CurrentSpeed -= ship_Acceleration * (float)(AEFrameRateControllerGetFrameTime());
		return;
	}*/
	//Slow down ship if no input

}
void TransformFoward(AEVec2* Origin, ObjectNormalValue* ONV, int type, float speed)
{
	if (type == PLAYERSHIP)
	{
		Origin->x += ONV->player_Ship_x * speed;
		Origin->y += ONV->player_Ship_y * speed;
	}
	if (type == PLAYERBULLET)
	{
		Origin->x += ONV->player_Bullet_x * speed;
		Origin->y += ONV->player_Bullet_y * speed;
	}
}
