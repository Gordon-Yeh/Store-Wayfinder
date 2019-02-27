#include "Graphics/gui.h"
#include "Bluetooth/Bluetooth.h"

int main(void)
{
	Init_BT();
	gui_start();
    return 0;
}
