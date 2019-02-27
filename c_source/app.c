#include <pthread.h>
#include <stdlib.h>

#include "Graphics/gui.h"
#include "Security/tracker.h"
#include "io/bridge.h"

void app_start() {
    Bound store_bound;
    store_bound.min_lon = 233.23;
    store_bound.min_lat = 454.0;
    store_bound.max_lon = 240.12;
    store_bound.max_lat = 455.0;

    // start tracking of the device with refresh rate of 1 second
    tracker_start(store_bound, 2, TESTING);
    gui_start();
}