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
#include "Collider.h"
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
	CP_Engine_SetNextGameState(Collider_init,Collider_update, Collider_exit);
	CP_Engine_Run();
	return 0;
}
