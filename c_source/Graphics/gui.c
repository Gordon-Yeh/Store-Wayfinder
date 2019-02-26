#include <stdio.h>
#include "Colours.h"
#include "Globalvars.h"
#include "Touchscreen.h"
#include "item/item.h"
#include "screens/screen.h"
#include "shapes/box.h"

#include "gui.h"

/*******************************/
//GLOBAL VARIABLES
char *cur_category;

int item_list_size = 0;
Item * item_list[100];
int pagenum = 0;
const int pagesize = 7;

Box *prev_page;
Box *next_page;
/*******************************/

int gui_run() {
    screen_t curr_screen = HOME;

    while (1) {
        screen_draw(curr_screen);
        curr_screen = screen_listen(curr_screen);
    } 
}

int gui_start() {
    printf("GUI starting...\n");
	Init_Touch();
	
	// Initialize global box variables
	prev_page = create_box(564, 426, 50, 50, FOREST_GREEN, FOREST_GREEN);
	next_page = create_box(725, 426, 50, 50, FOREST_GREEN, FOREST_GREEN);
	
    screen_init();

    gui_run();
	return 0;
}
