#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cprocessing.h"

typedef enum {
	CHARACTER_EVENT_POKED,
	CHARACTER_EVENT_COLLECTIBLE
} character_event_t;

typedef void (observer_callback_t)(void* context, character_event_t e);

typedef struct {
	void* context;
	observer_callback_t* observer_callback;
} observer_t;

typedef struct {
	CP_Vector position;
	float speed;
	float diameter;

	// observer pattern
	observer_t observers[64]; // let's have up to 64 observers
	size_t observer_count;

} character_t;


void add_observer(character_t* c, void* context, observer_callback_t callback);
void notify_observers(character_t* c, character_event_t e);
void update_character(character_t* c);
void init_character(character_t* c, float x, float y, float diameter, float speed);
void render_character(character_t* c);

#endif // __CHARACTER_H__