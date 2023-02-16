#pragma once
#include "cprocessing.h"
typedef struct object object;

typedef enum render_type
{
	NONE,
	CIRCLE,
	SQUARE,
	TEXTBOX
}render_type;

typedef struct circle_render_template
{
	CP_Color fill_color;
	CP_Color stroke_color;
	float diameter;
	CP_Vector offset;
}circle_render_template;

//requirements on previous implementation where a single spectator has more than one shape to render
typedef struct square_render_template
{
	CP_Color fill_color;
	CP_Color stroke_color;
	float width;
	float height;
}square_render_template;

typedef struct textbox_render_template
{
	CP_Color fill_color;
	float text_size;
	int alignment_x, alignment_y;
	CP_Vector offset;
	float row_width;
}textbox_render_template;

typedef struct render_component
{
	render_type type;
	int template_id;
	object* p_object;
}render_component;

void render_system_init();
void render_system_update();

int render_system_add_circle_render_template(circle_render_template circle);
int render_system_add_square_render_template(square_render_template square);
int render_system_add_textbox_render_template(textbox_render_template textbox);

render_component* add_component_render(object* p_object, render_type type, int template_id);
int remove_component_render(object* p_object);