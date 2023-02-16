#pragma once
#include "cprocessing.h"

//forward declaration of object struct
typedef struct object object;

//Position is shared for use for collision and rendering
typedef struct
{
	CP_Vector pos;
}position_component;

void position_system_init();
position_component* add_component_position(object* p_object, CP_Vector position);
char remove_component_position(object* p_object);