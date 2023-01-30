/* Start Header ************************************************************************/
/*!
\file <csd1130_gsm.cpp>
\author <Muhammad Farhan Bin Ahmad,b.muhammadfarhan,2200544>
\par <b.muhammadfarhan@digipen.edu>
\date <Jan 13,2023>
\brief
/// <Function Brief>
/// Level2_Load - Grab all necessary data from file(render material and save file if available)
/// Level2_Initialize - Initialize all needed variables and data
/// Level2_Update - Game Update function.Update state of game depending of game input,time,gameplay etc.s
/// Level2_Draw - Render graphics and visual of game
/// Level2_Free - Clean up state of current level. Prepare for either level to be restarted or data to be initialze again
/// Level2_Unload - Call when the the state is to be terminated. Use to dumb data back
/// <Function Brief>
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
*/
/* End Header **************************************************************************/

#pragma once

void Level2_Load();

void Level2_Initialize();

void Level2_Update();

void Level2_Draw();

void Level2_Free();

void Level2_Unload();