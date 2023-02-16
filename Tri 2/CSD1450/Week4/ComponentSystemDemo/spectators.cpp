#include <assert.h>
#include "shared.h"
#include "spectators.h"
#include "character.h"

spectator_t* add_spectator(spectator_list_t* sl, float x, float y) {
	assert(sl->spectator_count < array_count(sl->spectators));
	spectator_t* s = sl->spectators + sl->spectator_count++;
	s->position.x = x;
	s->position.y = y;

	return s;
}

void update_spectator(spectator_t* s) {
	if (s->dialogue_timer > 0.f)
		s->dialogue_timer -= CP_System_GetDt();
}


void update_spectators(spectator_list_t* sl) {
	for (size_t spectator_index = 0; spectator_index < sl->spectator_count; ++spectator_index)
	{
		spectator_t* s = sl->spectators + spectator_index;
		update_spectator(s);
	}
}

void render_spectators(spectator_list_t* sl) {
	for (size_t spectator_index = 0; spectator_index < sl->spectator_count; ++spectator_index)
	{
		spectator_t* s = sl->spectators + spectator_index;
		CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
		CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));

		// Note to students: please don't hard code like this :)
		CP_Graphics_DrawRect(s->position.x, s->position.y, 30.f, 50.f);

		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
		CP_Graphics_DrawCircle(s->position.x + 15.f, s->position.y, 40.f);

		if (s->dialogue_msg && s->dialogue_timer > 0.f) {
			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Settings_TextSize(24.f);

			CP_Settings_TextSize(24.f);
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			CP_Font_DrawTextBox(s->dialogue_msg, s->position.x - 100.f + 15.f, s->position.y - 40.f, 200.f);
		}
	}

}

void spectator_say_random_good_stuff(spectator_t* s) {
	static const char* msgs[] = {
		"wow!", "super!", "hey hey!", "whoa!", "amajing!"
	};
	unsigned random_index = CP_Random_RangeInt(0, array_count(msgs) - 1);

	s->dialogue_timer = 2.f;
	s->dialogue_msg = msgs[random_index];
}

// Must be the same type as observer_callback_t
void spectator_callback(void* context, character_event_t e) {
	spectator_t* s = (spectator_t*)context;
	switch (e) {
	case CHARACTER_EVENT_COLLECTIBLE:
		spectator_say_random_good_stuff(s);
		break;
	}
}