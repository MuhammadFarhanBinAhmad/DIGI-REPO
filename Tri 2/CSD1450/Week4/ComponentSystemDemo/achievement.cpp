#include "achievement.h"
#include "character.h"
#include "shared.h"

void render_notification(achievement_system_t* n) {

	if (n->notif_msg && n->notif_timer > 0) {
		float alpha = n->notif_timer / 3.f * 255.f;

		CP_Settings_Fill(CP_Color_Create(255, 125, 125, (int)alpha));
		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Settings_TextSize(128.f);
		CP_Font_DrawTextBox(n->notif_msg, 0.f, WINDOW_H - 128.f, WINDOW_W);
	}
}

void update_notification(achievement_system_t* n)
{
	if (n->notif_timer > 0)
		n->notif_timer -= CP_System_GetDt();
}

void set_notification(achievement_system_t* a, const char* msg)
{
	a->notif_timer = 3.f;
	a->notif_msg = msg;
}

// Must be the same type as observer_callback_t
void achievement_system_callback(void* context, character_event_t e) {
	achievement_system_t* a = (achievement_system_t*)context;
	switch (e) {
	case CHARACTER_EVENT_COLLECTIBLE:
		++a->collectibles_collected;
		if (a->collectibles_collected == 5) {
			set_notification(a, "Collected 5 collectibles!");
		}
		else {
			set_notification(a, "Collected a collectible!");
		}

		break;
	case CHARACTER_EVENT_POKED:
		++a->character_poked;
		if (a->character_poked == 10) {
			set_notification(a, "Poked character 10 times!");
		}
		else if (a->character_poked == 20) {
			set_notification(a, "Poked too many times!");
		}
		else if (a->character_poked == 30) {
			set_notification(a, "Seriously stop poking.");
		}
	}
}
