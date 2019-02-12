#ifndef HOMESCREENS_H_
#define HOMESCREENS_H_

#include "screens.h"
#include "../shapes/box.h"

static struct {
    // TODO: add all the component of homescreen here
    Box * new_list_box;
    Box * add_to_list_box;
    Box * map_box;
    Box * help_box;
} _HomeScreen;

/**
 * initalize homescreen
 * needs to be called before any other homescreen functions
 */
int homescreen_init(void);

/**
 *  draw the homescreen on the map
 */
void homescreen_draw(void);

/**
 * polling for touch action from user
 * @return the screen to switch to due to user action
 */
screen_t homescreen_listen(void);

#endif // HOMESCREENS_H_