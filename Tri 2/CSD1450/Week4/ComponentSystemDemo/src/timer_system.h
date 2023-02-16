#pragma once

typedef struct object object;

typedef struct
{
	float remaining;
	float base;
	float time_scale;
	char is_completed;
}timer_component;

void timer_system_init();
void timer_system_update(float dt);
void timer_system_post_update();

timer_component* add_component_timer(object* p_object, float base, float time_scale);
int remove_component_timer(object* p_object);


