#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "item.h"
#include "../Globalvars.h"
#include "../../Bluetooth/bluetooth.h"

// Returns an array of Item pointers
Item ** parse_BT_items(void) {
	char *buffer;
	bt_receive_message(&buffer);
	printf("received message: %s\n", buffer);
	
	static Item *items[10];
	int index = 0;
	
	char *token;
	char *name;
	int x, y;
	/* get the first token */
	token = strtok(buffer, ",");

	/* walk through other tokens */
	while( token != NULL ) {
		printf( "%s\n", token);
		// Right now, token is name
		name = malloc(strlen(token)+1);
		strcpy(name, token);
		token = strtok(NULL, ",");
		// Token is x
		x = atoi(token);
		printf("%d\n", x);
		token = strtok(NULL, ",");
		// Token is y
		y = atoi(token);
		printf("%d\n", y);
		
		items[index] = create_display_item(name, cur_category, x, y);
		index++;
		
		free(name);

		// Next word
		token = strtok(NULL, ",");
	}
	
	
	
	
	
	
	
	
	
	
	
	
	// char c;
	
	// static Item *items[10];
	// int index = 0;
	// char name[30];
	// int x = 0, y = 0;
	
	// int step = 1;

	// for(int i = 0; buffer[i] != '\0'; i++) {
		// c = buffer[i];
		// switch (c) {
			// case ',': {
				// // Create the item
				// items[index] = create_display_item(name, cur_category, x, y);
				// index++;
				// step = 1;
			// } break;
			// case '<': {
				// step = 2;
			// } break;
			// case '>': {
				// step = 3;
			// } break;
			// case '?': {
				// return items;
			// } break;
			// default: {
				// switch (step) {
					// case 1: {
						// // Step 1 is writing the name
						// sprintf(name, "%s%c", name, c);
					// } break;
					// case 2: {
						// // Step 2 is finding the x coordinate
						// x = x*10 + (int)c;
					// } break;
					// case 3: {
						// // Step 3 is finding the y coordinate
						// y = y*10 + (int)c;
					// } break;
					// default: {
					// } break;
				// }
			// } break;
		// }
		// i=0 ; // reset timer if we got something back
	// }
	// // Should never reach here
	return items;
}