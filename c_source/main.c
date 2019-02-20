//NOTE: (20, 0) is top left, (799, 479) is bottom right
#include <stdio.h>

#include "Graphics/gui.h"
#include "Graphics/item/item.h"

//GLOBAL VARIABLES
int item_list_size = 0;
Item * item_list[20];
char *cur_category;

int main(void)
{
	gui_start();
    return 0;
}
