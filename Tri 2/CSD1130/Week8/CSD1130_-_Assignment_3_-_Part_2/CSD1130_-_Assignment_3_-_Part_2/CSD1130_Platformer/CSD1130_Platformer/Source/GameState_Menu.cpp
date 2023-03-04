/******************************************************************************/
/*!
\file		GameState_Menu.cpp
\author 	Muhammad Farhan Bin Ahmad(ID: 2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	March 03, 2023
\brief

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "main.h"
#include <iostream>
#include <fstream>
#include "GameState_Menu.h"

void GameStateMenuLoad(void)
{

}
void GameStateMenuInit(void)
{
	//Set default BG to Black
	AEGfxSetBackgroundColor(0.f, 0.f, 0.f);
}
void GameStateMenuUpdate(void)
{
	//Set Condition to play certain scene
	if (AEInputCheckCurr(AEVK_Q))
	{
		//Quit Game
		gGameStateNext = GS_QUIT;
	}
	if (AEInputCheckCurr(AEVK_1))
	{
		//Go Level 1
		gGameStateNext = GS_PLATFORM_LVL_1;
	}
	if (AEInputCheckCurr(AEVK_2))
	{
		//Go Level 2
		gGameStateNext = GS_PLATFORM_LVL_2;
	}
}
void GameStateMenuDraw(void)
{
	char strBuffer[100];
	memset(strBuffer, 0, 100 * sizeof(char));
	AEGfxSetBlendMode(AE_GFX_BM_BLEND);

	//Set text for Main Menu
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