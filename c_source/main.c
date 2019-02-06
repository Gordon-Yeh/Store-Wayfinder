//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>

#include "Graphics/Screens.h"
#include "Graphics/Touchscreen.h"

int main(void)
{
    printf("Starting...\n");
	Init_Touch();
	
	HomeMenu();
	//SearchScreen();
	
    printf("Done...\n");
    return 0 ;
}



