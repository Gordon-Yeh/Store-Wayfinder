#ifndef LOCATION_PLOTTER_H
#define LOCATION_PLOTTER_H

/**
 * start location plotter concurrently
 * @effect creates a new thread
 *      LED3 will be on
 * @param
 *      update_rate - rate at where location is updated (in seconds)
 *      x_offset - starting x coordinate of the map on the screen (top left corner)
 *      y_offset - starting y coordinate of the map on the screen (top left corner)
 *      colour - colour of the marker to be drawn on map
 */
void location_plotter_start(int update_rate, int x_offset, int y_offset, int colour);

/**
 * ends location plotter
 * @effect kills the the thread created at the start
 */
void location_plotter_end();

#endif