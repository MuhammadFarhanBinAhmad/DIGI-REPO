/******************************************************************************/
/*!
\file		GameStateMgr.h
\author 	MuhammadFarhanBinAhmad(2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	February 02, 2023
\brief		Hold all the game state in the game
			GameStateMgrInit- Initialize all the game state and function pointers
			GameStateMgrUpdate - GameManager update function. Dictate which state is currently being
			run base on the current condition it state is in

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#ifndef CSD1130_GAME_STATE_MGR_H_
#define CSD1130_GAME_STATE_MGR_H_

// ---------------------------------------------------------------------------

#include "AEEngine.h"

// ---------------------------------------------------------------------------
// include the list of game states

#include "GameStateList.h"

typedef void (*FP)(void);

// ---------------------------------------------------------------------------
// externs

extern unsigned int gGameStateInit;
extern unsigned int gGameStateCurr;
extern unsigned int gGameStatePrev;
extern unsigned int gGameStateNext;

// ---------------------------------------------------------------------------

extern void (*GameStateLoad)();
extern void (*GameStateInit)();
extern void (*GameStateUpdate)();
extern void (*GameStateDraw)();
extern void (*GameStateFree)();
extern void (*GameStateUnload)();

// ---------------------------------------------------------------------------
// Function prototypes

// call this at the beginning and AFTER all game states are added to the manager
void GameStateMgrInit(unsigned int gameStateInit);

// update is used to set the function pointers
void GameStateMgrUpdate();

// ---------------------------------------------------------------------------

#endif