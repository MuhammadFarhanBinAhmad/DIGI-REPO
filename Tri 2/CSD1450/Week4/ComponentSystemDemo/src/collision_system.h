#pragma once

//forward declaration of object struct
typedef struct object object;

typedef enum
{
	NONE_COLLISION_ID = 0,
	PLAYER_COLLISION_ID,
	COLLECTIBLE_COLLISION_ID,
	NUM_COLLISION_ID
}collision_id;

//here diameter is separated as collision shapes do not need to match render shapes
typedef struct
{
	object* p_object;
	float diameter;
	char collision_id;
}circle_collision_component;

typedef struct
{
	int collision_hash;
	object* p_object_1;
	object* p_object_2;
}collision_event;

circle_collision_component* add_component_collision_circle(object* p_object, float diameter, char collision_id);
int remove_component_collision_circle(object* p_object);

#define COLLISION_EVENT_LIST_SIZE 20
extern collision_event collision_events_list[COLLISION_EVENT_LIST_SIZE];
extern int num_of_collision_events;

void collision_system_init();
void collision_system_update();

//collision pairs are used to identify which two types of objects should be tested for collision
//in our case, only the player will be colliding with collectibles.
//collectibles will not be colliding amongst themselves.
int collision_system_add_collision_pair(collision_id id_1, collision_id id_2);
int collision_system_remove_collision_pair(collision_id id_1, collision_id id_2);


