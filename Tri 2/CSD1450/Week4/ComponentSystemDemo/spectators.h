#ifndef __SPECTATORS_H__
#define __SPECTATORS_H__

#include "cprocessing.h"
#include "character.h"

typedef struct {
	CP_Vector position;

	// diaglogue system, kind of.
	float dialogue_timer;
	const char* dialogue_msg;
} spectator_t;

typedef struct {
	spectator_t spectators[5];
	size_t spectator_count;
} spectator_list_t;


spectator_t* add_spectator(spectator_list_t* sl, float x, float y);
void update_spectators(spectator_list_t* sl);
void render_spectators(spectator_list_t* sl);
void spectator_say_random_good_stuff(spectator_t* s);
void spectator_callback(void* context, character_event_t e);


#endif // __SPECTATORS_H__