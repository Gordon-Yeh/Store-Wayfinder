#include <pthread.h>
#include <unistd.h>

#include "../io/bridge.h"
#include "../GPS/GPS.h"
#include "tracker.h"

static volatile gps_point _curr_location;
static volatile int _status;
static volatile unsigned int _update_rate;
static volatile float _min_lon, _max_lon, _min_lat, _max_lat;

static void *tracking_loop(void *);
/**
 * function used for testing
 */
static int get_switch_status();

int tracker_start(float min_lon, float max_lon, float min_lat, float max_lat, unsigned int update_rate) {
    Init_GPS();

    // FIXME: do I need to keep a ref to this?
    pthread_t tracker_thread;
    int tracker_thread_code;

    _update_rate = update_rate;
    _status = IN_BOUND;
    
    _min_lon = min_lon;
    _max_lon = max_lon;
    _min_lat = min_lat;
    _max_lat = max_lat;

    tracker_thread_code = pthread_create(&tracker_thread, NULL, tracking_loop, NULL);
	if (tracker_thread_code) {
        // thread failed to start
		return 0;
    }

    return 1;
}

int tracker_get_status() {
    return _status;
}

/**
 * the loop function to be executed by the tracker thread 
 */
static void *tracking_loop(void *arg) {
    *LEDs = *LEDs | 0x1; // light up LEDR0 to indecate the security feature is on
    while (1) {
        _status = get_switch_status();

        // _curr_location = getPoint();
        // if (_curr_location.lon < _min_lon || _curr_location.lat < _min_lat || _curr_location.lon > _max_lon || _curr_location.lat > _max_lat)
        //     _status = OUT_OF_BOUND;
        // else
        //     _status = IN_BOUND;
        
        // obey the update rate by putting thread to sleep, so other threads can run
        sleep(_update_rate);
    }
}

static int get_switch_status() {
    return (int) (*Switches & 0x1);
}
