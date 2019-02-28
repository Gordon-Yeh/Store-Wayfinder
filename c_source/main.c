//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>

#include "io/bridge.h"
#include "app.h"
#include "GPS/GPS.h" 
#include "Graphics/Touchscreen.h" 
#include "Wifi/Wifi.h"
#include "Bluetooth/bluetooth.h"

/**
 * do required initalization before running the app
 */
int sys_init()
{
    bridge_init();
    Init_BT();
    // Init_Wifi(); TODO: fix, right now it throws an exception during run time, could be because the address mapping is wrong
    Init_Touch();
    Init_GPS();
}

int main(void)
{
    sys_init();
    app_start();
    return 0;
}
