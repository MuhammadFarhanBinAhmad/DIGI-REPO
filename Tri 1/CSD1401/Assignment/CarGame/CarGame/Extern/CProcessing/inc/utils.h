#pragma once

#include "carlevel.h"

//Colours
#define RED CP_Color_Create(255, 0, 0, 255)
#define BLUE CP_Color_Create(0, 0, 255, 255)
#define GREEN CP_Color_Create(0, 255, 0, 255)
#define YELLOW CP_Color_Create(255,255,0,255)
#define PURPLE CP_Color_Create(255,0,255,255)
#define AQUA CP_Color_Create(0,255,255,255)
#define BLACK CP_Color_Create(0, 0, 0, 255)
#define WHITE CP_Color_Create(255,255,255,255)
#define GREY CP_Color_Create(155,155,155,255)
//Centerpoint
#define CENTER_X CP_System_GetWindowWidth()/2
#define CENTER_Y CP_System_GetWindowHeight()/2
//Mouse position
#define MOUSE_X_POS CP_Input_GetMouseX()
#define MOUSE_Y_POS CP_Input_GetMouseY()

#define TIMER CP_System_GetDt() * 60
//float pie_value = 3.14f;

typedef struct ButtonInfo
{
	float x1, x2, x3, x4;
	float y1, y2, y3, y4;
	float pointmost_Left;
	float pointmost_Right;
	float pointmost_Top;
	float pointmost_Bottom;
	float text_PosX;
	float text_PosY;
	int input;
	char *text;
	/// <summary>
	/// input = 0 - Gamemenu
	/// input = 1 - ExitGame
	/// </summary>
	CP_Color button_Colour;
}ButtonInfo;
ButtonInfo button[2];
typedef struct TargetInfo
{
	float target_Health;
	float target_Diameter;
	float x_pos, y_pos;
	float top_x, top_y, bottom_x, bottom_y;
	CP_Color target_Colour;
	_Bool SetActive;

}TargetInfo;
_Bool ButtonClick;

TargetInfo Targets[5];

void CreateButton(ButtonInfo BI,char *text,CP_Color text_Colour,float text_Size, float text_PosX, float text_PosY,CP_Color button_Colour);
int AreaClicked(float click_x, float click_y,ButtonInfo BI);
void IsCarClickedIsCarClicked(float click_x, float click_y);
void SetTarget(CP_Color colour,float health, float diameter);
void TargetCollider(TargetInfo T);
union CP_Vector AngleToVector(float radian_angle);