//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>

#include "Graphics/Colours.h"
#include "Graphics/Screens.h"
#include "Graphics/Touchscreen.h"

#include "Graphics/Text.h"

int main(void)
{
    printf("Starting...\n");
	Init_Touch();
	
	//FillBox(30, 789, 360, 469, WHITE);
	HomeMenu();
	//Font3(20, 0, RED, (int)'A');
	
    printf("Done...\n");
    return 0 ;
}



