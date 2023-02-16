#include "position_system.h"
#include "object_system.h"
#include "components.h"
#include "string.h"

#define POSITION_LIST_SIZE 20

static position_component position_list[POSITION_LIST_SIZE];
static char usage_flag[POSITION_LIST_SIZE];

void position_system_init()
{
	memset(usage_flag, 0, POSITION_LIST_SIZE);
}

position_component* add_component_position(object* p_object, CP_Vector position)
{
	for (int i = 0; i < POSITION_LIST_SIZE; ++i)
	{
		if (!usage_flag[i])
		{
			usage_flag[i] = 1;
			position_component* p_pos = &position_list[i];

			p_pos->pos = position;
			add_component(p_object,POSITION, p_pos);
			return p_pos;
		}
	}

	//position list completely in use
	return 0;
}

char remove_component_position(object* p_object)
{
	position_component* p_pos = (position_component * )get_component(p_object, POSITION);
	size_t index = p_pos - position_list;
	char result = usage_flag[index];
	usage_flag[index] = 0;
	remove_component(p_object, POSITION);
	return result;
}