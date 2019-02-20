#include "Graphics/gui.h"
#include "io/bridge.h"

int sys_init()
{
    bridge_init();
}

int main(void)
{
	gui_start();
    return 0;
}
