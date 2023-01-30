#include <assert.h>
#include "shared.h"
#include "character.h"
#include "collectible.h"


void add_collectible(collectible_list_t* cl, float x, float y) {
	assert(cl->collectible_count < array_count(cl->collectibles));
	collectible_t* c = cl->collectibles + cl->collectible_count++;
	c->position.x = x;
	c->position.y = y;
	c->diameter = 20.f;
}

void render_collectibles(collectible_list_t* cl) {
	for (size_t collectible_index = 0; collectible_index < cl->collectible_count; ++collectible_index)
	{
		collectible_t* c = cl->collectibles + collectible_index;
		CP_Settings_Fill(CP_Color_Create(255, 125, 125, 255));
		CP_Settings_Stroke(CP_Color_Create(255 / 2, 125 / 2, 125 / 2, 255));

		CP_Graphics_DrawCircle(c->position.x, c->position.y, c->diameter);
	}
}

void collide_character_with_collectibles(character_t* c, collectible_list_t* cl) {
	for (size_t collectible_index = 0; collectible_index < cl->collectible_count; )
	{
		collectible_t* collectible = cl->collectibles + collectible_index;
		if (is_circle_in_circle(
			collectible->position.x, collectible->position.y, collectible->diameter,
			c->position.x, c->position.y, c->diameter))
		{
			// remove from list by replacing it with collectible in the back, since order doesn't matter
			cl->collectibles[collectible_index] = cl->collectibles[--cl->collectible_count];

			// notify!
			notify_observers(c, CHARACTER_EVENT_COLLECTIBLE);

			// in this case, we don't increase collectible index
		}
		else {
			++collectible_index;
		}
	}
}

