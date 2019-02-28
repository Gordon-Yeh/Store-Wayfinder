#include <stdlib.h>
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
static int approx_equal(Point * p1, Point * p2);
static int is_in_map(Point * p);

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
    p.x = _xoffset + 50;
    p.y = _yoffset + 50;
    prev_p = &p;
    while (_running) {
        curr_p = query_map_position();
        // printf("current locations: (%d, %d)\n", curr_p->x, curr_p->y);
        if (curr_p != NULL && !approx_equal(curr_p, prev_p) && is_in_map(curr_p)) {
            refill_location(prev_p);
            sleep(1);
            plot_location(curr_p);
            prev_p = curr_p;
        }
        sleep(_update_rate);
    }
    refill_location(prev_p);
    pthread_exit(NULL);
}

static void plot_location(Point * p) {
    Person(_xoffset, _yoffset, p->x, p->y, _colour);
}

static void refill_location(Point * p) {
    DrawMapSection(_xoffset, _yoffset, p->x, p->y);
}

static int is_in_map(Point * p) {
    return (p->x > PERSON_HALF_WIDTH) 
        && (p->y > PERSON_HALF_HEIGHT) 
        && (p->x < MAP_WIDTH - PERSON_HALF_WIDTH) 
        && (p->y < MAP_HEIGHT - PERSON_HALF_HEIGHT);
}

// @returns 1 if p1 and p2 are approximately equal
static int approx_equal(Point * p1, Point * p2) {
    return abs(p1->x - p2->x) < 5 && abs(p1->y - p2->y) < 5;
}

void location_plotter_end() {
    *LEDs = *LEDs & ~(0x4); // turn LED3 off
    _running = 0;
    pthread_join(_lp_thread, NULL);
}