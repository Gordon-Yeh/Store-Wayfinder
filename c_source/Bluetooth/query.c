#include <stdlib.h>
#include <string.h>
#include "../Graphics/Touchscreen.h"
#include "bluetooth.h"

#define LOC_REQUEST_MESSAGE "p,"
#define DELIMITER ","

Point * query_map_position() {
    char *position_str, *x_str, *y_str;

    Point * p = malloc(sizeof(Point));
    bt_send_message(LOC_REQUEST_MESSAGE);
    bt_receive_message(&position_str);

    x_str = strtok(position_str, DELIMITER);
    y_str = strtok(NULL, DELIMITER);

    p->x = atoi(x_str);
    p->y = atoi(y_str);

    free(position_str);

    return p;
}

