#ifndef ITEM_H
#define ITEM_H

#include "../shapes/box.h"

typedef struct {
	char *name;
    char *category; //which category is the item in
	int x; //x, y location to plot the item
	int y;
	Box *delete_box;
} Item;

// constructor for item struct
Item * create_item(char name[], char category[], int x, int y);

// destructor for item struct
void destroy_item(Item * i);

#endif
