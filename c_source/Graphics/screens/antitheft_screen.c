#include "../Touchscreen.h"
#include "../../Security/tracker.h"
#include "screen.h"
#include "antitheft_screen.h"
#include "../components/textbox.h"
#include "../Colours.h"
#include "../Text.h"

static struct {
    TextBox * label_box;
    TextBox * instruct_box;
} _ANTITHEFT_SCREEN;

/**
 * initalize antitheft_screen
 * needs to be called before any other antitheft_screen functions
 */
void antitheft_screen_init(void) {
    _ANTITHEFT_SCREEN.label_box = textbox_create(SCREEN_X_OFFSET, 120, SCREEN_X_MAX, 120);
    _ANTITHEFT_SCREEN.instruct_box = textbox_create(SCREEN_X_OFFSET, 240, SCREEN_X_MAX, 120);
    textbox_set_text(_ANTITHEFT_SCREEN.label_box, "OUT OF BOUNDS", FONT5, RED);
    textbox_set_text(_ANTITHEFT_SCREEN.instruct_box, "Please Return The Device Back to The Store", FONT2, RED);
    textbox_set_box_colour(_ANTITHEFT_SCREEN.label_box, WHITE, WHITE);
    textbox_set_box_colour(_ANTITHEFT_SCREEN.instruct_box, WHITE, WHITE);
}

void antitheft_screen_destroy(void) {
    textbox_destroy(_ANTITHEFT_SCREEN.label_box);
    textbox_destroy(_ANTITHEFT_SCREEN.instruct_box);
}

/**
 *  draw the antitheft_screen on the map
 */
void antitheft_screen_draw(void) {
    textbox_draw(_ANTITHEFT_SCREEN.label_box);
    textbox_draw(_ANTITHEFT_SCREEN.instruct_box);
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