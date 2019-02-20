#include <stdio.h>
#include "Touchscreen.h"
#include "screens/screen.h"

#include "gui.h"

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
    screen_init();

    gui_run();
	return 0;
}
