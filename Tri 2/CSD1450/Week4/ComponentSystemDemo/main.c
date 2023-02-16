
#include <assert.h>

#include "shared.h"
#include "character.h"
#include "collectible.h"
#include "achievement.h"
#include "spectators.h"
#include "cprocessing.h"
#include "src/component_level.h"

// Default font
static CP_Font g_font;


//
// game state data
//
static achievement_system_t g_achievement_system;
static character_t g_character;
static spectator_list_t g_spectator_list;
static collectible_list_t g_collectible_list;

//
// game state functions
//
void game_level_init(void) {
	// Load font
	g_font = CP_Font_Load("Assets/Roboto-Regular.ttf");

	//
	// Here, we put everything together.
	//
	init_character(&g_character, 100.f, 100.f, 50.f, 500.f);
	
	spectator_t* s1 = add_spectator(&g_spectator_list, 200.f, 100.f);
	spectator_t* s2 = add_spectator(&g_spectator_list, 300.f, 400.f);
	spectator_t* s3 = add_spectator(&g_spectator_list, 900.f, 500.f);
	spectator_t* s4 = add_spectator(&g_spectator_list, 800.f, 200.f);
	spectator_t* s5 = add_spectator(&g_spectator_list, 1500.f, 700.f);


	add_collectible(&g_collectible_list, 300.f, 100.f);
	add_collectible(&g_collectible_list, 400.f, 400.f);
	add_collectible(&g_collectible_list, 1000.f, 500.f);
	add_collectible(&g_collectible_list, 900.f, 200.f);
	add_collectible(&g_collectible_list, 1400.f, 700.f);


	// add observers to character
	add_observer(&g_character, s1, spectator_callback);
	add_observer(&g_character, s2, spectator_callback);
	add_observer(&g_character, s3, spectator_callback);
	add_observer(&g_character, s4, spectator_callback);
	add_observer(&g_character, s5, spectator_callback);
	add_observer(&g_character, &g_achievement_system, achievement_system_callback);
	
}

void game_level_update(void) {
	//
	// Update
	//
	update_character(&g_character);
	update_spectators(&g_spectator_list);
	update_notification(&g_achievement_system);
	collide_character_with_collectibles(&g_character, &g_collectible_list);
	
	//
	// Rendering
	//
	CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 255));
	render_spectators(&g_spectator_list);
	render_collectibles(&g_collectible_list);
	render_character(&g_character);
	render_notification(&g_achievement_system);
	
}

void game_level_exit(void) {
	
}



int main(void)
{
	CP_System_SetFrameRate(60.f);
	CP_System_SetWindowSize(WINDOW_W, WINDOW_H);
	//CP_Engine_SetNextGameState(game_level_init, game_level_update, game_level_exit);
	CP_Engine_SetNextGameState(component_level_init, component_level_update, component_level_exit);
	CP_Engine_Run();
	return 0;
}
