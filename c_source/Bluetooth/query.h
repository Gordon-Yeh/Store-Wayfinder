#ifndef QUERY_H
#define QUERY_H

#include "../Graphics/Touchscreen.h"

/**
 * @param string in the format "XXXXX,YYYY"
 * @returns point object with coordinates (XXXXX,YYYY)
 */
Point * parse_postion_string(char * str);

/**
 * @returns the current location of the device on the map
 */
Point * query_map_position();

#endif