#include <stdio.h>
#include "Colours.h"
#include "Screens.h"
#include "Text.h"
#include "Touchscreen.h"
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
	
	Box * new_list_box = create_box(30, 10, 760, 100, BLUE, FOREST_GREEN);
	Box * add_to_list_box = create_box(30, 120, 760, 100, BLUE, FOREST_GREEN);
	Box * map_box = create_box(30, 240, 760, 100, BLUE, FOREST_GREEN);
	Box * help_box = create_box(30, 360, 760, 100, BLUE, FOREST_GREEN);

	draw_box(new_list_box);
	draw_box(add_to_list_box);
	draw_box(map_box);
	draw_box(help_box);

	CenteredSentence(FONT2, 30, 789, 10, 109, WHITE, 0, "Create New Shopping List", DONT_ERASE);
	CenteredSentence(FONT2, 30, 789, 120, 229, WHITE, 0, "Add To Shopping List", DONT_ERASE);
	CenteredSentence(FONT2, 30, 789, 240, 349, WHITE, 0, "Go To Map", DONT_ERASE);
	CenteredSentence(FONT2, 30, 789, 360, 469, WHITE, 0, "Help", DONT_ERASE);
	
	//Touchscreen
	Point p, p1;
	while (1) {
		p = GetPress();
		printf("Press: x = %d, y = %d\n", p.x, p.y);
		p1 = GetRelease(); //wait for a getrelease
		printf("Release: x = %d, y = %d\n", p1.x, p1.y);
		if (within_box(new_list_box, p)) {
			// ItemScreen();
			break;
		} else if (within_box(add_to_list_box, p)) {
			ItemScreen();
			break;
		} else if (within_box(map_box, p)) {
			break;
		} else if (within_box(help_box, p)) {
			break;
		}
	}
}
