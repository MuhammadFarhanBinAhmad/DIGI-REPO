#include "cprocessing.h"

CP_Image logo;

void game_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_System_SetWindowSize(1920, 1440);
	CP_Image_Draw(logo, 0.0f, 0.0f, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), 255);
}

void game_update(void)
{
	CP_Graphics_ClearBackground(CP_Color_Create(255,255,255,255));
	CP_Image_Draw(logo, 0.0f, 0.0f, (float)CP_Image_GetWidth(logo), (float)CP_Image_GetHeight(logo), 255);
	//CP_Image_Draw(logo, CP_System_GetWindowWidth() / 2, CP_System_GetWindowHeight() / 2, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), 255);
	if (CP_Input_KeyDown(KEY_B))
	{

	}
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