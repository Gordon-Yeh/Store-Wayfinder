#include "../Globalvars.h"
#include "../Colours.h"
#include "../Text.h"
#include "../shapes/box.h"
#include "../item/item.h"

//MUST CALL SIDEBARLIST EVERYTIME A CHANGE IS MADE TO ITEM_LIST
void sidebarlist_draw(void) {
	Box * your_list_box = create_box(542, 6, 252, 474, BLUE, FOREST_GREEN);
	draw_box(your_list_box);
	destroy_box(your_list_box); //no need for the coordinates anymore
	CenteredSentence(FONT2, 542, 793, 0, 55, WHITE, 0, "Your List", DONT_ERASE);
	
	// Draw boxes depending on which page the user is on
	// ie. If page 0, draw items 0 to 6 or less
	// ie. If page 1, draw items 7 to 13 or less
	for(int i = pagenum*pagesize; i < ((pagenum+1)*pagesize) && i < item_list_size; i++) {
		textbox_draw(item_list[i]->delete_textbox);
		textbox_draw(item_list[i]->delete_icon);
	}
}