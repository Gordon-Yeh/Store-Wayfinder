#include "Basics.h"
#include "Colours.h"
#include "Fill.h"
#include "Screens.h"
#include "Text.h"
#include "Touchscreen.h"

void ResetScreen(void) {
	//Clear screen
	Clear(WHITE);
	//Create outer border
	Box(20, 799, 0, 479, BLUE);
}

void HomeMenu(void) {
	ResetScreen();
	
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
	Point p;
	while(1) {
		p = GetPress();
		printf("Press: x = %d, y = %d\n", p.x, p.y);
		GetRelease();
		//printf("Release: x = %d, y = %d\n", p.x, p.y);
		// if(p.x > 30 && p.x < 789 && p.y > 10 && p.y < 109) {
			// SearchScreen();
			// break;
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

void SearchScreen(void) {
	ResetScreen();
	BackButton();
	
	CenteredSentence(FONT2, 30, 789, 0, 55, FOREST_GREEN, 0, "Search By Category", DONT_ERASE);
	
	//temporary data from home depot
	int num_categories = 15; //will be dynamic data (max 15 categories)
	int i;
	char *categories[] = {"Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical", "Floors & Area Rugs", "Furniture", 
			"Hardware", "Kitchen", "Lighting & Fans", "Outdoors", "Paint", "Storage & Organization", "Tools", "Windows & Doors"};
	
	//first column
	for(i = 0; i < num_categories && i < 5; i++) {
		Box(26, 277, 56+i*86, 135+i*86, BLUE);
		Fill(27, 56+i*86+1, FOREST_GREEN, BLUE);
		CenteredSentence(FONT2, 26, 277, 56+i*86, 135+i*86, WHITE, 0, categories[i], DONT_ERASE);
	}
	
	//second column
	for(i = 0; i < (num_categories - 5) && i < 5; i++) {
		Box(284, 535, 56+i*86, 135+i*86, BLUE);
		Fill(285, 56+i*86+1, FOREST_GREEN, BLUE);
		CenteredSentence(FONT2, 284, 535, 56+i*86, 135+i*86, WHITE, 0, categories[i+5], DONT_ERASE);
	}
	
	//third column
	for(i = 0; i < (num_categories - 10) && i < 5; i++) {
		Box(542, 793, 56+i*86, 135+i*86, BLUE);
		Fill(543, 56+i*86+1, FOREST_GREEN, BLUE);
		CenteredSentence(FONT2, 542, 793, 56+i*86, 135+i*86, WHITE, 0, categories[i+10], DONT_ERASE);
	}
}

//Widgets
void BackButton(void) {
	Box(26, 75, 3, 52, BLUE);
	//TODO
}

void SidebarList(char *list[], int list_size) {
	
}