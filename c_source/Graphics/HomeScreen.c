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

void HomeScreen(void) {
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
			ItemScreen();
			break;
		} else if(p.x > 30 && p.x < 789 && p.y > 120 && p.y < 229) {
			ItemScreen();
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
