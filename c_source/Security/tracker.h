/**
 * The device location security feature
 * notifies a store employee via text message if the device has gone out the proximity of the store
 * runs concurrently with other component of the app
 */

#ifndef TRACKER_H
#define TRACKER_H

#include "../GPS/GPS.h"

#define IN_BOUND 1
#define OUT_OF_BOUND 0

typedef struct {
    float min_lon;
    float max_lon;
    float min_lat;
    float max_lat;
} Bound;

/* modes */
#define TESTING 1
#define PRODUCTION 0

/**
 * start the tracker concurrently
 * LED0 will light up to indicate it's running
 * @params 
 *  tracking_bound - determines if the device is out of bound
 *  update_rate - rate at which tracker will update the device's location
 *  mode - set how the tracker runs
 *      PRODUCTION: runs off the GPS, OUT_OF_BOUND status occurs when the gps coordinate is out of tracking_bound
 *      TESTING: runs off SW0, if SW0 is 1 then OUT_OF_BOUND status occurs 
 * @return 1 - if successfully starts, 0 - otherwise
 */
int tracker_start(Bound tracking_bound, unsigned int update_rate, int mode);

/**
 * @returns the location status of the device
 */
int tracker_get_status();

int inbound(gps_point * p, Bound * b);

#endif // TRACKER_H
