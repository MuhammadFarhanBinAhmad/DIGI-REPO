#include "component_level.h"
#include "collectible_system.h"
#include "collision_system.h"
#include "controller_system.h"
#include "message_system.h"
#include "object_system.h"
#include "position_system.h"
#include "render_system.h"
#include "spectator_system.h"

void component_level_init(void)
{
	//this could be done at the start of the application instead of game state
	object_system_init();
	collectible_system_init();
	collision_system_init();
	controller_system_init();
	message_system_init();
	position_system_init();
	render_system_init();
	spectator_system_init();

	//create objects
	//this can be loaded from file too
	object_system_create_player(CP_Vector_Set(100.f, 100.f));

	object_system_create_spectator(CP_Vector_Set(200.f, 100.f));
	object_system_create_spectator(CP_Vector_Set(300.f, 400.f));
	object_system_create_spectator(CP_Vector_Set(900.f, 500.f));
	object_system_create_spectator(CP_Vector_Set(800.f, 200.f));
	object_system_create_spectator(CP_Vector_Set(1500.f, 700.f));

	object_system_create_collectible(CP_Vector_Set(300.f, 100.f));
	object_system_create_collectible(CP_Vector_Set(400.f, 400.f));
	object_system_create_collectible(CP_Vector_Set(1000.f, 500.f));
	object_system_create_collectible(CP_Vector_Set(900.f, 200.f));
	object_system_create_collectible(CP_Vector_Set(1400.f, 700.f));
}

void component_level_update(void)
{
	float dt = CP_System_GetDt();
	controller_system_update(dt);
	collision_system_update();
	spectator_system_update(dt);
	collectible_system_update();
	render_system_update();
	
}

void component_level_exit(void)
{
	
}