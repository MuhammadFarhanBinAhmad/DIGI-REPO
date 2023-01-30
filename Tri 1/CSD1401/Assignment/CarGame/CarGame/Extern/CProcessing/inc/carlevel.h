#pragma once
#include <cprocessing.h>
typedef struct Cardetail
{
	int car_Number;
	float car_Diameter;
	float car_PosX;
	float car_PosY;
	float radius_Collider;
	_Bool car_Selected;
	CP_Color triangle_Colour;
	CP_Color circle_Colour;
	int car_speed;
	float car_CurrentRotation;
}Cardetail;
typedef struct ProjectileInfo
{
	int projectile_Speed;
	int projectile_Size;
	float x_pos;
	float y_pos;
	float x_direction;
	float y_direction;
	float direction;
	CP_Color projectile_Colour;
	_Bool is_Active;
	float projectile_Lifetime;
}ProjectileInfo;

Cardetail Car[2];
ProjectileInfo car_Projectiles[100];

void SetButton();
void SpawnCar(int car_number, float diameter, int speed, CP_Color triangle_Colour, CP_Color Circle_Colour, float pos_x, float pos_y);
void DrawCar();
void ControlCar(Cardetail* car);
void DriveCar(Cardetail* car);
void SpawnProjectile(Cardetail* car, int index, CP_Color projectile_Colour);
void SetProjectile(int speed, int size);
void Car_Level_Init(void);
void Car_Level_Update(void);
void Car_Level_Exit(void);