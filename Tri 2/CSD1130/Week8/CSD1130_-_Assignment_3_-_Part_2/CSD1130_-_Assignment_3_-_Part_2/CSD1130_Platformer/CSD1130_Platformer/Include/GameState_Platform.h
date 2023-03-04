/******************************************************************************/
/*!
\file		GameState_Platform.h
\author 	Muhammad Farhan Bin Ahmad(ID: 2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	February 03, 2023
\brief

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#ifndef CSD1130_GAME_STATE_PLAY_H_
#define CSD1130_GAME_STATE_PLAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// ---------------------------------------------------------------------------

void GameStatePlatformLoad(void);
void GameStatePlatformInit(void);
void GameStatePlatformUpdate(void);
void GameStatePlatformDraw(void);
void GameStatePlatformFree(void);
void GameStatePlatformUnload(void);

// ---------------------------------------------------------------------------

#endif // CSD1130_GAME_STATE_PLAY_H_