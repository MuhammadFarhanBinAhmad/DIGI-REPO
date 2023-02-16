#include "spectator_system.h"
#include "collision_system.h"
#include "object_system.h"
#include "message_system.h"
#include "../shared.h"
#include "position_system.h"
#define COMPONENT_LIST_SIZE 20

#define MESSAGE_DURATION 2.f

static spectator_component component_list[COMPONENT_LIST_SIZE];
static char usage_flag[COMPONENT_LIST_SIZE];
static int player_collectible_collision_hash;
static float remaining_time;

const char* get_spectator_msg();

void spectator_system_init()
{
	player_collectible_collision_hash = collision_system_add_collision_pair(PLAYER_COLLISION_ID, COLLECTIBLE_COLLISION_ID);

}

void spectator_system_update(float dt)
{
	char is_collected = 0;

	if (remaining_time > 0.0f)
	{
		remaining_time -= dt;
	}

	for (int i = 0; i < num_of_collision_events; ++i)
	{
		collision_event event = collision_events_list[i];
		if (event.collision_hash != player_collectible_collision_hash)
			continue;
		else
		{
			is_collected = 1;
			break;
		}
	}
	
	if (is_collected)
	{
		if (remaining_time <= 0.f)
		{
			//create dialog
			for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
			{
				if (!usage_flag[i])
					continue;

				spectator_component* p_spectator = component_list + i;
				const char* msg = get_spectator_msg();
				position_component* p_pos = (position_component*)get_component(p_spectator->p_object, POSITION);
				p_spectator->p_dialog = object_system_create_dialog(p_pos->pos, msg);
			}
		}
		else
		{
			for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
			{
				if (!usage_flag[i])
					continue;

				spectator_component* p_spectator = component_list + i;
				const char* msg = get_spectator_msg();
				message_component* p_message = (message_component *)get_component(p_spectator->p_dialog, MESSAGE);
				p_message->p_message = msg;
			}
		}
		remaining_time = MESSAGE_DURATION;
	}
	else
	{
		if (remaining_time <= 0.f)
		{
			//remove dialogs as time is up
			for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
			{
				if (!usage_flag[i])
					continue;

				spectator_component* p_spectator = component_list + i;

				if (p_spectator->p_dialog)
				{
					object_system_release_object(p_spectator->p_dialog);
					p_spectator->p_dialog = 0;
				}
			}
		}
		
	}
}

spectator_component* add_component_spectator(object* p_object)
{
	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (usage_flag[i])
			continue;

		spectator_component* p_spectator = component_list + i;

		int result = add_component(p_object, SPECTATOR, p_spectator);
		if (result < 0)
			return 0;//unable to add component for some reason

		//component successfully added
		usage_flag[i] = 1;
		//set member values
		p_spectator->p_object = p_object;
		return p_spectator;
	}
	return 0;
}

int remove_component_spectator(object* p_object)
{
	spectator_component* p_spectator = (spectator_component * )get_component(p_object, SPECTATOR);
	size_t index = p_spectator - component_list;
	usage_flag[index] = 0;
	int result = remove_component(p_object, SPECTATOR);
	return result;
}

const char* get_spectator_msg() 
{
	static const char* msgs[] = {
		"wow!", "super!", "hey hey!", "whoa!", "amajing!"
	};
	unsigned random_index = CP_Random_RangeInt(0, array_count(msgs) - 1);

	return msgs[random_index];
}
