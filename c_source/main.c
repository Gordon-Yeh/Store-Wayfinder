#include "Graphics/gui.h"
#include "Bluetooth/bluetooth.h"

int main(void)
{
	Init_BT();
	gui_start();
    return 0;
}
