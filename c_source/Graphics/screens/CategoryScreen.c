#include <stdio.h>
#include "Screens.h"
#include "../Text.h"
#include "../Colours.h"
#include "../Touchscreen.h"
#include "../shapes/box.h"

void CategoryScreen(void) {
	ResetScreen();
	//BackButton();
	
	CenteredSentence(FONT2, 30, 789, 0, 55, FOREST_GREEN, 0, "Search By Category", DONT_ERASE);
	
	/*temporary data from home depot
	********************************
	*/
	int num_categories = 15; //will be dynamic data (max 15 categories)
	char *categories[] = {"Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical", "Floors & Area Rugs", "Furniture", 
			"Hardware", "Kitchen", "Lighting & Fans", "Outdoors", "Paint", "Storage & Organization", "Tools", "Windows & Doors"};
	/******************************/
	
	int i;
	Box * category_boxes[num_categories];
	//first column
	for(i = 0; i < num_categories && i < 5; i++) {
		category_boxes[i] = create_box(categories[i], 26, 56+i*86, 252, 80, BLUE, FOREST_GREEN);
		draw_box(category_boxes[i]);
		CenteredSentence(FONT2, 26, 277, 56+i*86, 135+i*86, WHITE, 0, categories[i], DONT_ERASE);
	}
	
	//second column
	for(i = 0; i < (num_categories - 5) && i < 5; i++) {
		category_boxes[i+5] = create_box(categories[i], 284, 56+i*86, 252, 80, BLUE, FOREST_GREEN);
		draw_box(category_boxes[i+5]);
		CenteredSentence(FONT2, 284, 535, 56+i*86, 135+i*86, WHITE, 0, categories[i+5], DONT_ERASE);
	}
	
	//third column
	for(i = 0; i < (num_categories - 10) && i < 5; i++) {
		category_boxes[i+10] = create_box(categories[i], 542, 56+i*86, 252, 80, BLUE, FOREST_GREEN);
		draw_box(category_boxes[i+10]);
		CenteredSentence(FONT2, 542, 793, 56+i*86, 135+i*86, WHITE, 0, categories[i+10], DONT_ERASE);
	}
	
	//Touchscreen
	Point p;
	while(1) {
		p = GetPress();
		printf("Press: x = %d, y = %d\n", p.x, p.y);
		GetRelease();
		for(i = 0; i < num_categories; i++) {
			if (within_box(category_boxes[i], p)) {
				ItemScreen(category_boxes[i]->name); //pass name of the category to itemscreen
				break;
			}
		}
	}
}