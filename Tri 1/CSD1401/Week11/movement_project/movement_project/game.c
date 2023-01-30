#include "cprocessing.h"
#include "easing.h"

#define USE_ACCELERATION 0

// - Chaser --------------------------------------------------------
typedef struct {
	CP_Vector position;
} Chaser;

typedef struct {
	CP_Vector position;
	CP_Vector velocity;
} Player;


static void UpdateChaser(Chaser* chaser, const Player* target) {

	// Cheap way to 'chase' a target with a spring-like effect
	CP_Vector displacement = CP_Vector_Subtract(target->position, chaser->position);
	CP_Vector damped_displacement = CP_Vector_Scale(displacement, 0.05f);
	chaser->position = CP_Vector_Add(chaser->position, damped_displacement);

}

static void RenderChaser(Chaser* chaser) {
	CP_Color circle_color = { 255, 0, 0, 255 };
	CP_Settings_Fill(circle_color);
	CP_Graphics_DrawCircle(chaser->position.x, chaser->position.y, 50.f);
}



static void UpdatePlayer(Player* player) {

	CP_Vector direction = {0};

	if (CP_Input_KeyDown(KEY_LEFT))
	{
		direction.x = -1.f;
	}

	if (CP_Input_KeyDown(KEY_RIGHT))
	{
		direction.x = 1.f;
	}
	if (CP_Input_KeyDown(KEY_UP))
	{
		direction.y = -1.f;
	}

	if (CP_Input_KeyDown(KEY_DOWN))
	{
		direction.y = 1.f;
	}

#if USE_ACCELERATION
	direction = CP_Vector_Normalize(direction);
	CP_Vector acceleration = CP_Vector_Scale(direction, 0.2f);

	// For each frame
	player->velocity = CP_Vector_Add(player->velocity, acceleration); 
	player->position = CP_Vector_Add(player->position, player->velocity);
#else 
	direction = CP_Vector_Normalize(direction);
	CP_Vector velocity = CP_Vector_Scale(direction, 10.f);
	player->position = CP_Vector_Add(player->position, velocity);
#endif 

}

static void RenderPlayer(const Player* player) {
	CP_Color circle_color = { 255, 255, 255, 255 };
	CP_Settings_Fill(circle_color);
	CP_Graphics_DrawCircle(player->position.x, player->position.y, 50.f);
}

// - Game state functions -------------------------------------------------------------
Player player = { 0 }; 
Chaser chaser = { 0 };

void GameInit(void){
	player.position.x = 400.f;
	player.position.y = 400.f;

	chaser.position.x = 400.f;
	chaser.position.y = 400.f;
}
void GameUpdate(void) {

	UpdateChaser(&chaser, &player);
	UpdatePlayer(&player);


	CP_Color background_color = { 125, 125, 125, 255 };
	CP_Graphics_ClearBackground(background_color);
	RenderPlayer(&player);
	RenderChaser(&chaser);
}


void GameExit(void){}
