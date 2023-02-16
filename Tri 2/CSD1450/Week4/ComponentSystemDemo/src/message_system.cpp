#include "message_system.h"
#include "components.h"
#include "string.h"
#include "object_system.h"
#define COMPONENT_LIST_SIZE 20

static message_component component_list[COMPONENT_LIST_SIZE];
static char usage_flag[COMPONENT_LIST_SIZE];

void message_system_init()
{
	memset(usage_flag, 0, COMPONENT_LIST_SIZE);
	memset(component_list, 0, COMPONENT_LIST_SIZE * sizeof(message_component));
}

message_component* add_component_message(object* p_object, const char* message)
{
	for (int i = 0; i < COMPONENT_LIST_SIZE; ++i)
	{
		if (usage_flag[i])
		{
			continue;
		}

		message_component* p_message = component_list + i;

		int result = add_component(p_object, MESSAGE, p_message);
		if (result < 0)
		{
			//unable to add component for some reason
			return 0;
		}

		//component successfully added
		usage_flag[i] = 1;
		//set member values
		p_message->p_message = message;
		return p_message;

	}
	return 0;
}

int remove_component_message(object* p_object)
{
	message_component* p_message = get_component(p_object, MESSAGE);
	size_t index = p_message - component_list;
	usage_flag[index] = 0;
	int result = remove_component(p_object, MESSAGE);
	return result;
}