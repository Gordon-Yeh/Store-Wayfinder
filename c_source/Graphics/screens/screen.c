#include "../Colours.h"
#include "../draw/draw.h"

#include "screen.h"
#include "homescreen.h"
#include "categories_screen.h"

void reset_screen() {
	//Clear screen
	clear(WHITE);
	//Create outer border
	draw_square(20, 799, 0, 479, BLUE);
}

void screen_init() {
    homescreen_init();
    categories_screen_init();
    // TODO: call other screen init functions here
}

void screen_draw(screen_t screen) {
    reset_screen();
    switch (screen) {
        case HOME:       homescreen_draw(); break;
        case CATEGORIES: categories_screen_draw(); break;
        // TODO: add more screens
        default:
    }
}

screen_t screen_listen(screen_t curr_screen) {
    switch (curr_screen) {
        case HOME:       return homescreen_listen();
        case CATEGORIES: return categories_screen_listen();
        // TODO: add more screens
        default: return HOME;
    }
}
