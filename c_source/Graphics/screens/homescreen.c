#include "../Colours.h"
#include "../Text.h"
#include "../components/textbox.h"
#include "../Touchscreen.h"

#include "screen.h"

// every shape that should be plotted should go here
static struct {
    TextBox * new_list_button;
    TextBox * add_to_list_button;
    TextBox * map_button;
    TextBox * help_button;
    // TODO: add all the component of homescreen here
} _HomeScreen;

int homescreen_init() {
    // declare and set all shapes and components on the screen here
    TextBox * new_list_button = textbox_create(30, 10, 760, 100);
	TextBox * add_to_list_button = textbox_create(30, 120, 760, 100);
	TextBox * map_button = textbox_create(30, 240, 760, 100);
	TextBox * help_button = textbox_create(30, 360, 760, 100);

	textbox_set_box_colour(new_list_button, BLUE, FOREST_GREEN);
	textbox_set_box_colour(add_to_list_button, BLUE, FOREST_GREEN);
	textbox_set_box_colour(map_button, BLUE, FOREST_GREEN);
	textbox_set_box_colour(help_button, BLUE, FOREST_GREEN);

	textbox_set_text(new_list_button, "Create New Shopping List", FONT2, WHITE);
	textbox_set_text(add_to_list_button, "Add To Shopping List", FONT2, WHITE);
	textbox_set_text(map_button, "Go To Map", FONT2, WHITE);
	textbox_set_text(help_button, "Help", FONT2, WHITE);

    _HomeScreen.new_list_button = new_list_button;
    _HomeScreen.add_to_list_button = add_to_list_button;
    _HomeScreen.map_button = map_button;
    _HomeScreen.help_button = help_button;
}

void homescreen_draw() {
    textbox_draw(_HomeScreen.new_list_button);
	textbox_draw(_HomeScreen.add_to_list_button);
	textbox_draw(_HomeScreen.map_button);
	textbox_draw(_HomeScreen.help_button);
}

screen_t homescreen_listen() {
	Point pp, pr;
    while (1) {
        pp = GetPress();
        pr = GetRelease(); //wait for a getrelease
        printf("touched (%d, %d) \n", pr.x, pr.y);
        if (textbox_within(_HomeScreen.new_list_button, pr)) {
            // TODO:
        } else if (textbox_within(_HomeScreen.add_to_list_button, pr)) {
            printf("switching to categories screen!");
            return CATEGORIES;
        } else if (textbox_within(_HomeScreen.map_button, pr)) {
            // TODO:
        } else if (textbox_within(_HomeScreen.help_button, pr)) {
            // TODO:
        }
	}
}
