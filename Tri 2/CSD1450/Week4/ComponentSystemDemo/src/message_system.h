#pragma once
typedef struct object object;
typedef struct message_component
{
	const char* p_message;
}message_component;

void message_system_init();

message_component* add_component_message(object* p_object, const char* message);
int remove_component_message(object* p_object);