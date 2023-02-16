#pragma once
#include "cprocessing.h"
typedef struct object object;

typedef struct spectator_component
{
	object* p_object;
	object* p_dialog;
}spectator_component;

void spectator_system_init();
void spectator_system_update(float dt);

spectator_component* add_component_spectator(object* p_object);
int remove_component_spectator(object* p_object);
