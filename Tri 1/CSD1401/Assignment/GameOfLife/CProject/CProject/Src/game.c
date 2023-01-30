#include "cprocessing.h"
#include <stdio.h>
#define BLACK CP_Color_Create(0, 0, 0, 255)
#define WHITE CP_Color_Create(255, 255, 255, 255)
#define RED CP_Color_Create(255, 0, 0, 255)
#define CLEAR CP_Color_Create(0, 0, 0, 0)

#define WINDOW_WIDTH CP_System_GetWindowWidth()
#define WINDOW_HEIGHT CP_System_GetWindowHeight()

int x_Grid;
int y_Grid;
float width=10;
float height =10;
float cell_Size = 10;

enum GameState
{
	Pause,Edit,AutoPlay
};

struct SpaceInfo
{
	float x_pos;
	float y_pos;
	int total_Neighbour;
	_Bool is_Alive;
};


enum GameState State;
struct SpaceInfo the_Spaceinfo[50][50];

void CreateGrid()
{

	//create grid
	for (x_Grid = 0; x_Grid < 50; x_Grid++)
	{
		for (y_Grid = 0; y_Grid < 50; y_Grid++)
		{
			the_Spaceinfo[x_Grid][y_Grid].x_pos = (float)x_Grid * width;
			the_Spaceinfo[x_Grid][y_Grid].y_pos = (float)y_Grid * height;
		}
	}

}
void KillCell(int x_Grid, int y_Grid)
{
	the_Spaceinfo[x_Grid][y_Grid].is_Alive = 0;
	CP_Settings_Fill(BLACK);
	CP_Graphics_DrawRect(the_Spaceinfo[x_Grid][y_Grid].x_pos, the_Spaceinfo[x_Grid][y_Grid].y_pos, cell_Size, cell_Size);
}
void SpawnCell(int x_Grid, int y_Grid)
{
	the_Spaceinfo[x_Grid][y_Grid].is_Alive = 1;
	CP_Settings_Fill(WHITE);
	CP_Graphics_DrawRect(the_Spaceinfo[x_Grid][y_Grid].x_pos, the_Spaceinfo[x_Grid][y_Grid].y_pos, cell_Size, cell_Size);
}
void CheckCellState(int x_Grid, int y_Grid)
{
	//check to kill cell
	if (the_Spaceinfo[x_Grid][y_Grid].is_Alive == 1)
	{
		if (the_Spaceinfo[x_Grid][y_Grid].total_Neighbour < 2 || the_Spaceinfo[x_Grid][y_Grid].total_Neighbour > 3)
		{
			KillCell(x_Grid, y_Grid);
		}
	}
	//check to spawn cell
	else if (the_Spaceinfo[x_Grid][y_Grid].is_Alive == 0)
	{
		if (the_Spaceinfo[x_Grid][y_Grid].total_Neighbour == 3)
		{
			SpawnCell(x_Grid, y_Grid);
		}
	}
	the_Spaceinfo[x_Grid][y_Grid].total_Neighbour = 0;//reset neighbour count after every cycle
}
void CheckCellNeighbour()
{
	//Check all direction
	for (x_Grid = 0; x_Grid < 50; ++x_Grid)
	{
		for (y_Grid = 0; y_Grid < 50; ++y_Grid)
		{
			if (x_Grid - 1 > 0 && y_Grid - 1 > 0)
			{
				if (the_Spaceinfo[x_Grid + 1][y_Grid].is_Alive == 1)//EAST
				{
					the_Spaceinfo[x_Grid][y_Grid].total_Neighbour++;
				}
				if (the_Spaceinfo[x_Grid - 1][y_Grid].is_Alive == 1)//WEST
				{
					the_Spaceinfo[x_Grid][y_Grid].total_Neighbour++;
				}
				if (the_Spaceinfo[x_Grid][y_Grid + 1].is_Alive == 1)//NORTH
				{
					the_Spaceinfo[x_Grid][y_Grid].total_Neighbour++;
				}
				if (the_Spaceinfo[x_Grid][y_Grid - 1].is_Alive == 1)//SOUTH
				{
					the_Spaceinfo[x_Grid][y_Grid].total_Neighbour++;
				}
				if (the_Spaceinfo[x_Grid + 1][y_Grid + 1].is_Alive == 1)//NORTHEAST
				{
					the_Spaceinfo[x_Grid][y_Grid].total_Neighbour++;
				}
				if (the_Spaceinfo[x_Grid + 1][y_Grid - 1].is_Alive == 1)//SOUTHEAST
				{
					the_Spaceinfo[x_Grid][y_Grid].total_Neighbour++;
				}
				if (the_Spaceinfo[x_Grid - 1][y_Grid + 1].is_Alive == 1)//NORTHWEST
				{
					the_Spaceinfo[x_Grid][y_Grid].total_Neighbour++;
				}
				if (the_Spaceinfo[x_Grid - 1][y_Grid - 1].is_Alive == 1)//SOUTHWEST
				{
					the_Spaceinfo[x_Grid][y_Grid].total_Neighbour++;
				}
			}
		}
	}
	//check all cell current state
	for (x_Grid = 0; x_Grid < 50; x_Grid++)
	{
		for (y_Grid = 0; y_Grid < 50; y_Grid++)
		{
			CheckCellState(x_Grid, y_Grid);
		}
	}
}
void CheckSquare(float x_pos, float y_pos)
{
	//find which x and y grid the mouse is currently in
	int x = (int)x_pos / 10;
	int y = (int)y_pos / 10;
	if (CP_Input_GetMouseX() < 500 && CP_Input_GetMouseY() < 500)
	{
		//decide what the next life for the space will be
		if (the_Spaceinfo[x][y].is_Alive == 1)
		{
			KillCell(x, y);
		}
		else if (the_Spaceinfo[x][y].is_Alive == 0)
		{
			SpawnCell(x, y);
		}
	}
}

void game_init(void)
{
	CP_System_SetWindowSize(500,600);
	CP_Graphics_ClearBackground(BLACK);
	State = Edit;
	CreateGrid();
	//Draw text
	CP_Font_DrawTextBox("'A' - AutoPlay", 0, 355, 100);
	CP_Font_DrawTextBox("'P' - NextLife", 0, 370, 100);
	CP_Font_DrawTextBox("'Q' - Quit", 0, 385, 100);
	CP_Settings_TextSize(25.f);
	CP_Font_DrawTextBox("Welcome to the Game of Life", 150, 365, 200);

}
void game_update(void)
{

	switch (State)
	{
	case Pause:

		if (CP_Input_KeyDown(KEY_Q))
		{
			CP_Engine_Terminate();
		}
		if (CP_Input_KeyTriggered(KEY_ESCAPE))
		{
			State = Edit;
		}
		break;
	case Edit:
		
		if (CP_System_GetFrameRate() < 60.0f)
		{
			CP_System_SetFrameRate(60.f);
		}
		if (CP_Input_MouseClicked())
		{
			CheckSquare(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		}
		if (CP_Input_KeyTriggered(KEY_P))
		{
			CheckCellNeighbour();
		}
		if (CP_Input_KeyTriggered(KEY_A))
		{
			State = AutoPlay;
		}
		if (CP_Input_KeyTriggered(KEY_ESCAPE))
		{
			State = Pause;
		}
		if (CP_Input_KeyDown(KEY_Q))
		{
			CP_Engine_Terminate();
		}
		break;
	case AutoPlay:
		CP_System_SetFrameRate(10.0f);
		CheckCellNeighbour();
		if (CP_Input_KeyTriggered(KEY_A))
		{
			State = Edit;
		}
		break;
	}
}

void game_exit(void)
{
}
//Script wont compile because i forgot to remove int main(void).I really hate myself.
//I apologise for my mistake. I hope I can compensate with gam100 team project