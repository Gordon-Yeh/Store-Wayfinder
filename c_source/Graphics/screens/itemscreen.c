#include "../components/textbox.h"
#include "../Colours.h"
#include "../Globalvars.h"
#include "../Text.h"
#include "../Touchscreen.h"

#include "screen.h"

static const int max_buttons_per_col = 5;
static const int max_col = 2;
static const int max_buttons = 10; // buttons_per_col * num_of_col

static const int col_gap = 8;
static const int row_gap = 10;
static const int base_x = 25;
static const int base_y = 60;
static const int button_length = 250;
static const int button_width = 75;

// every shape that should be plotted should go here
static struct {
    TextBox * item_buttons[10];
    int num_items;
	TextBox * back_button;
	TextBox * map_button;
} _ItemScreen;

//item screen can only be as big as (20,0) to (541, 479)
void item_screen_init(void) {
	char * items[15] = {
        "Appliances", "Bath", "Building Materials", "Decor & Blinds", "Electrical",
        "Floors & Area Rugs", "Furniture", "Hardware", "Paint", "Tools",
        "Kitchen", "Lighting & Fans", "Outdoors", "Storage & Organization", "Windows & Doors"
    };
	
	int item_added = 0;
    for (int col = 0; col < max_col; col++) {
        for (int row = 0; row < max_buttons_per_col; row++) {
            TextBox * b = textbox_create(
                base_x + col * (button_length + col_gap),
                base_y + row * (button_width + row_gap),
                button_length,
                button_width);

            textbox_set_box_colour(b, BLUE, FOREST_GREEN);
            textbox_set_text(b, items[item_added], FONT2, WHITE);

            _ItemScreen.item_buttons[item_added] = b;
            item_added++;
        }
    }
    _ItemScreen.num_items = item_added;

	//Back button
    TextBox * bb = textbox_create(base_x, 5, 100, 50);
	textbox_set_box_colour(bb, DARK_GRAY, DIM_GRAY);
	textbox_set_text(bb, "BACK", FONT2, WHITE);
    _ItemScreen.back_button = bb;
	
	//Map button
	TextBox * mapb = textbox_create(base_x+408, 5, 100, 50);
	textbox_set_box_colour(mapb, BLUE, BLUE);
	textbox_set_text(mapb, "MAP", FONT2, WHITE);
    _ItemScreen.map_button = mapb;
}

void item_screen_destroy(void) {
	for (int i = 0; i < _ItemScreen.num_items; i++) {
        textbox_destroy(_ItemScreen.item_buttons[i]);
    }
    textbox_destroy(_ItemScreen.back_button);
	textbox_destroy(_ItemScreen.map_button);
}

void item_screen_draw(void) {
	//Title
	CenteredSentence(FONT2, 20, 541, 0, 55, FOREST_GREEN, 0, "Select your Items", DONT_ERASE);
    for (int i = 0; i < _ItemScreen.num_items; i++) {
        textbox_draw(_ItemScreen.item_buttons[i]);
    }
    textbox_draw(_ItemScreen.back_button);
	textbox_draw(_ItemScreen.map_button);
}

screen_t item_screen_listen(void) {
	Point pp, pr;
    while (1) {
        pp = GetPress();
		pr = GetRelease();
        if (textbox_within(_ItemScreen.back_button, pr)) {
            return CATEGORIES;
        }
		else if (textbox_within(_ItemScreen.map_button, pr)) {
            return MAP;
        }
		else {
			//look through each item button to see if we add the item
			for(int i = 0; i < _ItemScreen.num_items; i++) {
				//Limit the number of items to 7 for now
				if(textbox_within(_ItemScreen.item_buttons[i], pr) && item_list_size < 7) {
					add_to_item_list(_ItemScreen.item_buttons[i]->text);
					return ITEM;
				}
			}
			//look through each item delete_button to see if we delete the item
			for(int j = 0; j < item_list_size; j++) {
				if(textbox_within(item_list[j]->delete_textbox, pr) && item_list_size > 0) {
					remove_from_item_list(j);
					return ITEM;
				}
			}
		}
	}
}
