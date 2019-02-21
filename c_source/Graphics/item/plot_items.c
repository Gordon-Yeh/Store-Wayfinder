#include "../Colours.h"
#include "../Globalvars.h"
#include "../draw/DrawImages.h"
#include "item.h"

static const int map_base_x = 22;
static const int map_base_y = 60;

void plot_items(void) {
	for(int i = 0; i < item_list_size; i++) {
		Circle(item_list[i]->x + map_base_x, item_list[i]->y + map_base_y, RED);
	}
}

// Used to remove a plot from the map BEFORE an item is removed
void unplot_item(int index) {
	// Unplot really just fills the plot with GRAY, the same colour as the map
	Circle(item_list[index]->x + map_base_x, item_list[index]->y + map_base_y, GRAY);
}