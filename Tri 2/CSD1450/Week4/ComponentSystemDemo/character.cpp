#include <assert.h>
//#include "utils.h"
#include "shared.h"
#include "character.h"

void add_observer(character_t* c, void* context, observer_callback_t callback)
{
	assert(c->observer_count < array_count(c->observers));
	observer_t* observer = c->observers + c->observer_count++;
	observer->context = context;
	observer->observer_callback = callback;
}

void notify_observers(character_t* c, character_event_t e) {
	for (size_t observer_index = 0; observer_index < c->observer_count; ++observer_index)
	{
		observer_t* observer = c->observers + observer_index;
		observer->observer_callback(observer->context, e);
	}
}


void update_character(character_t* c) {
	// Process mouse input for selection of characters
	if (CP_Input_MouseClicked())
	{
		float mouse_x = CP_Input_GetMouseX();
		float mouse_y = CP_Input_GetMouseY();

		if (is_point_in_circle(c->position.x, c->position.y, c->diameter, mouse_x, mouse_y))
		{
			notify_observers(c, CHARACTER_EVENT_POKED);
		}
	}

	CP_Vector dir = { 0 };
	if (CP_Input_KeyDown(KEY_A))
	{
		dir.x += -1.f;
	}
	if (CP_Input_KeyDown(KEY_D))
	{
		dir.x += 1.f;
	}
	if (CP_Input_KeyDown(KEY_W))
	{
		dir.y += -1.f;
	}
	if (CP_Input_KeyDown(KEY_S))
	{
		dir.y += 1.f;
	}

	CP_Vector velocity = CP_Vector_Scale(CP_Vector_Normalize(dir), 500.f * CP_System_GetDt());
	c->position = CP_Vector_Add(c->position, velocity);

}

void init_character(character_t* c, float x, float y, float diameter, float speed) {
	c->position.x = x;
	c->position.y = y;
	c->diameter = diameter;
	c->speed = speed;
	c->observer_count = 0;
}

void render_character(character_t* c) {
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
	CP_Graphics_DrawCircle(c->position.x, c->position.y, c->diameter);
}



