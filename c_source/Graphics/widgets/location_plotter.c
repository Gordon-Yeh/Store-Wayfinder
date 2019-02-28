#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include "../../io/bridge.h"
#include "../../Bluetooth/query.h"
#include "../Touchscreen.h"
#include "../draw/DrawImages.h"
#include "../draw/DrawMap.h"

static _update_rate;
static volatile int _running;
static pthread_t _lp_thread;
static int _colour;
static int _xoffset, _yoffset;
static void *update_location(void * args);
static void plot_location(Point * p);
static void refill_location(Point * p);

#define PERSON_HALF_WIDTH 9
#define PERSON_HALF_HEIGHT 13
#define MAP_WIDTH 518
#define MAP_HEIGHT 418

int location_plotter_start(int update_rate, int x_offset, int y_offset, int colour) {
    int result;
    _running = 1;
    _update_rate = update_rate;
    _xoffset = x_offset;
    _yoffset = y_offset;
    _colour = colour;

    result = pthread_create(&_lp_thread, NULL, update_location, NULL);
    if (result) {
        return 0;
    }
    return 1;
}

static void *update_location(void * args) {
    *LEDs = *LEDs | 0x4; // turn on LED2 to indicate its running 
    Point p;
    Point *curr_p, *prev_p;
    // initalize the point so the first iteration won't complain
    p.x = 0;
    p.y = 0;
    prev_p = &p;
    while (_running) {
        curr_p = query_map_position();
        if (curr_p == NULL) continue;
        // printf("current locations: (%d, %d)\n", curr_p->x, curr_p->y);
        refill_location(prev_p);
        plot_location(curr_p);
        prev_p = curr_p;
        sleep(_update_rate);
    }
    refill_location(prev_p);
    pthread_exit(NULL);
}

static void plot_location(Point * p) {
    printf("printing person at (%d, %d)\n", _xoffset + p->x, _yoffset + p->y);
    if (p->x < PERSON_HALF_WIDTH || p->y < PERSON_HALF_HEIGHT) return;
    if (p->x > MAP_WIDTH - PERSON_HALF_WIDTH || p->y > MAP_HEIGHT - PERSON_HALF_HEIGHT) return;
    Person(_xoffset, _yoffset, p->x, p->y, _colour);
}

static void refill_location(Point * p) {
    printf("refilling person at (%d, %d)\n", _xoffset + p->x, _yoffset + p->y);
    if (p->x < PERSON_HALF_WIDTH || p->y < PERSON_HALF_HEIGHT) return;
    if (p->x > MAP_WIDTH - PERSON_HALF_WIDTH || p->y > MAP_HEIGHT - PERSON_HALF_HEIGHT) return;
    DrawMapSection(_xoffset, _yoffset, p->x, p->y);
}

void location_plotter_end() {
    *LEDs = *LEDs & ~(0x4);
    _running = 0;
    pthread_join(_lp_thread, NULL);
}