/*---------------------------------------------------------
 * file:	main.c
 * author:	[NAME]
 * email:	[DIGIPEN EMAIL ADDRESS]
* 
 * brief:	Main entry point for the sample project
			* of the CProcessing library
* 
 * documentation link:
 * https://inside.digipen.edu/main/GSDP:GAM100/CProcessing
* 
 * Copyright © 2020 DigiPen, All rights reserved.
* ---------------------------------------------------------*/
#include <stdio.h>
#include "cprocessing.h"


void GameInit(void);
void GameUpdate(void);
void GameExit(void);

/* Entry point */
int main(void)
{
    CP_System_SetWindowSize(800, 800);
    CP_System_SetFrameRate(60);
    CP_Engine_SetNextGameState(GameInit, GameUpdate, GameExit);
    CP_Engine_Run();
    return 0;
}
