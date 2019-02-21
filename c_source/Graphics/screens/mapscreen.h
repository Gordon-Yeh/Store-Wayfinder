#ifndef MAPSCREEN_H_
#define MAPSCREEN_H_

#include "screen.h"

void map_screen_init(void);

void map_screen_destroy(void);

void map_screen_draw(void);

screen_t map_screen_listen(void);

#endif