#ifndef PLOT_H   /* Include guard */
#define PLOT_H

void draw_pixel(int x, int y, int Colour);

int read_pixel(int x, int y);

void ProgramPalette(int PaletteNumber, int RGB);

void draw_h_line(int x1, int y1, int x2, int Colour);

void draw_v_line(int x1, int y1, int y2, int Colour);

void draw_line(int x1, int y1, int x2, int y2, int Colour);

void draw_square(int x1, int x2, int y1, int y2, int Colour);

void fill_square(int x1, int x2, int y1, int y2, int Colour);

void clear(int Colour);

#endif // PLOT_H
