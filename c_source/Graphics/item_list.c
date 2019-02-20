#include "Globalvars.h"
#include "Colours.h"
#include "Text.h"
#include "components/textbox.h"
#include "shapes/box.h"

// For the item delete_box
static const int d_row_gap = 2; //y
static const int d_base_x = 544;
static const int d_base_y = 60;
static const int d_button_length = 246; //x
static const int d_button_width = 50; //y

// For the item delete_icon
static const int di_row_gap = 12; //y
static const int di_base_x = 745;
static const int di_base_y = 65;
static const int di_box_length = 40; //x
static const int di_box_width = 40; //y

void add_to_item_list(char *item_name) {
	//TODO: find the item from the database and create a new item to put in the item_list array
	
	//ie. if item_list_size == 3, 3 items in array already, so insert an item into the 3rd index, row = 3
	//ie. if item_list_size == 7, 7 items in array already, so insert an item into the 7th index, row = 0
	int row = item_list_size%pagesize;
	
	/********************************************/
	// Set up the delete_box
	TextBox *db = textbox_create(
		d_base_x,
		d_base_y + row * (d_button_width + d_row_gap),
		d_button_length,
		d_button_width);

	textbox_set_box_colour(db, BLUE, WHITE);
	textbox_set_text(db, item_name, FONT2, FOREST_GREEN);
		// h_align is -46 to make room for the delete_icon
	textbox_set_text_align(db, -46, 0);
	/********************************************/
	
	/********************************************/
	// Set up the delete_icon
	TextBox *di = textbox_create(
		di_base_x,
		di_base_y + row * (di_box_width + di_row_gap),
		di_box_length,
		di_box_width);
	
	textbox_set_box_colour(di, BLACK, RED);
	textbox_set_text(di, "X", FONT2, BLACK);
	/********************************************/
		
	//Temporary data
	item_list[item_list_size] = create_item(item_name, "category a", 50, 50, db, di);
	
	item_list_size++; //increase the size by 1
}

// Precondition: item_list[index] is a valid item
void remove_from_item_list(int index) {
	destroy_item(item_list[index]);
	item_list_size--; //decrease the size by 1
	// If item_list_size != 0, we have do shift everything greater than index down by 1
	if(item_list_size != 0) {
		for(int k = index+1; k < item_list_size+1; k++) {
			// Delete the current boxes
			destroy_box(item_list[k]->delete_textbox->box);
			destroy_box(item_list[k]->delete_icon->box);
			
			// Set up new boxes with a lower row
			int row = (k-1)%pagesize;
			Box *b = create_box(
				d_base_x,
				d_base_y + row * (d_button_width + d_row_gap),
				d_button_length,
				d_button_width, BLUE, WHITE);
			Box *bi = create_box(
				di_base_x,
				di_base_y + row * (di_box_width + di_row_gap),
				di_box_length,
				di_box_width, BLACK, RED);
						
			// Replace the old boxes
			item_list[k]->delete_textbox->box = b;
			item_list[k]->delete_icon->box = bi;
			
			// Move the index down
			item_list[k-1] = item_list[k];
		}
		// Make the last item point to NULL
	}
}