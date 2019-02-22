#include <pthread.h>

static _update_rate;
static volatile int _running;
static pthread _lp_thread;
static void *update_location(void *);

int location_plotter_start(int update_rate) {
    int result;
    _running = 1;
    _update_rate = update_rate;
    result = pthread_create(&_lp_thread, NULL, update_location, NULL);
    if (result) {
        return 0;
    }
    return 1;
}

static void *update_location(void *) {
    while (_running) {
        // get new location
        // refill old location
        // plot new location
        sleep(_update_rate);
    }

    pthread_exit(NULL);
}

void location_plotter_end() {
    _running = 0;
    pthread_join(_lp_thread, NULL);
}