#include <stdlib.h>
#include <string.h>
#include "textbox.h"
#include "../Text.h"
#include "../shapes/box.h"

TextBox * textbox_create(int x, int y, int l, int w) {
    TextBox * tb = malloc(sizeof(TextBox));
    tb->box = create_box(x, y, l, w, 0, 0);
	// Default: center the text in the box
	tb->h_align = 0;
	tb->v_align = 0;
    return tb;
}

void textbox_destroy(TextBox *tb) {
	free(tb->text);
	destroy_box(tb->box);
	free(tb);
}

void textbox_set_box_colour(TextBox *tb, int b_c, int f_c) {
    tb->box->f_c = f_c;
    tb->box->b_c = b_c;
}

void textbox_set_text(TextBox *tb, char *text, int font, int colour) {
	tb->text = malloc(strlen(text)+1); //same as strdup
	strcpy(tb->text, text);
    //tb->text = text;
    tb->font = font;
    tb->colour = colour;
}

void textbox_set_text_align(TextBox *tb, int h_align, int v_align) {
    tb->h_align = h_align;
    tb->v_align = v_align;
}

void textbox_draw(TextBox * tb) {
    draw_box(tb->box);
	CenteredSentence(tb->font, 
        textbox_get_x(tb),
        textbox_get_x(tb) + textbox_get_length(tb) - 1 + tb->h_align,
        textbox_get_y(tb),
        textbox_get_y(tb) + textbox_get_width(tb) - 1 + tb->v_align,
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
