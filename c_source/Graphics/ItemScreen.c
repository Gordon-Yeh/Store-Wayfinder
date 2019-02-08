#include "Text.h"
#include "Colours.h"
#include "Touchscreen.h"
#include "Screens.h"

void ItemScreen(void) {
	ResetScreen();
	BackButton();
	
	CenteredSentence(FONT2, 20, 541, 0, 55, FOREST_GREEN, 0, "Select your Items", DONT_ERASE);
	
	/*temporary list from home depot
	********************************
	*/
	int list_size = 15; //will be dynamic data (max 15 categories)
	char *list[] = {"Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical", "Floors & Area Rugs", "Furniture", 
			"Hardware", "Kitchen", "Lighting & Fans", "Outdoors", "Paint", "Storage & Organization", "Tools", "Windows & Doors"};
	/******************************/
	
	SidebarList(list, list_size);
	
	/*temporary items from home depot
	********************************
	*/
	int num_items = 10; //will be dynamic data (max 10)
	char *items[] = {"Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical", "Floors & Area Rugs", "Furniture", 
			"Hardware", "Kitchen", "Lighting & Fans"};
	/******************************/
	
	int i;
	//first column
	for(i = 0; i < num_items && i < 5; i++) {
		BorderedBox(26, 277, 56+i*86, 135+i*86, BLUE, FOREST_GREEN);
		//Fill(27, 56+i*86+1, FOREST_GREEN, BLUE);
		CenteredSentence(FONT2, 26, 277, 56+i*86, 135+i*86, WHITE, 0, items[i], DONT_ERASE);
	}
	
	//second column
	for(i = 0; i < (num_items - 5) && i < 5; i++) {
		BorderedBox(284, 535, 56+i*86, 135+i*86, BLUE, FOREST_GREEN);
		//Fill(285, 56+i*86+1, FOREST_GREEN, BLUE);
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

void SidebarList(char *list[], int list_size) {
	int i;
	BorderedBox(542, 793, 6, 135+4*86, BLUE, FOREST_GREEN);
	CenteredSentence(FONT2, 542, 793, 6, 25, WHITE, 0, "Your List", DONT_ERASE);
	for(i = 0; i < list_size; i++) {
		CenteredSentence(FONT1, 542, 793, 56+i*86, 135+i*86, WHITE, 0, list[i], DONT_ERASE);
	}
}
