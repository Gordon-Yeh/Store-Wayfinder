#include <stdio.h>
#include "Screens.h"
#include "../Text.h"
#include "../Colours.h"
#include "../Touchscreen.h"
#include "../shapes/box.h"
#include "../widgets/widgets.h"

void ItemScreen(char category[]) {
	ResetScreen();
	Box * back_box = BackButton();
	
	CenteredSentence(FONT2, 20, 541, 0, 55, FOREST_GREEN, 0, "Select your Items", DONT_ERASE);
	
	SidebarList();
	
	/*temporary items from home depot
	********************************
	*/
	int num_items = 10; //will be dynamic data (max 10)
	char *items[] = {"Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical", "Floors & Area Rugs", "Furniture", 
			"Hardware", "Kitchen", "Lighting & Fans"};
	/******************************/
	
	int i;
	//first column
	Box * item_boxes[num_items];
	for(i = 0; i < num_items && i < 5; i++) {
		item_boxes[i] = create_box(items[i], 26, 56+i*86, 252, 80, BLUE, FOREST_GREEN);
		draw_box(item_boxes[i]);
		CenteredSentence(FONT2, 26, 277, 56+i*86, 135+i*86, WHITE, 0, items[i], DONT_ERASE);
	}
	
	//second column
	for(i = 0; i < (num_items - 5) && i < 5; i++) {
		item_boxes[i] = create_box(items[i], 284, 56+i*86, 252, 80, BLUE, FOREST_GREEN);
		draw_box(item_boxes[i]);
		CenteredSentence(FONT2, 284, 535, 56+i*86, 135+i*86, WHITE, 0, items[i+5], DONT_ERASE);
	}

	//Touchscreen
	Point p;
	while(1) {
		p = GetPress();
		printf("Press: x = %d, y = %d\n", p.x, p.y);
		GetRelease();
		if(within_box(back_box, p)) {
			HomeScreen();
			break;
		}
		else {
			for(i = 0; i < num_items; i++) {
				if (within_box(item_boxes[i], p)) {
					//TODO: add item to list
					ItemScreen(category);
					break;
				}
			}
		}
	}
	
	destroy_box(back_box);
	for(i = 0; i < num_items; i++) {
		destroy_box(item_boxes[i]);
	}
}
