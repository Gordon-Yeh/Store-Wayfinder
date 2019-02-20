#ifndef LABEL_H
#define LABEL_H

#include "../shapes/box.h"

#define LEFT 0
#define CENTER 1
#define RIGHT 2

#define TOP 0
#define MIDDLE 1
#define BOTTOM 2

typedef struct {
    char *text;
    int font;
    int colour;
    Box * box;

	// Positive h_align means shifting the text right
    int h_align;
	// Positive v_align means shifting the text down
    int v_align;
} TextBox;

TextBox * textbox_create(int x, int y, int l, int w);

void textbox_destroy(TextBox *tb);

void textbox_set_box_colour(TextBox *tb, int b_c, int f_c);

void textbox_set_text(TextBox *tb, char *text, int font, int colour);

void textbox_set_text_align(TextBox *tb, int h_align, int v_align);

int textbox_get_length(TextBox *tb);
int textbox_get_width(TextBox *tb);
int textbox_get_x(TextBox *tb);
int textbox_get_y(TextBox *tb);

int textbox_within(TextBox *tb, Point p);

// draw out the text on screen
void textbox_draw(TextBox *);

#endif
