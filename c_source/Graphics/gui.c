#include "Touchscreen.h"
#include "screens/screen.h"

#include "gui.h"

int gui_run() {
    screen_t curr_screen = HOME;

    while (1) {
        screen_draw(curr_screen);
        printf("listening!\n");
        curr_screen = screen_listen(curr_screen);
        printf("switching screen!\n");
    } 
}

int gui_start() {
    printf("Starting...\n");
	Init_Touch();
    screen_init();

    gui_run();
}
