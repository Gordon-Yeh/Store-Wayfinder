#include "../Colours.h"
#include "../draw/draw.h"
#include "../item/plot_items.h"
#include "../../Security/tracker.h"

#include "screen.h"
#include "homescreen.h"
#include "categories_screen.h"
#include "itemscreen.h"
#include "mapscreen.h"
#include "helpscreen.h"
#include "antitheft_screen.h"

#include "../widgets/widgets.h"

void reset_screen() {
	//Clear screen
	clear(WHITE);
	//Create outer border
	draw_square(20, 799, 0, 479, BLUE);
}

void screen_init() {
    homescreen_init();
    categories_screen_init();
	map_screen_init();
	help_screen_init();
}

void screen_draw(screen_t screen) {
    switch (screen) {
        case HOME: {
			reset_screen();
			homescreen_draw();
		} break;
        case CATEGORIES: {
			reset_screen();
			categories_screen_draw(); 
		} break;
		case ITEM: {
			reset_screen();
			//item_screen is changing
			item_screen_init();
			//draw the sidebarlist and the item screen
			item_screen_draw(); 
			sidebarlist_draw(); 
		} break;
		case ITEM_SIDEBAR: {
			sidebarlist_draw();
		} break;
		case MAP: {
			reset_screen();
			map_screen_draw();
			plot_items();
			sidebarlist_draw();
		} break;
		case MAP_SIDEBAR: {
			plot_items();
			sidebarlist_draw();
		} break;
		case HELP: {
			reset_screen();
			help_screen_draw();
		} break;

		case THIEF: {  //TODO: should draw the screen after it's implemented 
			reset_screen();
		} break;
		
        // TODO: add more screens
        default: {
			reset_screen(); 
			homescreen_draw(); 
		} break;
    }
}

screen_t screen_listen(screen_t curr_screen) {
	screen_t next_screen;
    switch (curr_screen) {
        case HOME: {   
			next_screen = homescreen_listen();
		} break;
        case CATEGORIES: {
			next_screen = categories_screen_listen();
		} break;
		case ITEM: {
			//item_screen is changing
			next_screen = item_screen_listen();
			// Free the item_screen memory unless we're only updating the sidebar
			if(next_screen != ITEM_SIDEBAR)
				item_screen_destroy();
		} break;
		case ITEM_SIDEBAR: {
			next_screen = item_screen_listen();
			// Free the item_screen memory unless we're only updating the sidebar
			if(next_screen != ITEM_SIDEBAR)
				item_screen_destroy();
		} break;
		case MAP: {
			next_screen = map_screen_listen();
		} break;
		case MAP_SIDEBAR: {
			next_screen = map_screen_listen();
		} break;
		case HELP: {
			next_screen = help_screen_listen();
		} break;
		
		case THIEF: {
			next_screen = antitheft_screen_listen();
		} break;

        default: {
			next_screen = HOME;
		}
    }

	if (tracker_get_status() == OUT_OF_BOUND)
		next_screen = THIEF;

	return next_screen;
}
