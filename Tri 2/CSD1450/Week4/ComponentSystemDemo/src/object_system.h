#pragma once
#include "components.h"
#include "cprocessing.h"

#define COMPONENT_LIST_LENGTH 5

typedef struct component_entry
{
	component_type type;
	void* p_component;
}component_entry;

typedef struct object
{
	component_entry component_list[COMPONENT_LIST_LENGTH];
}object;

void object_system_init();
object* object_system_get_object();
char object_system_release_object(object* p_object);

object* object_system_create_spectator(CP_Vector position);
object* object_system_create_collectible(CP_Vector position);
object* object_system_create_player(CP_Vector position);
object* object_system_create_dialog(CP_Vector position, const char* msg);

//these functions are to be used only by component systems
void* get_component(object* p_object, component_type type);
int add_component(object* p_object, component_type type,  void * p_component);
int remove_component(object* p_object, component_type type);

