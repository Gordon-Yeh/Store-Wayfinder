#include <pthread.h>
#include <unistd.h>
#include "../io/bridge.h"
#include "tracker.h"

static volatile gps_point current_loc;
static volatile int status;
static int UPDATE_RATE;

static void *tracking_loop(void *);
/**
 * function used for testing
 */
static int get_switch_status();

int tracker_start(int update_rate) {
    // FIXME: do I need to keep a ref to this?
    pthread_t tracker_thread;
    int tracker_thread_code;

    UPDATE_RATE = update_rate;
    status = IN_BOUND;

    tracker_thread_code = pthread_create(&tracker_thread, NULL, tracking_loop, NULL);
	if (tracker_thread_code) {
        // thread failed to start
		return 0;
    }

    return 1;
}

int tracker_get_status() {
    return status;
}

/**
 * the loop function to be executed by the tracker thread 
 */
void *tracking_loop(void *arg) {
    *LEDs = *LEDs | 0x1; // light up LEDR0 to indecate the security feature is on
    while (1) {
        status = get_switch_status();
        // obey the update rate by putting thread to sleep, so other threads can run
        sleep(UPDATE_RATE);
    }
}

static int get_switch_status() {
    return (int) (*Switches & 0x1);
}
