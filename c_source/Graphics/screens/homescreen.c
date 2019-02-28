#include "../Colours.h"
#include "../Globalvars.h"
#include "../Text.h"
#include "../components/textbox.h"
#include "../Touchscreen.h"

#include <stdio.h>

#include "screen.h"

// every shape that should be plotted should go here
static struct {
    TextBox * new_list_button;
    TextBox * help_button;
    // TODO: add all the component of homescreen here
} _HomeScreen;

void homescreen_init() {
    // declare and set all shapes and components on the screen here
	TextBox * new_list_button = textbox_create(30, 150, 760, 150);
	TextBox * help_button = textbox_create(30, 325, 760, 150);

	textbox_set_box_colour(new_list_button, BLUE, FOREST_GREEN);
	textbox_set_box_colour(help_button, BLUE, FOREST_GREEN);

	textbox_set_text(new_list_button, "Start Shopping List", FONT3, WHITE);
	textbox_set_text(help_button, "Help", FONT3, WHITE);

    _HomeScreen.new_list_button = new_list_button;
    _HomeScreen.help_button = help_button;
}

void homescreen_draw() {
	CenteredSentence(FONT5, 30, 789, 0, 150, FOREST_GREEN, 0, "Store Wayfinder", DONT_ERASE);
    textbox_draw(_HomeScreen.new_list_button);
	textbox_draw(_HomeScreen.help_button);
}

screen_t homescreen_listen() {
	Point pp, pr;
    while (1) {
        pp = GetPress();
		pr = GetRelease();

        if (textbox_within(_HomeScreen.new_list_button, pr)) {
			//Free item_list memory
			return CATEGORIES;
        } else if (textbox_within(_HomeScreen.help_button, pr)) {
            return HELP;
        }
	}
}
