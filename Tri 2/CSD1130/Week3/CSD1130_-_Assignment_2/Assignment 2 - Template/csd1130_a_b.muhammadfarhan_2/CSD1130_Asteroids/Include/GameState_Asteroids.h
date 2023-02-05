/******************************************************************************/
/*!
\file		GameObject.h
\author 	MuhammadFarhanBinAhmad(2200544)
\par    	email: b.muhammadfarhan@digipen.edu
\date   	February 02, 2023
\brief		Hold all 6 state in the game
			GameStateAsteroidsLoad- Load all needed assets and data
			GameStateAsteroidsInit- Initilize all needed variables and object being use in the game
			GameStateAsteroidsUpdate- Game Update Function. Handles all the physics,input etc.
			GameStateAsteroidsDraw- Game render function. Handles all the rendering
			GameStateAsteroidsFree- Remove all remaining objects instances and freeing their allocated memory.
			GameStateAsteroidsUnload- Unload all memory that was loaded in the game

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/

#ifndef CSD1130_GAME_STATE_PLAY_H_
#define CSD1130_GAME_STATE_PLAY_H_

// ---------------------------------------------------------------------------

void GameStateAsteroidsLoad(void);
void GameStateAsteroidsInit(void);
void GameStateAsteroidsUpdate(void);
void GameStateAsteroidsDraw(void);
void GameStateAsteroidsFree(void);
void GameStateAsteroidsUnload(void);

// ---------------------------------------------------------------------------



#endif // CSD1130_GAME_STATE_PLAY_H_


