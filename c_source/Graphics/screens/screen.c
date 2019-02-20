#include "../Colours.h"
#include "../draw/draw.h"

#include "screen.h"
#include "homescreen.h"
#include "categories_screen.h"
#include "itemscreen.h"

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
	//item_screen_init(); //changing
	//map_screen_init();
	//help_screen_init();
	//antitheft_screen_init();
	
    // TODO: call other screen init functions here
}

void screen_draw(screen_t screen) {
    reset_screen();
    switch (screen) {
        case HOME:       homescreen_draw(); break;
        case CATEGORIES: categories_screen_draw(); break;
		case ITEM: {
			//item_screen is changing
			item_screen_init();
			//draw the sidebarlist and the item screen
			item_screen_draw(); 
			sidebarlist_draw(); 
		}
		break;
		
        // TODO: add more screens
        default: homescreen_draw(); break;
    }
}

screen_t screen_listen(screen_t curr_screen) {
	screen_t next_screen;
    switch (curr_screen) {
        case HOME:       
			next_screen = homescreen_listen();
		break;
        case CATEGORIES: 
			next_screen = categories_screen_listen();
		break;
		case ITEM: {
			//item_screen is changing
			next_screen = item_screen_listen();
			item_screen_destroy();
		}	
		break;
        // TODO: add more screens
        default: return HOME;
    }
	return next_screen;
}
