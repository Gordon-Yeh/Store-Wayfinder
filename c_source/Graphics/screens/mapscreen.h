#ifndef MAPSCREEN_H_
#define MAPSCREEN_H_

#include "screen.h"

#define MAP_BASE_X 22
#define MAP_BASE_Y 60

void map_screen_init(void);

void map_screen_destroy(void);

void map_screen_draw(void);

screen_t map_screen_listen(void);

#endif