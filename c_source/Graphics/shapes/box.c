#include <stdlib.h>
#include <string.h>
#include "box.h"
#include "../draw/draw.h"
#include "../Touchscreen.h"

Box * create_box(char name[], int x, int y, int l, int w, int b_c, int f_c) {
    Box * b = malloc(sizeof(Box));
	b->name = strdup(name); //strdup allocates memory and copies in name
    b->x = x;
    b->y = y;
    b->l = l;
    b->w = w;
    b->b_c = b_c;
    b->f_c = f_c;

    return b;
}

void destroy_box(Box * b) {
	free(b->name);
    free(b);
}

void draw_box(Box * b) {
    draw_square(b->x, b->x + b->l - 1, b->y, b->y + b->w - 1, b->b_c);
    fill_square(b->x, b->x + b->l - 1, b->y, b->y + b->w - 1, b->f_c);
}

int within_box(Box * b, Point p) {
    return p.x > b->x 
        && p.y > b->y 
        && p.x < b->x + b->l
        && p.y < b->y + b->w;
}
