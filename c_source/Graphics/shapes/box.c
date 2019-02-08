#include <stdlib.h>
#include "box.h"
#include "../draw/draw.h"
#include "../Touchscreen.h"

Box * create_box(int x, int y, int l, int w, int b_c, int f_c) {
    Box * b = malloc(sizeof(Box));
    b->x = x;
    b->y = y;
    b->l = l;
    b->w = w;
    b->b_c = b_c;
    b->f_c = f_c;

    return b;
}

void destory_box(Box * b) {
    free(b);
}

void draw_box(Box * b) {
    draw_square(b->x, b->x + b->l, b->y, b->y + b->w, b->b_c);
    fill_square(b->x, b->x + b->l, b->y, b->y + b->w, b->f_c);
}

int within_box(Box * b, Point p) {
    return p.x > b->x 
        && p.y > b->y 
        && p.x < b->x + b->l
        && p.y < b->y + b->w;
}
