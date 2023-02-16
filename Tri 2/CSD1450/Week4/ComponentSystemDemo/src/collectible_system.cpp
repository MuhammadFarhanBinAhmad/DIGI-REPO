#include "collectible_system.h"
#include "collision_system.h"
#include "components.h"
#include "object_system.h"
static int player_collectible_collision_hash;

void collectible_system_init()
{
	player_collectible_collision_hash = collision_system_add_collision_pair(PLAYER_COLLISION_ID, COLLECTIBLE_COLLISION_ID);
}
void collectible_system_update()
{
	for (int i = 0; i < COLLISION_EVENT_LIST_SIZE; ++i)
	{
		int hash = collision_events_list[i].collision_hash;

		if (hash != player_collectible_collision_hash)
			continue;

		collision_event* p_event = collision_events_list + i;
		circle_collision_component* p_circle = (circle_collision_component * )get_component(p_event->p_object_1, CIRCLE_COLLIDER);

		object* p_collectible = p_circle->collision_id == COLLECTIBLE_COLLISION_ID? p_event->p_object_1 : p_event->p_object_2;

		//we normally do not release objects immediately.
		//We mark them for release then release with a system just before the end of the frame.
		object_system_release_object(p_collectible);
	}
}