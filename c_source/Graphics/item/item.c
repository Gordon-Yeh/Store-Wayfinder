#include <stdlib.h>
#include <string.h>
#include "../components/textbox.h"
#include "../item/item.h"

Item * create_display_item(char *name, char *category, int x, int y) {
	Item * i = malloc(sizeof(Item));
	i->name = malloc(strlen(name)+1); //same as strdup
	strcpy(i->name, name);
	i->category = malloc(strlen(category)+1); //same as strdup
	strcpy(i->category, category);
	i->x = x;
    i->y = y;
	
	// A display item does not have textboxes
	i->delete_textbox = textbox_create(0,0,0,0);
	textbox_set_text(i->delete_textbox, "", 0, 0);
	i->delete_icon = textbox_create(0,0,0,0);
	textbox_set_text(i->delete_icon, "", 0, 0);
    return i;
}

Item * create_item(char *name, char *category, int x, int y, TextBox *delete_textbox, TextBox *delete_icon) {
    Item * i = malloc(sizeof(Item));
	i->name = malloc(strlen(name)+1); //same as strdup
	strcpy(i->name, name);
	i->category = malloc(strlen(category)+1); //same as strdup
	strcpy(i->category, category);
    i->x = x;
    i->y = y;
	i->delete_textbox = delete_textbox;
	i->delete_icon = delete_icon;
    return i;
}

void destroy_item(Item * i) {
	free(i->name);
    free(i->category);
	textbox_destroy(i->delete_textbox);
	textbox_destroy(i->delete_icon);
	free(i);
}