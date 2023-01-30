#include <cprocessing.h>
//#include <carlevel.h>
#include <utils.h>
#include <mainmenu.h>

void Main_Menu_Init()
{

	CP_System_SetWindowSize(500, 500);
	/// <Button Info>
	/// Set up Button infomation(Points,colour)
	/// <Button Info>
	button[0].pointmost_Left = -100;
	button[0].pointmost_Right = 100;
	button[0].pointmost_Top = -100;
	button[0].pointmost_Bottom = 0;
	button[0].input = 0;
	button[1].pointmost_Left = -100;
	button[1].pointmost_Right = 100;
	button[1].pointmost_Top = 50;
	button[1].pointmost_Bottom = 150;
	button[1].input = 1;
	for (int i = 0; i < 2; i++)
	{
		/*
			Button making instruction
			x1 - most left point
			x2 - most right point
			y3 - top point
			y1 - bottom point
		*/
		button[i].x1 = CENTER_X + button[i].pointmost_Left;
		button[i].y1 = CENTER_Y + button[i].pointmost_Bottom;
		button[i].x2 = CENTER_X + button[i].pointmost_Right;
		button[i].y2 = CENTER_Y + button[i].pointmost_Bottom;
		button[i].x3 = CENTER_X + button[i].pointmost_Right;
		button[i].y3 = CENTER_Y + button[i].pointmost_Top;
		button[i].x4 = CENTER_X + button[i].pointmost_Left;
		button[i].y4 = CENTER_Y + button[i].pointmost_Top;
		button[i].input = i;
	}
}

void Main_Menu_Update()
{

	CP_Graphics_ClearBackground(BLACK);
	CreateButton(button[0], "Play",WHITE,35.f, CENTER_X -25.f, button[0].y1-25.f,BLUE);
	CreateButton(button[1], "Exit",WHITE,35.f, CENTER_X -25.f, button[1].y1-25.f,GREEN);
	if (CP_Input_MouseClicked())
	{
		for (int i = 0; i < 2; i++)
		{
			//Check which button is being click
			switch (AreaClicked(CP_Input_GetMouseX(), CP_Input_GetMouseY(), button[i]))
			{
				case 0:
				{
					//CP_Engine_SetNextGameState(test_init, test_update, test_exit);

					break;
				}
				case 1:
				{
					CP_Engine_Terminate();
					break;
				}
			}
		}
	}
	CP_Settings_Fill(RED);
	CP_Settings_TextSize(35.0f);
	CP_Font_DrawTextBox("CAR GAME", CENTER_X-60.f, CENTER_Y-200.f, 150);
}

void Main_Menu_Exit()
{

}