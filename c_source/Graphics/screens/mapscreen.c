//map screen can only be as big as (20,0) to (541, 479)
//map dimensions: 518x418

#include <stdlib.h>

#include "../components/textbox.h"
#include "../Colours.h"
#include "../draw/DrawMap.h"
#include "../item/plot_items.h"
#include "../Globalvars.h"
#include "../Text.h"
#include "../Touchscreen.h"
#include "mapscreen.h"
#include "screen.h"
#include "../../Bluetooth/query.h"
#include "../draw/DrawImages.h"

static const int base_x = 25;

static const int map_base_x = 22;
static const int map_base_y = 60;

// every shape that should be plotted should go here
static struct {
	TextBox * back_button;
	TextBox * done_button;
} _MapScreen;

void map_screen_init(void) {
	//Back button
    TextBox * bb = textbox_create(base_x, 5, 100, 50);
	textbox_set_box_colour(bb, DARK_GRAY, DIM_GRAY);
	textbox_set_text(bb, "BACK", FONT2, WHITE);
    _MapScreen.back_button = bb;
	
	//Done button
	TextBox * doneb = textbox_create(base_x+408, 5, 100, 50);
	textbox_set_box_colour(doneb, BLUE, BLUE);
	textbox_set_text(doneb, "DONE", FONT2, WHITE);
    _MapScreen.done_button = doneb;
}

void map_screen_destroy(void) {
    textbox_destroy(_MapScreen.back_button);
	textbox_destroy(_MapScreen.done_button);
}

/**
 * @returns 1 : if p would be located in the map domain
 */ 
static int is_in_map(Point * p) {
    return (p->x > PERSON_HALF_WIDTH) 
        && (p->y > PERSON_HALF_HEIGHT) 
        && (p->x < MAP_WIDTH - PERSON_HALF_WIDTH) 
        && (p->y < MAP_HEIGHT - PERSON_HALF_HEIGHT);
}

static void plot_location(Point * p, int colour) {
    Person(MAP_BASE_X, MAP_BASE_Y, p->x, p->y, colour);
}

static void refill_location(Point * p) {
    DrawMapSection(MAP_BASE_X, MAP_BASE_Y, p->x, p->y);
}

void map_screen_draw(void) {
	//Title
	CenteredSentence(FONT2, 20, 541, 0, 55, FOREST_GREEN, 0, "Store Map", DONT_ERASE);
	DrawMap(map_base_x, map_base_y);
    textbox_draw(_MapScreen.back_button);
	textbox_draw(_MapScreen.done_button);
}

screen_t map_screen_listen(void) {
	Point pp, pr;
	Point *prev_p, *curr_p;
	Point *p = malloc(sizeof(Point));
	p->x = 50;
	p->y = 50;
	prev_p = p;
    while (1) {
		curr_p = query_map_position();
		if (curr_p && is_in_map(curr_p)) {
			refill_location(prev_p);
			plot_location(curr_p, RED);
			free(prev_p);
			prev_p = curr_p;
		}

        pp = GetPress();
		pr = GetRelease();

        if (textbox_within(_MapScreen.back_button, pr)) {
			// location_plotter_end();
            return ITEM;
        }
		else if (textbox_within(_MapScreen.done_button, pr)) {
			//Free item_list memory
			for(int i = 0; i < item_list_size; i++) {
				destroy_item(item_list[i]);
			}
			//Set the global item_list_size to 0
            item_list_size = 0;
			// location_plotter_end();
            return HOME;
        }
		else if (within_box(prev_page, pr)) {
			//	Cannot have a pagenum less than 0
			if(pagenum > 0) {
				pagenum--;
				return MAP_SIDEBAR;
			}
		}
		else if (within_box(next_page, pr)) {
			// Cannot have a pagenum greater than the (number of items - 1)/ pagesize rounded down
			if(pagenum < (item_list_size - 1)/pagesize) {
				pagenum++;
				return MAP_SIDEBAR;
			}
		}
		else {
			//look through each item delete_button to see if we delete the item
			for(int j = 0; j < item_list_size; j++) {
				if(textbox_within(item_list[j]->delete_textbox, pr)) {
					unplot_item(j);
					remove_from_item_list(j);
					return MAP_SIDEBAR;
				}
			}
		}
	}
}
