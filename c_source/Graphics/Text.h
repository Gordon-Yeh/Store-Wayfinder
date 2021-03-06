#ifndef TEXT_H_   /* Include guard */
#define TEXT_H_

#define FONT1 1
#define FONT2 2
#define FONT3 3
#define FONT4 4
#define FONT5 5
#define DONT_ERASE 0
#define ERASE 1

void Font1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase);
void Font2(int x, int y, int colour, int backgroundcolour, int c, int Erase);
void Font3(int x, int y, int colour, int c);
void Font4(int x, int y, int colour, int c);
void Font5(int x, int y, int colour, int c);
void Sentence(int font, int x, int y, int fontcolour, int backgroundcolour, char sentence[], int Erase);
void CenteredSentence(int font, int leftx, int rightx, int topy, int boty, int fontcolour, int backgroundcolour, char sentence[], int Erase);
void Paragraph(int x, int y, int fontcolour, int backgroundcolour, char * sentences[], int sentences_size, int Erase);

#endif // TEXT_H_
