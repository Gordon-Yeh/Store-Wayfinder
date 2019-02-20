#ifndef GLOBALVARS_H
#define GLOBALVARS_H

#include "item/item.h"

extern int item_list_size; //uninitialized
extern Item * item_list[20]; //array of item pointers
extern char *cur_category;

void add_to_item_list(char *item_name);
void remove_from_item_list(int index);

#endif
