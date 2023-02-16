#include "controller_system.h"
#include "string.h"
#include "cprocessing.h"
#include "position_system.h"
#include "components.h"
#include "object_system.h"

#define COMPONENT_LIST_SIZE 10

static controller_component component_list[COMPONENT_LIST_SIZE];
static char usage_flag[COMPONENT_LIST_SIZE];


void controller_system_init()
{
	memset(usage_flag, 0, COMPONENT_LIST_SIZE);
	memset(component_list, 0, COMPONENT_LIST_SIZE * sizeof(controller_component));
}

void controller_system_update(float dt)
{
	CP_Vector dir = { 0 };
	if (CP_Input_KeyDown(KEY_A))
	{
		dir.x += -1.f;
	}
	if (CP_Input_KeyDown(KEY_D))
	{
		dir.x += 1.f;
	}
	if (CP_Input_KeyDown(KEY_W))
	{
		dir.y += -1.f;
	}
	if (CP_Input_KeyDown(KEY_S))
	{
		dir.y += 1.f;
	}

	dir = CP_Vector_Normalize(dir);

	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (!usage_flag[i])
			continue;

		controller_component* p_controller = component_list + i;
		CP_Vector velocity = CP_Vector_Scale(dir, p_controller->speed * CP_System_GetDt());
		position_component* p_pos = (position_component*)get_component(p_controller->p_object, POSITION);
		p_pos->pos = CP_Vector_Add(p_pos->pos, velocity);
	}
}

controller_component* add_component_controller(object* p_object, float speed)
{
	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (usage_flag[i])
			continue;

		controller_component* p_controller = component_list + i;

		int result = add_component(p_object, CONTROLLER, p_controller);
		if (result < 0)
			return 0;//unable to add component

		//component successfully added
		usage_flag[i] = 1;
		//set member values
		p_controller->p_object = p_object;
		p_controller->speed = speed;
		return p_controller;

	}
	return 0;
}

int remove_component_controller(object* p_object)
{
	controller_component* p_controller = (controller_component * )get_component(p_object, CONTROLLER);
	size_t index = p_controller - &component_list[0];
	usage_flag[index] = 0;
	int result = remove_component(p_object, CONTROLLER);
	return result;
}