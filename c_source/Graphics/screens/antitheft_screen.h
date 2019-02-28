#ifndef ANTITHEFT_H_
#define ANTITHEFT_H_

#include "screen.h"

/**
 * initalize antitheft_screen
 * needs to be called before any other antitheft_screen functions
 */
void antitheft_screen_init(void);

void antitheft_screen_destroy(void);

/**
 *  draw the antitheft_screen on the map
 */
void antitheft_screen_draw(void);

/**
 * polling for touch action from user
 * @return the screen to switch to due to user action
 */
screen_t antitheft_screen_listen(void);

#endif // ANTITHEFT_H_
