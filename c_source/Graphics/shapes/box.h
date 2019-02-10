#ifndef SQUARE_H
#define SQUARE_H

#include "../Touchscreen.h"

typedef struct {
	char *name;
    int x;
    int y;
    int l;
    int w;
    int b_c; // border colour
    int f_c; // fill colour
} Box;

// constructor for box struct
Box * create_box(char name[], int x, int y, int l, int w, int b_c, int f_c);

// destructor for box struct
void destroy_box(Box *);

// function for plotting the box on screen
void draw_box(Box *);

// return true if the coordinate is within the box
int within_box(Box * b, Point p);

#endif
