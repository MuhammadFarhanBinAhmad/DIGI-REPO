/* Start Header ************************************************************************/
/*!
\file <csd1130_gsm.cpp>
\author <Muhammad Farhan Bin Ahmad,b.muhammadfarhan,2200544>
\par <b.muhammadfarhan@digipen.edu>
\date <Jan 13,2023>
\brief
// <Function Brief>
/// Level1_Load - Grab all necessary data from file(render material and save file if available)
/// Level1_Initialize - Initialize all needed variables and data
/// Level1_Update - Game Update function.Update state of game depending of game input,time,gameplay etc.s
/// Level1_Draw - Render graphics and visual of game
/// Level1_Free - Clean up state of current level. Prepare for either level to be restarted or data to be initialze again
/// Level1_Unload - Call when the the state is to be terminated. Use to dumb data back
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

int Level1_Counter{ 0 };

void Level1_Load()
{
	//READFILE
	std::fstream file_Level1("Level1_Counter.txt", std::ios_base::in);
	//Check if file open
	if (!file_Level1)
	{
		printf("File fail to open\n");
	}
	//GETDATA
	file_Level1 >> Level1_Counter;

	printf("Level1:Load\n");

	//CLOSEFILE
	file_Level1.close();

}

void Level1_Initialize()
{
	printf("Level1:Initialize\n");
}

void Level1_Update()
{
	if (--Level1_Counter <= 0)
	{
		next = GS_LEVEL2;
	}
	printf("Level1:Update\n");
}

void Level1_Draw()
{
	printf("Level1:Draw\n");
}

void Level1_Free()
{
	printf("Level1:Free\n");
}

void Level1_Unload()
{
	printf("Level1:Unload\n");
}