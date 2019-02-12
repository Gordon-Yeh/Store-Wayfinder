#ifndef SCREEN_H_
#define SCREEN_H_

typedef enum screen {
    HOME,
    ITEM
} screen_t;

/**
 * initalize screen
 * needs to be called before any other screen functions
 */
void screen_init();

/**
 * change the LCD display to a different screen
 * @param next_screen the screen to change to
 */
void screen_switch(screen_t next_screen);

/**
 * polling for touch action from user
 * @param curr_screen the screen that's being displayed right now
 * @return the screen to switch to due to user action
 */
screen_t screen_listen(screen_t curr_screen);

#endif // SCREEN_H_
