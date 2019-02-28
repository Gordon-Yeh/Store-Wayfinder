#include "../Touchscreen.h"
#include "../../Security/tracker.h"
#include "screen.h"
#include "antitheft_screen.h"

/**
 * initalize antitheft_screen
 * needs to be called before any other antitheft_screen functions
 */
void antitheft_screen_init(void) {
    // TODO: add components
}

void antitheft_screen_destroy(void) {
    // TODO:
}

/**
 *  draw the antitheft_screen on the map
 */
void antitheft_screen_draw(void) {
    // TODO:
}

/**
 * polling for touch action from user
 * @return the screen to switch to due to user action
 */
screen_t antitheft_screen_listen(void) {
	Point pp, pr;
    while (1) {
        if (tracker_get_status() == IN_BOUND) {
            return HOME;
        }
	}
}