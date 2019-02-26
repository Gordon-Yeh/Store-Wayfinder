#include "../Colours.h"
#include "../Text.h"
#include "../components/textbox.h"
#include "../Touchscreen.h"

#include "screen.h"

static const int base_x = 25;
static const int base_y = 60;

static struct {
    TextBox * back_button;
} _HelpScreen;

void help_screen_init() {
    TextBox * bb = textbox_create(base_x, 5, 100, 50);
	textbox_set_box_colour(bb, DARK_GRAY, DIM_GRAY);
	textbox_set_text(bb, "BACK", FONT2, WHITE);
    _HelpScreen.back_button = bb;
}

void help_screen_draw(void) {
	// FONT2 has height 14 and width 10
	CenteredSentence(FONT2, 30, 789, 0, 55, FOREST_GREEN, 0, "How to use this system", DONT_ERASE);
	char * sentences[] = {
		"1. Home Menu", 
					"   - To create a new, empty shopping list, tap on the \"Create New ",
					"     Shopping List\" button",
					"   - To add to the existing shopping list, tap on the \"Add To ",
					"     Shopping List\" button",
					"   - To access a view of the store map, tap on the \"Go To Map\" button",
					"   - To access this help menu, tap on the \"Help\" button",
		"",
		"2. Category Screen", 
					"   - To search for an item, first tap on the category that the item ",
					"     is in",
		"",
		"3. Item Screen", 
					"   - To add an item to your list, tap on the item on the left display", 
					"   - To remove an item from your list, tap on the \"X\" button next to ",
					"     the item on the right display",
					"   - To browse through your list, tap the previous and next page ",
					"     buttons on the right display",
					"   - When you are done adding items to your shopping list, tap the ",
					"     \"MAP\" button",
		"",
		"4. Map Screen", 
					"   - A map of the store is displayed with your location and the ",
					"     locations of the items in your list"};
	int sentences_size = 24;
	Paragraph(base_x, base_y, FOREST_GREEN, 0, sentences, sentences_size, DONT_ERASE);
	
	textbox_draw(_HelpScreen.back_button);
}

screen_t help_screen_listen(void) {
	Point pp, pr;
    while (1) {
        pp = GetPress();
		pr = GetRelease();
        if (textbox_within(_HelpScreen.back_button, pr)) {
            return HOME;
        }
	}
}
