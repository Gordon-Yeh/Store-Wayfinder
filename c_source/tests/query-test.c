#include <stdio.h>

#include "../io/bridge.h"
#include "../Bluetooth/bluetooth.h"
#include "../Bluetooth/query.h"
#include "../Graphics/Touchscreen.h"

void test_query_map_position() {
    Point * p = query_map_position();
    printf("current locations: [ %d , %d ]\n", p->x, p->y);
    free(p);
}

void sys_init() {
    bridge_init();  
    Init_BT();
}

int main(int argc, char **argv) {
    sys_init();
    test_query_map_position();
}