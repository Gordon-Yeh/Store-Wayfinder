#include "Graphics/gui.h"
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
