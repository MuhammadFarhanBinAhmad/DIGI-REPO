#include "cprocessing.h"
#include "splashscreen.h"

CP_Image logo;
int value_Alpha = 0;

void splash_screen_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
	CP_System_SetFrameRate(60.0f);
}

void splash_screen_update(void)
{
	value_Alpha += CP_System_GetDt() * 100;//cp_system_getdt is like time.delta
//Set alpha value for logo
	if (value_Alpha > 255)
	{
		value_Alpha = 0;
	}
	CP_Image_Draw(logo, 0.0f, 0.0f, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), (int)value_Alpha);

	//create circle and change colour value for circle
	CP_Color circle_Colour = CP_Color_Create(0, value_Alpha, 0, 255);
	CP_Settings_Fill(circle_Colour);
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f);

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
}

void splash_screen_exit(void)
{

}