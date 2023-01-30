#ifndef __ACHIEVEMENT_H__
#define __ACHIEVEMENT_H__

#include "cprocessing.h"
#include "character.h"

typedef struct {
	float notif_timer;
	const char* notif_msg;

	int character_poked;
	int collectibles_collected;

} achievement_system_t;


void render_notification(achievement_system_t* n);
void update_notification(achievement_system_t* n);
void set_notification(achievement_system_t* a, const char* msg);
void achievement_system_callback(void* context, character_event_t e);


#endif // __ACHIEVEMENT_H__