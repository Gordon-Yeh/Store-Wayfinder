#include <stdlib.h>
#include <string.h>
#include <
#include "../shapes/box.h"

Item * create_item(char name[], char category[], int x, int y) {
    Item * i = malloc(sizeof(Item));
	i->name = strdup(name); //strdup allocates memory and copies in name
	i->category = strdup(category);
    i->x = x;
    i->y = y;
    return i;
}

void destory_item(Item * i) {
	free(i->name);
    free(i->category);
	destory_box(i->delete_box);
	free(i);
}