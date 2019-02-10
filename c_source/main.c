//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>

#include "Graphics/Colours.h"
#include "Graphics/item/item.h"
#include "Graphics/screens/Screens.h"
#include "Graphics/Globalvars.h"
#include "Graphics/Touchscreen.h"
#include "Graphics/widgets/widgets.h"

#include "Graphics/Text.h"

int item_list_size = 0;
Item * item_list[30];

int main(void)
{
    printf("Starting...\n");
	Init_Touch();
	
	//HomeScreen();
	ResetScreen();
	SidebarList();
	
    printf("Done...\n");
    return 0 ;
}
