#include "../io/bridge.h" 
#include "../GPS/GPS.h" 
#include "../Graphics/Touchscreen.h" 
#include "../Wifi/Wifi.h"
#include "../Bluetooth/bluetooth.h"

#include "tests.h"

void sys_init() {
    bridge_init();  
    Init_BT();
    Init_Wifi();
    Init_Touch();
    Init_GPS();
}

int main() {
    sys_init();

    /* put test to run here ..............*/
    // test_parse_postion_string();
    test_tracker();
}