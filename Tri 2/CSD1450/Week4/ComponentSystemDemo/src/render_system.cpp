#include "render_system.h"
#include "string.h"
#include "cprocessing.h"
#include "position_system.h"
#include "object_system.h"
#include "message_system.h"

//You may have different sizes for the list of various templates
#define TEMPLATE_LIST_SIZE 3
static square_render_template square_template_list[TEMPLATE_LIST_SIZE];
static circle_render_template circle_template_list[TEMPLATE_LIST_SIZE];
static textbox_render_template textbox_template_list[TEMPLATE_LIST_SIZE];

static char num_square_templates, num_circle_templates, num_textbox_templates;

#define COMPONENT_LIST_SIZE 20
static render_component component_list[COMPONENT_LIST_SIZE];
static char usage_flag[COMPONENT_LIST_SIZE];

//forward declarations
void render_square(int template_id, CP_Vector position);
void render_circle(int template_id, CP_Vector position);
void render_textbox(int template_id, CP_Vector position, const char* p_message);

void render_system_init()
{
	num_square_templates = 0;
	num_circle_templates = 0;
	num_textbox_templates = 0;
}

void render_system_update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(125, 125, 125, 255));
	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (!usage_flag[i])
			continue;
		
		render_component* p_render = component_list + i;
		position_component* p_pos = (position_component*)get_component(p_render->p_object, POSITION);

		switch (p_render->type)
		{
		case CIRCLE:
			render_circle(p_render->template_id, p_pos->pos);
			break;
		case SQUARE:
			render_square(p_render->template_id, p_pos->pos);
			break;
		case TEXTBOX:
			{
				message_component* p_message = (message_component*)get_component(p_render->p_object, MESSAGE);
				render_textbox(p_render->template_id, p_pos->pos, p_message->p_message);
			}
			break;
		}
		
	}
}

int render_system_add_square_render_template(square_render_template square)
{
	if (num_square_templates >= TEMPLATE_LIST_SIZE)
		return -1;

	square_template_list[num_square_templates] = square;

	return num_square_templates++;
}

int render_system_add_circle_render_template(circle_render_template circle)
{
	if (num_circle_templates >= TEMPLATE_LIST_SIZE)
		return -1;

	circle_template_list[num_circle_templates] = circle;

	return num_circle_templates++;
}

int render_system_add_textbox_render_template(textbox_render_template textbox)
{
	if (num_textbox_templates >= TEMPLATE_LIST_SIZE)
		return -1;

	textbox_template_list[num_textbox_templates] = textbox;

	return num_textbox_templates++;
}

render_component* add_component_render(object* p_object, render_type type, int template_id)
{
	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (usage_flag[i])
			continue;

		render_component* p_render = component_list + i;

		int result = add_component(p_object, RENDER, p_render);
		if (result < 0)
		{
			//unable to add component for some reason
			return 0;
		}

		//component successfully added
		usage_flag[i] = 1;
		//set member values
		p_render->p_object = p_object;
		p_render->type = type;
		p_render->template_id = template_id;
		return p_render;

	}
	return 0;
}

int remove_component_render(object* p_object)
{
	render_component* p_render = get_component(p_object, RENDER);
	size_t index = p_render - component_list;
	usage_flag[index] = 0;
	int result = remove_component(p_object, RENDER);
	return result;
}

void render_square(int template_id, CP_Vector position)
{
	square_render_template square = square_template_list[template_id];
	CP_Settings_Fill(square.fill_color);
	CP_Settings_Stroke(square.stroke_color);
	CP_Graphics_DrawRect(position.x, position.y, square.width, square.height);
}

void render_circle(int template_id, CP_Vector position)
{
	circle_render_template circle = circle_template_list[template_id];
	CP_Settings_Fill(circle.fill_color);
	CP_Settings_Stroke(circle.stroke_color);
	CP_Graphics_DrawCircle(position.x + circle.offset.x, position.y + circle.offset.y, circle.diameter);
}

void render_textbox(int template_id, CP_Vector position, const char* p_message)
{
	textbox_render_template textbox = textbox_template_list[template_id];
	CP_Settings_Fill(textbox.fill_color);
	CP_Settings_TextSize(textbox.text_size);
	
	CP_Settings_TextAlignment(textbox.alignment_x, textbox.alignment_y);
	CP_Font_DrawTextBox(p_message, position.x + textbox.offset.x, position.y + textbox.offset.y, textbox.row_width);
}