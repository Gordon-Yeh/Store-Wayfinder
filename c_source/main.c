#include "Graphics/gui.h"
#include "io/bridge.h"

int sys_init()
{
    bridge_init();
}

int main(void)
{
	sys_init();
	gui_start();
    return 0;
}
