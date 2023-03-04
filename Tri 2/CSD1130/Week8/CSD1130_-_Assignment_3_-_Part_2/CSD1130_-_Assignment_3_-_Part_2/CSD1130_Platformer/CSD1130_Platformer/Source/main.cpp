/******************************************************************************/
/*!
\file		main.cpp
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
#include <memory>


// ---------------------------------------------------------------------------
// Globals
float	 g_dt;
double	 g_appTime;

char font;
/******************************************************************************/
/*!
	Starting point of the application
*/
/******************************************************************************/
int WINAPI WinMain(HINSTANCE instanceH, HINSTANCE prevInstanceH, LPSTR command_line, int show)
{
	// Initialize the system
	AESysInit (instanceH, show, 800, 600, 1, 60, false, NULL);
	
	//Create your font here, and use it for all your levels
	font = AEGfxCreateFont("..//Resources//Fonts//Arial Italic.ttf",20);

	//MY BEST FRIEND AND WORST ENEMY :)
	// Enable run-time memory check for debug builds.
	//#if defined(DEBUG) | defined(_DEBUG)
	//	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//#endif

	GameStateMgrInit(GS_MENU);

	while(gGameStateCurr != GS_QUIT)
	{
		// reset the system modules
		AESysReset();

		// If not restarting, load the gamestate
		if(gGameStateCurr != GS_RESTART)
		{
			GameStateMgrUpdate();
			GameStateLoad();
		}
		else
			gGameStateNext = gGameStateCurr = gGameStatePrev;

		// Initialize the gamestate
		GameStateInit();

		while(gGameStateCurr == gGameStateNext)
		{
			AESysFrameStart();

			AEInputUpdate();

			GameStateUpdate();

			GameStateDraw();
			
			AESysFrameEnd();


			g_dt = (f32)AEFrameRateControllerGetFrameTime();
			
			//capping the game loop - delta time, to 1/60.0f
			if (g_dt > 0.01667f)	//0.01667f = 1/60.0f
				g_dt = 0.01667f;
				
			g_appTime += g_dt;
		}
		
		GameStateFree();

		if(gGameStateNext != GS_RESTART)
			GameStateUnload();

		gGameStatePrev = gGameStateCurr;
		gGameStateCurr = gGameStateNext;
	}

	//free you font here
	AEGfxDestroyFont(font);
	// free the system
	AESysExit();
}