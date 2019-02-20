#include <stdlib.h>
#include "textbox.h"
#include "../Text.h"

TextBox * textbox_create(int x, int y, int l, int w) {
    TextBox * tb = malloc(sizeof(TextBox));
    tb->box = create_box(x, y, l, w, 0, 0);;
    return tb;
}

void textbox_set_box_colour(TextBox *tb, int b_c, int f_c) {
    tb->box->f_c = f_c;
    tb->box->b_c = b_c;
}

void textbox_set_text(TextBox *tb, char *text, int font, int colour) {
    tb->text = text;
    tb->font = font;
    tb->colour = colour;
}

void textbox_draw(TextBox * tb) {
    draw_box(tb->box);
	CenteredSentence(tb->font, 
        textbox_get_x(tb),
        textbox_get_x(tb) + textbox_get_length(tb),
        textbox_get_y(tb),
        textbox_get_y(tb) + textbox_get_width(tb),
        tb->colour, 0, tb->text, DONT_ERASE);
}

int textbox_within(TextBox *tb, Point p) {
    return within_box(tb->box, p);
}

int textbox_get_length(TextBox *tb) {
    return tb->box->l;
}

int textbox_get_width(TextBox *tb) {
    return tb->box->w;
}

int textbox_get_x(TextBox *tb) {
    return tb->box->x;
}

int textbox_get_y(TextBox *tb) {
    return tb->box->y;
}
