#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "item/item.h"

// Communication between categoryscreen and itemscreen
extern char *cur_category;

// For item_list use
extern int item_list_size;
	// Items 0 to 6 are on page 0. Items 7 to 13 are on page 1. etc
extern Item *item_list[30]; //array of item pointers
extern int pagenum; //page 0 is the first page
extern const int pagesize;

extern Box *next_page;
extern Box *prev_page;

void add_to_item_list(char *item_name);
void remove_from_item_list(int index);

#endif
