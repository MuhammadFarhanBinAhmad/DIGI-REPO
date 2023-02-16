#pragma once
typedef struct object object;

typedef struct
{
	object* p_object;
	float speed;
}controller_component;

void controller_system_init();
void controller_system_update(float dt);
controller_component* add_component_controller(object* p_object, float speed);
int remove_component_controller(object* p_object);
