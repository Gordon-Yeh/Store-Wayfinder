#include "../Colours.h"
#include "../shapes/box.h"
#include "../draw/draw.h"

//Only draws a button, doesn't do anything with it
Box * BackButton(void) {
	Box * back_box = create_box("back_box", 26, 2, 50, 50, BLUE, FOREST_GREEN);
	draw_box(back_box);

	draw_h_line(36, 26, 67, WHITE);
	draw_line(36, 26, 51, 8, WHITE);
	draw_line(36, 26, 51, 42, WHITE);
	
	return back_box; //box memory is allocated in heap, so safe to return
}