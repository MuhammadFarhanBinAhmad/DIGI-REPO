
#include "carlevel.h"
#include "cprocessing.h"
#include "utils.h"
#include "mainmenu.h"
#include "math.h"
#include <time.h>

Cardetail* current_car;

float firerate = 20;
float current_FireTime = 0;;

int window_Width = 1000, window_Height = 1000;

enum State
{
	Play,Pause
};
enum State GAMESTATE;
void Car_Level_Init()
{
	CP_System_SetWindowSize(window_Width, window_Height);

	GAMESTATE = Play;

	SpawnCar(0, 50.f, 5,RED, BLACK, 200, 100);
	SpawnCar(1, 65.f, 10, BLUE, BLACK, 150, 200);
	SpawnCar(2, 80.f, 15, GREEN, BLACK, 300, 400);
	SetButton();
	//Spawn car
	if (current_car == NULL)
	{
		current_car = &Car[0];
	}
	else
	{
		current_car = &Car[current_car->car_Number];
	}
	//Set object pool for projectile
	SetProjectile(2, 20);
	//SetTarget(RED, 100.f, 20.f);
}
void SetButton()
{
	//Exitbutton position
	button[0].pointmost_Left = -100;
	button[0].pointmost_Right = 100;
	button[0].pointmost_Top = -60;
	button[0].pointmost_Bottom = 0;
	button[0].x1 = CENTER_X + button[0].pointmost_Left;
	button[0].y1 = CENTER_Y + button[0].pointmost_Bottom;
	button[0].x2 = CENTER_X + button[0].pointmost_Right;
	button[0].y2 = CENTER_Y + button[0].pointmost_Bottom;
	button[0].x3 = CENTER_X + button[0].pointmost_Right;
	button[0].y3 = CENTER_Y + button[0].pointmost_Top;
	button[0].x4 = CENTER_X + button[0].pointmost_Left;
	button[0].y4 = CENTER_Y + button[0].pointmost_Top;
	button[0].input = 0;
	//ResumeButton
	button[1].pointmost_Left = -100;
	button[1].pointmost_Right = 100;
	button[1].pointmost_Top = 25;
	button[1].pointmost_Bottom = 85;
	button[1].x1 = CENTER_X + button[1].pointmost_Left;
	button[1].y1 = CENTER_Y + button[1].pointmost_Bottom;
	button[1].x2 = CENTER_X + button[1].pointmost_Right;
	button[1].y2 = CENTER_Y + button[1].pointmost_Bottom;
	button[1].x3 = CENTER_X + button[1].pointmost_Right;
	button[1].y3 = CENTER_Y + button[1].pointmost_Top;
	button[1].x4 = CENTER_X + button[1].pointmost_Left;
	button[1].y4 = CENTER_Y + button[1].pointmost_Top;
	button[1].input = 1;
}
/// <CAR FUNCTIONS>
void SpawnCar(int car_number, float diameter, int speed, CP_Color triangle_Colour, CP_Color Circle_Colour, float pos_x, float pos_y)
{
	//Set up car details
	Car[car_number].car_Number = car_number;
	Car[car_number].car_Diameter = diameter;
	Car[car_number].car_PosX = pos_x;
	Car[car_number].car_PosY = pos_y;
	Car[car_number].car_speed = speed;
	Car[car_number].car_CurrentRotation = 0;
	//Drawing Cicle
	Car[car_number].circle_Colour =Circle_Colour;
	CP_Settings_Fill(Car[car_number].circle_Colour);
	CP_Graphics_DrawCircle(Car[car_number].car_PosX, Car[car_number].car_PosY, Car[car_number].car_Diameter);
	//Drawing Triangle
	Car[car_number].triangle_Colour = triangle_Colour;
	CP_Settings_Fill(Car[car_number].triangle_Colour);
	CP_Graphics_DrawTriangleAdvanced
	(Car[car_number].car_PosX - (Car[car_number].car_Diameter) / 2, Car[car_number].car_PosY + (Car[car_number].car_Diameter / 2)
		, Car[car_number].car_PosX, Car[car_number].car_PosY - (Car[car_number].car_Diameter / 2)
		, Car[car_number].car_PosX + (Car[car_number].car_Diameter / 2), Car[car_number].car_PosY
		, Car[car_number].car_CurrentRotation);

}
void DrawCar()
{
	for (int i = 0; i  <= 2; i++)
	{
		if (!Car[i].car_Selected)
		{
			CP_Settings_Fill(Car[i].circle_Colour);
			CP_Graphics_DrawCircle(Car[i].car_PosX, Car[i].car_PosY, Car[i].car_Diameter);
			CP_Settings_Fill(Car[i].triangle_Colour);
			CP_Graphics_DrawTriangleAdvanced(Car[i].car_PosX - (Car[i].car_Diameter / 2), Car[i].car_PosY
				, Car[i].car_PosX + (Car[i].car_Diameter / 2), Car[i].car_PosY
				, Car[i].car_PosX, Car[i].car_PosY + (Car[i].car_Diameter / 2)
				, Car[i].car_CurrentRotation);
		}
	}
}
void IsCarClicked(float click_x, float click_y)
{
	if (CP_Input_MouseClicked())
	{
		for (int i = 0; i < 3; i++)
		{
			//Check all vehicle if there are selected
			if (click_x >= Car[i].car_PosX - Car[i].car_Diameter &&
				click_x <= Car[i].car_PosX + Car[i].car_Diameter &&
				click_y >= Car[i].car_PosY - Car[i].car_Diameter &&
				click_y <= Car[i].car_PosY + Car[i].car_Diameter)
			{
				current_car->car_Selected = FALSE;
				current_car = &Car[i];
			}
		}
	}
}
void ControlCar(Cardetail* car_Number)
{
	//Front and back control
	if (CP_Input_KeyDown(KEY_W))
	{
		float radian_rot = car_Number->car_CurrentRotation;
		radian_rot *= 3.14f / 180;
		CP_Vector vec = AngleToVector(radian_rot);
		car_Number->car_PosX += vec.x * car_Number->car_speed;
		car_Number->car_PosY += vec.y* car_Number->car_speed;
	}
	if (CP_Input_KeyDown(KEY_S))
	{
		float radian_rot = car_Number->car_CurrentRotation;
		radian_rot *=  3.14f/ 180;
		CP_Vector vec = AngleToVector(radian_rot);
		car_Number->car_PosX -= vec.x* car_Number->car_speed;
		car_Number->car_PosY -= vec.y* car_Number->car_speed;
	}
	//Rotation
	if (CP_Input_KeyDown(KEY_D))
	{
		car_Number->car_CurrentRotation += car_Number->car_speed;
	}
	if (CP_Input_KeyDown(KEY_A))
	{
		car_Number->car_CurrentRotation -= car_Number->car_speed;
	}
	DriveCar(car_Number);
}
void DriveCar(Cardetail* current_car)
{
	//Draw car with updated movement values
	current_car->car_Selected = TRUE;
	CP_Settings_Fill(WHITE);
	CP_Graphics_DrawCircle(current_car->car_PosX, current_car->car_PosY, current_car->car_Diameter);
	CP_Settings_Fill(current_car->triangle_Colour);
	CP_Graphics_DrawTriangleAdvanced(current_car->car_PosX - (current_car->car_Diameter / 2), current_car->car_PosY
		, current_car->car_PosX + (current_car->car_Diameter / 2), current_car->car_PosY
		, current_car->car_PosX, current_car->car_PosY + (current_car->car_Diameter / 2)
		, current_car->car_CurrentRotation);
}
/// <CAR FUNCTIONS>

/// <PROJECTILE FUNCTIONS>
void SetProjectile(int speed, int size)
{
	for (int i = 0; i < 100; i++)
	{
		car_Projectiles[i].projectile_Speed = speed;
		car_Projectiles[i].projectile_Size = size;
		car_Projectiles[i].is_Active = FALSE;
	}
}
void SpawnProjectile(Cardetail* car, int index,CP_Color projectile_Colour)
{
	float x ;//x vector direction
	float y ;//y vector direction
	//distance
	float d;
	float normal_x;
	float normal_y;
	if (car_Projectiles[index].is_Active == FALSE)
	{
		//Set direction for projectile base on mouse position
		x = (MOUSE_X_POS - car->car_PosX);
		y = (MOUSE_Y_POS - car->car_PosY);
		d = (float)sqrt(pow(x,2) + pow(y,2));
		//normalize vector
		normal_x = x / d;
		normal_y = y / d;
		car_Projectiles[index].x_direction = normal_x;
		car_Projectiles[index].y_direction = normal_y;
		car_Projectiles[index].is_Active = TRUE;
	}
	car_Projectiles[index].x_pos = car->car_PosX;
	car_Projectiles[index].y_pos = car->car_PosY;
	car_Projectiles[index].projectile_Colour = projectile_Colour;

}
//Draw car projectiles
void DrawProjectile(int index)
{
	CP_Settings_Fill(car_Projectiles[index].projectile_Colour);
	CP_Graphics_DrawCircle(car_Projectiles[index].x_pos += car_Projectiles[index].x_direction*5, car_Projectiles[index].y_pos += car_Projectiles[index].y_direction*5, 20);
}
void CheckProjectile(int index)
{
	car_Projectiles[index].projectile_Lifetime += TIMER;//projectile timer
	//If lifespan expires, reset timer and life status
	if (car_Projectiles[index].projectile_Lifetime > 300)
	{
		car_Projectiles[index].is_Active = FALSE;
		car_Projectiles[index].projectile_Lifetime = 0;
	}
}
/// <PROJECTILE FUNCTIONS>

/// <Targets>
/*void SetTarget(CP_Color colour, float health, float diameter)
{
	srand(time(0));
	for (int i = 0; i < 5; i++)
	{
		Targets[i].target_Health = health;
		Targets[i].target_Diameter = diameter;
		Targets[i].target_Colour = RED;
		//Set random pos
		int random_x = (rand() % window_Width/2) + 1;
		int random_y = (rand() % window_Height/2) + 1;
		Targets[i].x_pos = (float)random_x;
		Targets[i].y_pos = (float)random_y;
		Targets[i].SetActive = TRUE; 
	}
}
void SpawnTarget()
{
	for (int i = 0; i < 5; i++)
	{
		CP_Settings_Fill(Targets[i].target_Colour);
		CP_Graphics_DrawCircle(Targets[i].x_pos, Targets[i].y_pos, Targets[i].target_Diameter);
	}
}
void TargetCollider(TargetInfo T)
{
	if (T.SetActive)
	{
		//Target hit by projectile
		//Projectile will pass info to the Target and will use it accordingly
	}
}*/
/// </Targets>
void Car_Level_Update()
{

	switch (GAMESTATE)
	{
	case Play:
	{
		CP_Settings_Fill(WHITE);
		CP_Settings_TextSize(15.0f);
		CP_Font_DrawTextBox("'W'/'S' - Move Front/Back", 10, 25, 250);
		CP_Font_DrawTextBox("'A'/'D' - Rotate Left/Right", 10, 50, 250);
		CP_Font_DrawTextBox("'ESC' - Pause Menu", 10, 75, 250);
		CP_Font_DrawTextBox("'Left Mouse Button' - Fire projectile", 10, 100, 250);
		CP_Font_DrawTextBox("'Mouse Position' - Aim projectile", 10, 125, 250);

		//firerate
		if (current_FireTime <= firerate)
		{
			current_FireTime += TIMER;
		}
		if (CP_Input_MouseDown(MOUSE_BUTTON_RIGHT) && current_FireTime >= firerate)
		{
			for (int i = 0; i < 100; ++i)
			{
				//Check if projectile in pool has been spawn
				if (car_Projectiles[i].is_Active == 0)
				{
					SpawnProjectile(current_car, i, current_car->triangle_Colour);
					car_Projectiles[i].is_Active = 1;
					break;
				}
			}
			current_FireTime = 0;
		}
		//Projectile update
		for (int i = 0; i < 100; ++i)
		{
			if (car_Projectiles[i].is_Active == 1)
			{
				DrawProjectile(i);
				CheckProjectile(i);
			}
		}
		//Target Update
		/*for (int i = 0; i < 5; i++)
		{
			if (Targets[i].SetActive == TRUE)
			{
				SpawnTarget();
			}
		}*/
		CP_Graphics_ClearBackground(GREY);
		/// <CAR FUNCTION>
		IsCarClicked(CP_Input_GetMouseX(), CP_Input_GetMouseY());
		DrawCar();
		ControlCar(current_car);
		if (CP_Input_KeyDown(KEY_ESCAPE))
		{
			GAMESTATE = Pause;
		}

		break;
	}
	case Pause:
	{
		CP_Graphics_ClearBackground(BLACK);

		CP_Settings_Fill(WHITE);
		CP_Settings_TextSize(50.0f);
		CP_Font_DrawTextBox("PAUSE", CENTER_X - 60.f, CENTER_Y - 250.f, 150);

		CreateButton(button[0], "Resume", WHITE,35.f, CENTER_X-65.f, CENTER_Y - 15.f, RED);
		CreateButton(button[1], "Main Menu", WHITE,35.f, CENTER_X-65.f, CENTER_Y+65.f, AQUA);
		if (CP_Input_MouseClicked())
		{
			for (int i = 0; i < 2; i++)
			{
				switch (AreaClicked(CP_Input_GetMouseX(), CP_Input_GetMouseY(), button[i]))
				{
				case 0:
				{
					GAMESTATE = Play;
					break;
				}
				case 1:
				{
					CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
				}
				}
			}
		}
		break;
	}
	}


}

void Car_Level_Exit()
{

}