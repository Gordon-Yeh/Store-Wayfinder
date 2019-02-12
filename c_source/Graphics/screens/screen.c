#include "screen.h"
#include "homescreen.h"

void screen_init() {
    homescreen_init();
    // TODO: call other screen init functions here
}

void screen_switch(screen_t next_screen) {
    switch (next_screen) {
        case HOME: homescreen_draw(); break;
        // TODO: add more screens
        default:
    }
}

screen_t screen_listen(screen_t curr_screen) {
    switch (curr_screen) {
        case HOME: return homescreen_listen();
        // TODO: add more screens
        default:
    }
}
