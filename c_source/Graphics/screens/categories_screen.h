#ifndef CATEGORIES_H_
#define CATEGORIES_H_

#include "screen.h"

/**
 * initalize categories_screen
 * needs to be called before any other categories_screen functions
 */
int categories_screen_init(void);

/**
 *  draw the categories_screen on the map
 */
void categories_screen_draw(void);

/**
 * polling for touch action from user
 * @return the screen to switch to due to user action
 */
screen_t categories_screen_listen(void);

#endif // CATEGORIES_H_
