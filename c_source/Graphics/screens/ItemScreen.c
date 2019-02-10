#include <stdio.h>
#include "Screens.h"
#include "../Text.h"
#include "../Colours.h"
#include "../Touchscreen.h"
#include "../shapes/box.h"

void ItemScreen(char category[]) {
	ResetScreen();
	// BackButton();
	
	CenteredSentence(FONT2, 20, 541, 0, 55, FOREST_GREEN, 0, "Select your Items", DONT_ERASE);
	
	/*temporary list from home depot
	********************************
	*/
	int list_size = 15; //will be dynamic data (max 15 categories)
	char *list[] = {"Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical", "Floors & Area Rugs", "Furniture", 
			"Hardware", "Kitchen", "Lighting & Fans", "Outdoors", "Paint", "Storage & Organization", "Tools", "Windows & Doors"};
	/******************************/
	
	// SidebarList(list, list_size);
	
	/*temporary items from home depot
	********************************
	*/
	int num_items = 10; //will be dynamic data (max 10)
	char *items[] = {"Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical", "Floors & Area Rugs", "Furniture", 
			"Hardware", "Kitchen", "Lighting & Fans"};
	/******************************/
	
	int i;
	//first column
	Box * first_column[5];
	for(i = 0; i < num_items && i < 5; i++) {
		first_column[i] = create_box(items[i], 26, 56+i*86, 252, 80, BLUE, FOREST_GREEN);
		draw_box(first_column[i]);
		CenteredSentence(FONT2, 26, 277, 56+i*86, 135+i*86, WHITE, 0, items[i], DONT_ERASE);
	}
	
	//second column
	Box * second_column[5];
	for(i = 0; i < (num_items - 5) && i < 5; i++) {
		second_column[i] = create_box(items[i], 284, 56+i*86, 252, 80, BLUE, FOREST_GREEN);
		draw_box(second_column[i]);
		CenteredSentence(FONT2, 284, 535, 56+i*86, 135+i*86, WHITE, 0, items[i+5], DONT_ERASE);
	}

	//Touchscreen
	Point p;
	while(1) {
		p = GetPress();
		printf("Press: x = %d, y = %d\n", p.x, p.y);
		GetRelease();
	}
}
