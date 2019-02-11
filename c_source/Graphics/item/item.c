#include <stdlib.h>
#include <string.h>
//#include <stddef.h>
#include "../item/item.h"
#include "../shapes/box.h"

Item * create_item(char name[], char category[], int x, int y) {
    Item * i = malloc(sizeof(Item));
	i->name = malloc(strlen(name)+1);
	strcpy(i->name, name);
	//i->name = strdup(name); //strdup allocates memory and copies in name
	i->category = malloc(strlen(category)+1);
	strcpy(i->category, category);
	//i->category = strdup(category);
    i->x = x;
    i->y = y;
    return i;
}

void destroy_item(Item * i) {
	free(i->name);
    free(i->category);
	destroy_box(i->delete_box);
	free(i);
}