#include <pthread.h>
#include <unistd.h>

#include "../io/bridge.h"
#include "../GPS/GPS.h"
#include "tracker.h"

static volatile gps_point * _curr_point;
static volatile int _status;
static volatile unsigned int _update_rate;
static volatile Bound _bound;

static void *gps_tracking_loop(void *);
static void *switch_tracking_loop(void *);

/**
 * function used for testing
 */
static int get_switch_status();

int tracker_start(Bound tracking_bound, unsigned int update_rate, int mode) {
    // FIXME: do I need to keep a ref to this?
    pthread_t tracker_thread;
    int tracker_thread_code;
    void * start_routine;

    _update_rate = update_rate;
    _status = IN_BOUND;
    _bound = tracking_bound;

    if (mode == PRODUCTION)
        start_routine = gps_tracking_loop;
    else
        start_routine = switch_tracking_loop;

    tracker_thread_code = pthread_create(
        &tracker_thread, // pthread
        NULL, // thread attributes
        start_routine, // new thread entry point
        NULL // args
    );

    // thread failed to start
	if (tracker_thread_code) {
		return 0;
    }

    return 1;
}

int tracker_get_status() {
    return _status;
}


int inbound(gps_point * p, Bound * b) {
    return p->lon > b->min_lon && p->lat > b->min_lat && p->lon < b->max_lon && p->lat < b->max_lat;
} 

/**
 * the loop function to be executed by the tracker thread 
 */
static void *gps_tracking_loop(void *arg) {
    *LEDs = *LEDs | 0x1; // light up LEDR0 to indecate the security feature is on
    while (1) {
        _curr_point = getPoint();
        if (inbound(_curr_point, &_bound))
            _status = IN_BOUND;
        else
            _status = OUT_OF_BOUND;
        // obey the update rate by putting thread to sleep, so other threads can run
        sleep(_update_rate);
        free(_curr_point);
    }
}

static void *switch_tracking_loop(void *arg) {
    *LEDs = *LEDs | 0x1; // light up LEDR1 to indecate the security feature is on
    while (1) {
        _status = get_switch_status();
        // obey the update rate by putting thread to sleep, so other threads can run
        sleep(_update_rate);
    }
}


static int get_switch_status() {
    return (int) (*Switches & 0x1);
}
