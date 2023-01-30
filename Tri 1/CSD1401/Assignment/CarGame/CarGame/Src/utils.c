#include <cprocessing.h>
#include <utils.h>
#include "mainmenu.h"
#include "carlevel.h"
#include "math.h"

void CreateButton(ButtonInfo button, char *text, CP_Color text_Colour, float text_Size, float text_PosX, float text_PosY,CP_Color button_Colour)
{
	CP_Settings_Fill(button_Colour);
	CP_Graphics_DrawQuad(button.x1, button.y1,    
		button.x2, button.y2,    
		button.x3, button.y3,   
		button.x4, button.y4);
	CP_Settings_Fill(text_Colour);
	CP_Settings_TextSize(text_Size);
	button.text = text;
	CP_Font_DrawTextBox(text, text_PosX, text_PosY, 150);
}
int AreaClicked(float click_x, float click_y, ButtonInfo BI)
{
	if (CP_Input_MouseClicked())
	{
		if (click_x >= BI.x1 && click_x <= BI.x2 && click_y >= BI.y3 && click_y <= BI.y1)
		{
			return BI.input;
		}
	}
	return 0;
}
CP_Vector AngleToVector(float radian_angle)
{
	float x = (float)sin(radian_angle);
	float y = (float)cos(radian_angle);
    CP_Vector ret = CP_Vector_Set(-x,y);
    return ret;
}