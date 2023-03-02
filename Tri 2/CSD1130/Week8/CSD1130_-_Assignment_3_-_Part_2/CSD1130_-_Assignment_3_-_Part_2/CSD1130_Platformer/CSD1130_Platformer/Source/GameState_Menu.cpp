#include "main.h"
#include <iostream>
#include <fstream>
#include "GameState_Menu.h"

void GameStateMenuLoad(void)
{

}
void GameStateMenuInit(void)
{
	AEGfxSetBackgroundColor(0.f, 0.f, 0.f);
}
void GameStateMenuUpdate(void)
{
	if (AEInputCheckCurr(AEVK_Q))
	{
		gGameStateNext = GS_QUIT;
	}
	if (AEInputCheckCurr(AEVK_1))
	{
		gGameStateNext = GS_PLATFORM_LVL_1;
	}
	if (AEInputCheckCurr(AEVK_2))
	{
		gGameStateNext = GS_PLATFORM_LVL_2;
	}
}
void GameStateMenuDraw(void)
{
	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	sprintf_s(strBuffer, "Platformer");
	AEGfxPrint(font, strBuffer, -0.3f, .4f, 1.0f, 1.0f, 0.0f, 1.0f);
	sprintf_s(strBuffer, "Press '1' for Level 1");
	AEGfxPrint(font, strBuffer, -0.3f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	sprintf_s(strBuffer, "Press '2' for Level 2");
	AEGfxPrint(font, strBuffer, -0.3f, -.2f, 1.0f, 1.0f, 1.0f, 1.0f);
	sprintf_s(strBuffer, "Press 'Q' to Quit");
	AEGfxPrint(font, strBuffer, -0.3f, .2f, 1.0f, 1.0f, 1.0f, 1.0f);
}
void GameStateMenuFree(void)
{

}
void GameStateMenuUnload(void)
{

}