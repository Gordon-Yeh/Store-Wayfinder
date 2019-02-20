//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>

#include "io/bridge.h"
#include "app.h"

/**
 * do required initalization before running the app
 */
int sys_init()
{
    bridge_init();
}

int main(void)
{
    sys_init();
    app_start();
    return 0;
}
