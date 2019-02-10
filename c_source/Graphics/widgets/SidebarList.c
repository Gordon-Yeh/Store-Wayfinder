#include <stdio.h>
#include "../Globalvars.h"
#include "../Colours.h"
#include "../Text.h"
#include "../Touchscreen.h"
#include "../shapes/box.h"
#include "../draw/draw.h"

//MUST CALL SIDEBARLIST EVERYTIME A CHANGE IS MADE TO ITEM_LIST
void SidebarList(void) {
	/*temporary test data*/
	int j;
	item_list_size = 20;
	for(j = 0; j < 20; j++) {
		item_list[j] = create_item("this is an item", "category a", 50, 50);
	}
	/************************/
	
	Box * your_list_box = create_box("your_list", 542, 6, 252, 474, BLUE, FOREST_GREEN);
	draw_box(your_list_box);
	CenteredSentence(FONT2, 542, 793, 6, 25, WHITE, 0, "Your List", DONT_ERASE);
	
	int i;
	for(i = 0; i < item_list_size; i++) {
		//TODO: calculate spacing
		CenteredSentence(FONT2, 542, 793, 56+i*26, 75+i*26, WHITE, 0, item_list[i]->name, DONT_ERASE);
		
		item_list[i]->delete_box = create_box(item_list[i]->name, 542, 56+i*26, 252, 20, RED, RED);
		//draw_box(item_list[i]->delete_box);
	}
	
	//must free all boxes after
}