#ifndef BASICS_H_   /* Include guard */
#define BASICS_H_

void WriteAPixel(int x, int y, int Colour);
int ReadAPixel(int x, int y);
void ProgramPalette(int PaletteNumber, int RGB);
void HLine(int x1, int y1, int x2, int Colour);
void VLine(int x1, int y1, int y2, int Colour);
void Box(int x1, int x2, int y1, int y2, int Colour);
void Line(int x1, int y1, int x2, int y2, int Colour);
void Clear(int Colour);

#endif // BASICS_H_