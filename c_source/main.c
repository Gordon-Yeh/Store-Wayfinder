//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>

#include "Graphics/Colours.h"
#include "Graphics/screens/Screens.h"
#include "Graphics/Touchscreen.h"

#include "Graphics/Text.h"

int main(void)
{
    printf("Starting...\n");
	Init_Touch();
	
	HomeScreen();
	
    printf("Done...\n");
    return 0 ;
}
