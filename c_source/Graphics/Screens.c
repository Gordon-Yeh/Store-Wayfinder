#include "Basics.h"
#include "Colours.h"
#include "Fill.h"
#include "Screens.h"
#include "Text.h"
#include "Touchscreen.h"

#include <stdio.h>

void ResetScreen(void) {
	//Clear screen
	Clear(WHITE);
	//Create outer border
	Box(20, 799, 0, 479, BLUE);
}

void HomeMenu(void) {
	ResetScreen();
	
	// BorderedBox(30, 789, 10, 109, BLUE, FOREST_GREEN);
	// BorderedBox(30, 789, 120, 229, BLUE, FOREST_GREEN);
	// BorderedBox(30, 789, 240, 349, BLUE, FOREST_GREEN);
	// BorderedBox(30, 789, 360, 469, BLUE, FOREST_GREEN);
	Box(30, 789, 10, 109, BLUE);
	Box(30, 789, 120, 229, BLUE);
	Box(30, 789, 240, 349, BLUE);
	Box(30, 789, 360, 469, BLUE);
	Fill(31, 11, FOREST_GREEN, BLUE);
	Fill(31, 121, FOREST_GREEN, BLUE);
	Fill(31, 241, FOREST_GREEN, BLUE);
	Fill(31, 361, FOREST_GREEN, BLUE);
	CenteredSentence(FONT2, 30, 789, 10, 109, WHITE, 0, "Create New Shopping List", DONT_ERASE);
	CenteredSentence(FONT2, 30, 789, 120, 229, WHITE, 0, "Add To Shopping List", DONT_ERASE);
	CenteredSentence(FONT2, 30, 789, 240, 349, WHITE, 0, "Go To Map", DONT_ERASE);
	CenteredSentence(FONT2, 30, 789, 360, 469, WHITE, 0, "Help", DONT_ERASE);
	
	//Touchscreen
	Point p, p1;
	while(1) {
		p = GetPress();
		printf("Press: x = %d, y = %d\n", p.x, p.y);
		p1 = GetRelease(); //wait for a getrelease
		printf("Release: x = %d, y = %d\n", p1.x, p1.y);
		if(p.x > 30 && p.x < 789 && p.y > 10 && p.y < 109) {
			SearchScreen();
			break;
		} else if(p.x > 30 && p.x < 789 && p.y > 120 && p.y < 229) {
			SearchScreen();
			break;
		} else if(p.x > 30 && p.x < 789 && p.y > 240 && p.y < 349) {
			break;
		} else if(p.x > 30 && p.x < 789 && p.y > 360 && p.y < 469) {
			break;
		}
	}
}

void SearchScreen(void) {
	ResetScreen();
	BackButton();
	
	CenteredSentence(FONT2, 30, 789, 0, 55, FOREST_GREEN, 0, "Search By Category", DONT_ERASE);
	
	/*temporary data from home depot
	********************************
	*/
	int num_categories = 15; //will be dynamic data (max 15 categories)
	char *categories[] = {"Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical", "Floors & Area Rugs", "Furniture", 
			"Hardware", "Kitchen", "Lighting & Fans", "Outdoors", "Paint", "Storage & Organization", "Tools", "Windows & Doors"};
	/******************************/
	
	int i;
	//first column
	for(i = 0; i < num_categories && i < 5; i++) {
		// BorderedBox(26, 277, 56+i*86, 135+i*86, BLUE, FOREST_GREEN);
		Box(26, 277, 56+i*86, 135+i*86, BLUE);
		Fill(27, 56+i*86+1, FOREST_GREEN, BLUE);
		CenteredSentence(FONT2, 26, 277, 56+i*86, 135+i*86, WHITE, 0, categories[i], DONT_ERASE);
	}
	
	//second column
	for(i = 0; i < (num_categories - 5) && i < 5; i++) {
		// BorderedBox(284, 535, 56+i*86, 135+i*86, BLUE, FOREST_GREEN);
		Box(284, 535, 56+i*86, 135+i*86, BLUE);
		Fill(285, 56+i*86+1, FOREST_GREEN, BLUE);
		CenteredSentence(FONT2, 284, 535, 56+i*86, 135+i*86, WHITE, 0, categories[i+5], DONT_ERASE);
	}
	
	//third column
	for(i = 0; i < (num_categories - 10) && i < 5; i++) {
		// BorderedBox(542, 793, 56+i*86, 135+i*86, BLUE, FOREST_GREEN);
		Box(542, 793, 56+i*86, 135+i*86, BLUE);
		Fill(543, 56+i*86+1, FOREST_GREEN, BLUE);
		CenteredSentence(FONT2, 542, 793, 56+i*86, 135+i*86, WHITE, 0, categories[i+10], DONT_ERASE);
	}
	
	//Touchscreen
	Point p;
	while(1) {
		p = GetPress();
		printf("Press: x = %d, y = %d\n", p.x, p.y);
		GetRelease();
		if(p.x > 26 && p.x < 75 && p.y > 3 && p.y < 52) {
			HomeMenu();
			break;
		}
		// } else if(p.x > 30 && p.x < 789 && p.y > 120 && p.y < 229) {
			// SearchScreen();
			// break;
		// } else if(p.x > 30 && p.x < 789 && p.y > 240 && p.y < 349) {
			// break;
		// } else if(p.x > 30 && p.x < 789 && p.y > 360 && p.y < 469) {
			// break;
		// }
	}
}

void ItemSelectScreen(void) {
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
		if(p.x > 30 && p.x < 789 && p.y > 10 && p.y < 109) {
			SearchScreen();
			break;
		} else if(p.x > 30 && p.x < 789 && p.y > 120 && p.y < 229) {
			SearchScreen();
			break;
		} else if(p.x > 30 && p.x < 789 && p.y > 240 && p.y < 349) {
			break;
		} else if(p.x > 30 && p.x < 789 && p.y > 360 && p.y < 469) {
			break;
		}
	}
}

//Widgets
void BackButton(void) {
	Box(26, 75, 3, 52, BLUE);
	//TODO
}

void SidebarList(char *list[], int list_size) {
	int i;
	BorderedBox(542, 793, 6, 135+4*86, BLUE, FOREST_GREEN);
	CenteredSentence(FONT2, 542, 793, 6, 25, WHITE, 0, "Your List", DONT_ERASE);
	for(i = 0; i < list_size; i++) {
		CenteredSentence(FONT1, 542, 793, 56+i*86, 135+i*86, WHITE, 0, list[i], DONT_ERASE);
	}
}