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
#include "pch.h"
#include "Input.h"
#include "GameStateManager.h"

int Level2_Counter{ 0 }, Level2_Live{0};

void Level2_Load()
{
	std::fstream file_Live2("Level2_Lives.txt", std::ios_base::in);
	//Check if file is open
	if (!file_Live2)
	{
		printf("File fail to open\n");
	}
	//Get data from file
	file_Live2 >> Level2_Live;
	printf("Level2:Load\n");

	//CLOSEFILE
	file_Live2.close();
}

void Level2_Initialize()
{
	//READFILE
	std::fstream file_Counterl2("Level2_Counter.txt", std::ios_base::in);
	//Check if file open
	if (!file_Counterl2)
	{
		printf("File fail to open\n");
	}
	//GETDATA
	file_Counterl2 >> Level2_Counter;
	printf("Level2:Initialize\n");

	//CLOSEFILE
	file_Counterl2.close();
}

void Level2_Update()
{

	if (--Level2_Counter <= 0)
	{
		//Check current life
		if (--Level2_Live > 0)
		{
			next = GS_RESTART;
		}
		else
		{
			next = GS_QUIT;
		}
	}
	printf("Level2:Update\n");
}

void Level2_Draw()
{
	printf("Level2:Draw\n");
}

void Level2_Free()
{
	printf("Level2:Free\n");
}

void Level2_Unload()
{
	printf("Level2:Unload\n");
}