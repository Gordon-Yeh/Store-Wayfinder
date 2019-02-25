/**
 * The device location security feature
 * notifies a store employee via text message if the device has gone out the proximity of the store
 * runs concurrently with other component of the app
 */

#ifndef TRACKER_H
#define TRACKER_H

#define IN_BOUND 0
#define OUT_OF_BOUND 1

/**
 * start the tracker concurrently
 * LED0 will light up to indicate it's running
 * @param update_rate - rate at which the location updates (in ms)
 * @return 1 - if successfully starts, 0 - otherwise
 */
int tracker_start(float min_lon, float max_lon, float min_lat, float max_lat, unsigned int update_rate);

/**
 * @returns the location status of the device
 */
int tracker_get_status();

#endif // TRACKER_H
