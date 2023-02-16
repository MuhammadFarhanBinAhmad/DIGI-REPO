#include "timer_system.h"
#include "string.h"
#include "components.h"
#include "object_system.h"

#define COMPONENT_LIST_SIZE 20

static timer_component component_list[COMPONENT_LIST_SIZE];
static char usage_flag[COMPONENT_LIST_SIZE];

void timer_system_init()
{
	memset(usage_flag, 0, COMPONENT_LIST_SIZE);
	memset(component_list, 0, COMPONENT_LIST_SIZE * sizeof(timer_component));
}

void timer_system_update(float dt)
{
	
	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (!usage_flag[i])
			continue;
		
		timer_component* p_timer = component_list + i;

		p_timer->remaining -= dt * p_timer->time_scale;
		if (p_timer->remaining <= 0.0f)
		{
			p_timer->is_completed = 1;
		}
	}
}

void timer_system_post_update()
{
	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (!usage_flag[i])
			continue;
		
		timer_component* p_timer = component_list + i;

		if (p_timer->remaining <= 0.0f)
		{
			p_timer->remaining += p_timer->base;
			p_timer->is_completed = 0;
		}
	}
}

timer_component* add_component_timer(object* p_object, float base, float time_scale)
{
	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (usage_flag[i])
		{
			continue;
		}
		
		timer_component* p_timer = component_list + i;

		int result = add_component(p_object, TIMER, p_timer);
		if (result < -1)
		{
			//unable to add component for some reason
			return 0;
		}

		//component successfully added
		usage_flag[i] = 1;
		//set member values
		p_timer->remaining = base;
		p_timer->base = base;
		p_timer->is_completed = 0;
		p_timer->time_scale = time_scale;
		return p_timer;
		
	}
	return 0;
}

int remove_component_timer(object* p_object)
{
	timer_component* p_timer = get_component(p_object, TIMER);
	size_t index = p_timer - component_list;
	usage_flag[index] = 0;
	int result = remove_component(p_object, TIMER);
	return result;
}