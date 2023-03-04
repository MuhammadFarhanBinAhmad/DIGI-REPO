/******************************************************************************/
/*!
\file		GameStateMgr.cpp
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

// ---------------------------------------------------------------------------
// globals

// variables to keep track the current, previous and next game state
unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

// pointer to functions for game state life cycles functions
void (*GameStateLoad)()		= 0;
void (*GameStateInit)()		= 0;
void (*GameStateUpdate)()	= 0;
void (*GameStateDraw)()		= 0;
void (*GameStateFree)()		= 0;
void (*GameStateUnload)()	= 0;

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStateMgrInit(unsigned int gameStateInit)
{
	// set the initial game state
	gGameStateInit = gameStateInit;

	// reset the current, previoud and next game
	gGameStateCurr = 
	gGameStatePrev = 
	gGameStateNext = gGameStateInit;

	// call the update to set the function pointers
	GameStateMgrUpdate();
}

/******************************************************************************/
/*!

*/
/******************************************************************************/
void GameStateMgrUpdate()
{
	if ((gGameStateCurr == GS_RESTART) || (gGameStateCurr == GS_QUIT))
		return;

	switch (gGameStateCurr)
	{
	case GS_MENU:
		GameStateLoad = GameStateMenuLoad;
		GameStateInit = GameStateMenuInit;
		GameStateUpdate = GameStateMenuUpdate;
		GameStateDraw = GameStateMenuDraw;
		GameStateFree = GameStateMenuFree;
		GameStateUnload = GameStateMenuUnload;
		break;
	//USE GAMESTATEPLATFORM INSTEAD OF MAKING ANOTHER FILE.JUST CHANGE/RESET STATS 
	case GS_PLATFORM_LVL_1:
		GameStateLoad	= GameStatePlatformLoad;
		GameStateInit	= GameStatePlatformInit;
		GameStateUpdate	= GameStatePlatformUpdate;
		GameStateDraw	= GameStatePlatformDraw;
		GameStateFree	= GameStatePlatformFree;
		GameStateUnload	= GameStatePlatformUnload;
		break;
	case GS_PLATFORM_LVL_2:
		GameStateLoad = GameStatePlatformLoad;
		GameStateInit = GameStatePlatformInit;
		GameStateUpdate = GameStatePlatformUpdate;
		GameStateDraw = GameStatePlatformDraw;
		GameStateFree = GameStatePlatformFree;
		GameStateUnload = GameStatePlatformUnload;
		break;
	default:
		AE_FATAL_ERROR("invalid state!!");
	}
}
