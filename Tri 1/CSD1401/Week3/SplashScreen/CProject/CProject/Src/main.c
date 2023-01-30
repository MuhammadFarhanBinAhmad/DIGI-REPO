#include "cprocessing.h"
#include "splashscreen.h"

CP_Image logo;
int value_Alpha = 0;

void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
	CP_System_SetFrameRate(60.0f);
}

void game_update(void)
{
	value_Alpha += CP_System_GetDt() *150;//cp_system_getdt is like time.delta
	//Set alpha value for logo
	value_Alpha = value_Alpha % 255;
	CP_Image_Draw(logo, 0.0f, 0.0f, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), value_Alpha);

	//create circle and change colour value for circle
	CP_Color circle_Colour = CP_Color_Create(0, value_Alpha, 0, 255);
	CP_Settings_Fill(circle_Colour);
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f);

	CP_Graphics_ClearBackground(CP_Color_Create(255,255,255,255));
	
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
}

void game_exit(void)
{
	CP_Image_Free(&logo);
}
int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}