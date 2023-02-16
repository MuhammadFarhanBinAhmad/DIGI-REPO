#include "object_system.h"
#include "string.h"
#include "render_system.h"
#include "position_system.h"
#include "timer_system.h"
#include "collision_system.h"
#include "spectator_system.h"
#include "message_system.h"
#include "controller_system.h"

#define OBJECT_LIST_SIZE 20

static object object_list[OBJECT_LIST_SIZE];
static char usage_flag[OBJECT_LIST_SIZE];

//Rendering ids got from loading templates of each type of object
static int spectator_head_id, spectator_body_id;
static int collectible_id;
static int player_id;
static int message_id;

void load_spectator_template();
void load_player_template();
void load_collectible_template();
void load_message_template();

void object_system_init()
{
	memset(usage_flag, 0, OBJECT_LIST_SIZE);
	memset(object_list, 0, OBJECT_LIST_SIZE * sizeof(object));

	//load templates
	load_spectator_template();
	load_player_template();
	load_collectible_template();
	load_message_template();
}

object* object_system_get_object()
{
	for (int i = 0; i < OBJECT_LIST_SIZE; ++i)
	{
		if (!usage_flag[i])
		{
			usage_flag[i] = 1;
			object* p_object = object_list + i;
			return p_object;
		}
	}

	return 0;
}

char object_system_release_object(object* p_object)
{
	size_t index = p_object - object_list;
	if (!usage_flag[index])
		return -1;

	for (int i = 0; i < COMPONENT_LIST_LENGTH; ++i)
	{
		int type = p_object->component_list[i].type;
		switch (type)
		{
		case POSITION:
			remove_component_position(p_object);
			break;
		case CIRCLE_COLLIDER:
			remove_component_collision_circle(p_object);
			break;
		case TIMER:
			remove_component_timer(p_object);
			break;
		case RENDER:
			remove_component_render(p_object);
			break;
		case SPECTATOR:
			remove_component_spectator(p_object);
			break;
		case MESSAGE:
			remove_component_message(p_object);
			break;
		case CONTROLLER:
			remove_component_controller(p_object);
			break;
		}
	}
	
	usage_flag[index] = 0;
	memset(p_object, 0, sizeof(object));
	return 0;
}

void* get_component(object* p_object, component_type type)
{
	for (int i = 0; i < COMPONENT_LIST_LENGTH; ++i)
	{
		if (p_object->component_list[i].type == type)
		{
			return p_object->component_list[i].p_component;
		}
	}

	return 0;
}

int add_component(object* p_object, component_type type, void* p_component)
{
	for (int i = 0; i < COMPONENT_LIST_LENGTH; ++i)
	{
		if (p_object->component_list[i].type == NONE_COMPONENT)
		{
			p_object->component_list[i].type = type;
			p_object->component_list[i].p_component = p_component;
			return i;
		}
	}

	return -1;
}

int remove_component(object* p_object, component_type type)
{
	for (int i = 0; i < COMPONENT_LIST_LENGTH; ++i)
	{
		if (p_object->component_list[i].type == type)
		{
			p_object->component_list[i].type = NONE;
			p_object->component_list[i].p_component = 0;
			return i;
		}
	}

	return -1;
}

object* object_system_create_spectator(CP_Vector position)
{
	object* p_object = object_system_get_object();
	add_component_position(p_object, position);
	add_component_render(p_object, CIRCLE, spectator_head_id);
	add_component_render(p_object, SQUARE, spectator_body_id);
	add_component_spectator(p_object);
	return p_object;
}

object* object_system_create_collectible(CP_Vector position)
{
	object* p_object = object_system_get_object();
	add_component_position(p_object, position);
	add_component_render(p_object, CIRCLE, collectible_id);
	add_component_collision_circle(p_object, 20.0f, COLLECTIBLE_COLLISION_ID);
	return p_object;
}

object* object_system_create_player(CP_Vector position)
{
	object* p_object = object_system_get_object();
	add_component_position(p_object, position);
	add_component_render(p_object, CIRCLE, player_id);
	add_component_collision_circle(p_object, 50.0f, PLAYER_COLLISION_ID);
	add_component_controller(p_object, 500.f);
	return p_object;
}

object* object_system_create_dialog(CP_Vector position, const char* msg)
{
	object* p_object = object_system_get_object();
	add_component_position(p_object, position);
	add_component_render(p_object, TEXTBOX, message_id);
	add_component_message(p_object, msg);
	return p_object;
}

void load_spectator_template()
{
	square_render_template body;
	body.fill_color = CP_Color_Create(255, 255, 0, 255);
	body.stroke_color = CP_Color_Create(0, 0, 0, 255);
	body.width = 30.f;
	body.height = 50.f;
	spectator_body_id = render_system_add_square_render_template(body);

	circle_render_template head;
	head.diameter = 40.f;
	head.fill_color = CP_Color_Create(255, 255, 255, 255);
	head.offset = CP_Vector_Set(15.f, 0.f);
	head.stroke_color = CP_Color_Create(0, 0, 0, 255);
	spectator_head_id = render_system_add_circle_render_template(head);
}

void load_player_template()
{
	circle_render_template player;
	player.diameter = 40.f;
	player.fill_color = CP_Color_Create(0, 255, 0, 255);
	player.offset = CP_Vector_Set(0.f, 0.f);
	player.stroke_color = CP_Color_Create(0, 0, 0, 255);
	player_id = render_system_add_circle_render_template(player);
}

void load_collectible_template()
{
	circle_render_template collectible;
	collectible.diameter = 20.f;
	collectible.fill_color = CP_Color_Create(255, 125, 125, 255);
	collectible.offset = CP_Vector_Set(0.f, 0.f);
	collectible.stroke_color = CP_Color_Create(255 / 2, 125 / 2, 125 / 2, 255);
	collectible_id = render_system_add_circle_render_template(collectible);
}

void load_message_template()
{
	textbox_render_template message;
	message.alignment_x = CP_TEXT_ALIGN_H_CENTER;
	message.alignment_y = CP_TEXT_ALIGN_V_MIDDLE;
	message.fill_color = CP_Color_Create(0, 0, 0, 255);
	message.offset = CP_Vector_Set(-100.f + 15.f, -40.f);
	message.row_width = 200.f;
	message.text_size = 24.f;
	message_id = render_system_add_textbox_render_template(message);
}