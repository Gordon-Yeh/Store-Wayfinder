#include "../Touchscreen.h"
#include "../../Security/tracker.h"
#include "screen.h"
#include "antitheft_screen.h"
#include "../components/textbox.h"
#include "../Colours.h"
#include "../Text.h"

static struct {
    TextBox * box;
} _ANTITHEFT_SCREEN;

/**
 * initalize antitheft_screen
 * needs to be called before any other antitheft_screen functions
 */
void antitheft_screen_init(void) {
    _ANTITHEFT_SCREEN.box = textbox_create(0, SCREEN_X_MAX, 0, SCREEN_Y_MAX);
    textbox_set_text(_ANTITHEFT_SCREEN.box, "STEALING IS BAD", FONT3, BLACK);
    textbox_set_box_colour(_ANTITHEFT_SCREEN.box, BLACK, WHITE);
}

void antitheft_screen_destroy(void) {
    textbox_destroy(_ANTITHEFT_SCREEN.box);
}

/**
 *  draw the antitheft_screen on the map
 */
void antitheft_screen_draw(void) {
    textbox_draw(_ANTITHEFT_SCREEN.box);
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