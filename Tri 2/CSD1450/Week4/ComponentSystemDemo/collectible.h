#ifndef __COLLECTIBLE_H__
#define __COLLECTIBLE_H__

#include "cprocessing.h"

typedef struct {
	CP_Vector position;
	float diameter;
} collectible_t;

typedef struct {
	collectible_t collectibles[5];
	size_t collectible_count;
} collectible_list_t;

void add_collectible(collectible_list_t* cl, float x, float y);
void render_collectibles(collectible_list_t* cl);
void collide_character_with_collectibles(character_t* c, collectible_list_t* cl);



#endif // __COLLECTIBLE_H__