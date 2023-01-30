//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "mainmenu.h"
#include "carlevel.h"
#include "utils.h"

void game_init(void)
{

}
void game_update(void)
{


}
void game_exit(void)
{

}
int main(void)
{
	CP_Engine_SetNextGameState(Car_Level_Init, Car_Level_Update, Car_Level_Exit);
	CP_Engine_Run();
	return 0;
}
