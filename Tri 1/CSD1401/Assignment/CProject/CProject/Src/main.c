#include "cprocessing.h"
#include "Game.h"
#include <stdbool.h>


#define WINDOWHEIGHT 1080
#define WINDOWWIDTH 1920

struct CellInfo
{
	BOOLEAN is_Alive;
	float x_pos;
	float y_pos;
};
struct SpaceInfo
{
	float x_pos;
	float y_pos;
	bool is_Occupied;
};

struct SpaceInfo the_Spaceinfo[50][50];

void CreateGrid()
{
	int x;
	int y;
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	for (x = 0; x < 50; x++)
	{
		for (y = 0; y < 50; y++)
		{
			the_Spaceinfo[x][y];
			the_Spaceinfo[x][y].x_pos = x * 10;
			the_Spaceinfo[x][y].y_pos = y * 10;
		}
	}
}

void Print()
{
	CP_Font_DrawTextBox("Hit", 25, 0, 10);
}
void game_init(void)
{
	CP_System_SetWindowSize(WINDOWWIDTH,WINDOWHEIGHT);
}
void game_update(void)
{


}

void game_exit(void)
{
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run();
	return 0;
}
