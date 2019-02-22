#ifndef LOCATION_PLOTTER_H
#define LOCATION_PLOTTER_H

/**
 * start location plotter concurrently
 * @effect creates a new thread
 * @param update_rate - rate at where location is updated (in seconds)
 */
void location_plotter_start(int update_rate);

/**
 * ends location plotter
 * @effect kills the the thread created at the start
 */
void location_plotter_end();

#endif