#include <stdio.h>
#include "Colours.h"
#include "Screens.h"
#include "Text.h"
#include "Touchscreen.h"
#include "components/textbox.h"
#include "shapes/box.h"
#include "draw/draw.h"

void ResetScreen(void) {
	//Clear screen
	clear(WHITE);
	//Create outer border
	draw_square(20, 799, 0, 479, BLUE);
}

void HomeScreen(void) {
	ResetScreen();

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

	textbox_draw(new_list_button);
	textbox_draw(add_to_list_button);
	textbox_draw(map_button);
	textbox_draw(help_button);

	//Touchscreen
	Point p, p1;
	while (1) {
		p = GetPress();
		p1 = GetRelease(); //wait for a getrelease
		if (textbox_within(new_list_button, p1)) {
			// TODO:
		} else if (textbox_within(add_to_list_button, p1)) {
			ItemScreen();
		} else if (textbox_within(map_button, p1)) {
			// TODO:
		} else if (textbox_within(help_button, p1)) {
			// TODO:
		}
	}
}
