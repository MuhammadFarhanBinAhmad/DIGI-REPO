#include "collision_system.h"
#include "object_system.h"
#include "string.h"
#include "../shared.h"
#include "position_system.h"

typedef struct
{
	int id_1;
	int id_2;
}collision_id_pair;

#define CIRCLE_COLLISION_COMPONENT_LIST_SIZE 20
#define COLLISION_ID_PAIR_LIST_SIZE 3

static circle_collision_component component_list[CIRCLE_COLLISION_COMPONENT_LIST_SIZE];
static char usage_flag[CIRCLE_COLLISION_COMPONENT_LIST_SIZE];

static collision_id_pair component_id_pair_list[COLLISION_ID_PAIR_LIST_SIZE];

collision_event collision_events_list[COLLISION_EVENT_LIST_SIZE];
int num_of_collision_events;

void collision_system_add_collision_event(object* p_object_1, object* p_object_2, int collision_hash);
int generate_collision_hash_from_pair(collision_id_pair pair);

circle_collision_component* add_component_collision_circle(object* p_object, float diameter, char collision_id)
{
	for (int i = 0; i < CIRCLE_COLLISION_COMPONENT_LIST_SIZE; ++i)
	{
		if (!usage_flag[i])
		{
			circle_collision_component* p_circle = component_list + i;

			int result = add_component(p_object, CIRCLE_COLLIDER, p_circle);
			if (result < 0)
			{
				//unable to add component for some reason
				return 0;
			}

			//component successfully added
			usage_flag[i] = 1;
			//set member values
			p_circle->p_object = p_object;
			p_circle->diameter = diameter;
			p_circle->collision_id = collision_id;
			return p_circle;
		}
	}

	return 0;
}

int remove_component_collision_circle(object* p_object)
{
	circle_collision_component* p_circle = get_component(p_object, CIRCLE_COLLIDER);
	size_t index = p_circle - component_list;
	usage_flag[index] = 0;
	int result = remove_component(p_object, CIRCLE_COLLIDER);
	return result;
}

void collision_system_init()
{
	memset(component_list, 0, sizeof(circle_collision_component) * CIRCLE_COLLISION_COMPONENT_LIST_SIZE);
	memset(usage_flag, 0, CIRCLE_COLLISION_COMPONENT_LIST_SIZE);
	memset(component_id_pair_list, 0, sizeof(collision_id_pair) * COLLISION_ID_PAIR_LIST_SIZE);
}

void collision_system_update()
{
	//Every new frame we reset all collision events that have happened before.
	memset(collision_events_list, 0, sizeof(collision_event) * COLLISION_EVENT_LIST_SIZE);
	num_of_collision_events = 0;

	for (int i = 0; i < COLLISION_ID_PAIR_LIST_SIZE; ++i)
	{
		collision_id_pair pair = component_id_pair_list[i];
		if (pair.id_1 == NONE_COLLISION_ID)
			continue;

		for (int iter_1 = 0; iter_1 < CIRCLE_COLLISION_COMPONENT_LIST_SIZE; ++iter_1)
		{
			if (!usage_flag[iter_1])
				continue;
			circle_collision_component circle_1 = component_list[iter_1];
			if (circle_1.collision_id != pair.id_1)
				continue;

			for (int iter_2 = 0; iter_2 < CIRCLE_COLLISION_COMPONENT_LIST_SIZE; ++iter_2)
			{
				if (!usage_flag[iter_2])
					continue;
				circle_collision_component circle_2 = component_list[iter_2];
				if (circle_2.collision_id != pair.id_2)
					continue;

				position_component* p_pos_1 = (position_component*)get_component(circle_1.p_object, POSITION);
				position_component* p_pos_2 = (position_component*)get_component(circle_2.p_object, POSITION);
				int result = is_circle_in_circle(p_pos_1->pos.x, p_pos_1->pos.y, circle_1.diameter,
					p_pos_2->pos.x, p_pos_2->pos.y, circle_2.diameter);

				if (result)
					collision_system_add_collision_event(circle_1.p_object, circle_2.p_object, generate_collision_hash_from_pair(pair));
			}
		}
	}
}

collision_id_pair generate_pair(collision_id id_1, collision_id id_2)
{
	collision_id_pair pair;
	if (id_1 < id_2)
	{
		pair.id_1 = id_1;
		pair.id_2 = id_2;
	}
	else
	{
		pair.id_1 = id_2;
		pair.id_2 = id_1;
	}
	return pair;
}

int generate_collision_hash_from_pair(collision_id_pair pair)
{
	return pair.id_1 + pair.id_2 * NUM_COLLISION_ID;
}

//this function returns a collision hash if successful.
//the collision hash is a unique number to represent collision events between the input collision_id provided
int collision_system_add_collision_pair(collision_id id_1, collision_id id_2)
{
	//unique collision pair generation and check
	collision_id_pair pair = generate_pair(id_1, id_2);
	int pair_id = generate_collision_hash_from_pair(pair);

	for (int i = 0; i < COLLISION_ID_PAIR_LIST_SIZE; ++i)
	{
		if (component_id_pair_list[i].id_1 == pair.id_1 &&
			component_id_pair_list[i].id_2 == pair.id_2)
		{
			//pair already exists, no need for further action
			return pair_id;
		}
	}

	for (int i = 0; i < COLLISION_ID_PAIR_LIST_SIZE; ++i)
	{
		if (component_id_pair_list[i].id_1 == NONE_COLLISION_ID)
		{
			component_id_pair_list[i] = pair;
			return pair_id;
		}
	}

	//list is full, cannot add more collision pairs
	return -1;
}

int collision_system_remove_collision_pair(collision_id id_1, collision_id id_2)
{
	collision_id_pair pair = generate_pair(id_1, id_2);
	for (int i = 0; i < COLLISION_ID_PAIR_LIST_SIZE; ++i)
	{
		if (component_id_pair_list[i].id_1 == pair.id_1 &&
			component_id_pair_list[i].id_2 == pair.id_2)
		{
			component_id_pair_list[i].id_1 = NONE_COLLISION_ID;
			component_id_pair_list[i].id_2 = NONE_COLLISION_ID;
			return i;
		}
	}
	//unable to find pair
	return -1;
}

void collision_system_add_collision_event(object* p_object_1, object* p_object_2, int collision_hash)
{
	collision_events_list[num_of_collision_events].collision_hash = collision_hash;
	collision_events_list[num_of_collision_events].p_object_1 = p_object_1;
	collision_events_list[num_of_collision_events].p_object_2 = p_object_2;
	++num_of_collision_events;
}
