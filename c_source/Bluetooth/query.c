#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../Graphics/Touchscreen.h"
#include "bluetooth.h"

#define LOC_REQUEST_MESSAGE "p,"
#define DELIMITER ","

Point * parse_postion_string(char * str) {
    char *x_str, *y_str;

    Point * p = malloc(sizeof(Point));

    x_str = strtok(str, DELIMITER);
    y_str = strtok(NULL, DELIMITER);
    strtok(NULL, DELIMITER);

    p->x = atoi(x_str);
    p->y = atoi(y_str);
    return p;
}

Point * query_map_position() {
    char *position_str;
    Point * p;

    bt_send_message(LOC_REQUEST_MESSAGE);
    bt_receive_message(&position_str);
    printf("query_map_position: receive: %s\n", position_str);
    p = parse_postion_string(position_str);
    free(position_str);

    return p;
}

