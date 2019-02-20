#include <pthread.h>
#include "tracker.h"

static gps_point current_loc;
static int status;
static int UPDATE_RATE;

static void *tracking_loop(void *);

/**
 * function used for testing
 */
static void *get_switch_status(void *);

void tracker_start(int update_rate) {
    pthread_t tracker_thread;

    UPDATE_RATE = update_rate;
}

/**
 * the loop function to be executed by the tracker thread 
 */
void *tracking_loop(void *arg) {
    while (1) {

        // obey the update rate by putting thread to sleep, so other threads can run
        sleep(UPDATE_RATE);
    }
}
