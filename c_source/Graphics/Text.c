/*************************************************************************************************
** This function draws a single ASCII character at the coord and colour specified
** it optionally ERASES the background colour pixels to the background colour
** This means you can use this to erase characters
**
** e.g. writing a space character with Erase set to true will set all pixels in the
** character to the background colour
**
*************************************************************************************************/
#include <string.h>

#include "draw/draw.h"
#include "Defines.h"
#include "Text.h"

// Constants ideally put this in a header file and #include it
#define FONT2_XPIXELS	10				// width of Font2 characters in pixels (no spacing)
#define FONT2_YPIXELS	14				// height of Font2 characters in pixels (no spacing)
#define FONT3_XPIXELS	16
#define FONT3_YPIXELS	27
#define FONT4_XPIXELS	22
#define FONT4_YPIXELS	40
#define FONT5_XPIXELS	38
#define FONT5_YPIXELS	59


// declaration of the external Array, ideally put this in a header file and #include it

extern const unsigned char Font5x7[][7] ; //5 pixels wide, 7 pixels high
extern const unsigned short int Font10x14[][14] ; //10 pixels wide, 14 pixels high
extern const unsigned char Font16x27[];
extern const unsigned char Font22x40[];
extern const unsigned char Font38x59[];

void Font1(int x, int y, int fontcolour, int backgroundcolour, int c, int Erase)
{
// using register variables (as opposed to stack based ones) may make execution faster
// depends on compiler and CPU

	register int row, column, theX = x, theY = y ;
	register int pixels ;
	register char theColour = fontcolour  ;
	register int BitMask, theC = c ;

// if x,y coord off edge of screen don't bother

    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))
        return ;


// if printable character subtract hex 20
	if(((short)(theC) >= (short)(' ')) && ((short)(theC) <= (short)('~'))) {
		theC = theC - 0x20 ;
		for(row = 0; (char)(row) < (char)(7); row ++)	{

// get the bit pattern for row 0 of the character from the software font
			pixels = Font5x7[theC][row] ;
			BitMask = 16 ;

			for(column = 0; (char)(column) < (char)(5); column ++)	{

// if a pixel in the character display it
				if((pixels & BitMask))
					draw_pixel(theX+column, theY+row, theColour) ;

				else {
					if(Erase == TRUE)

// if pixel is part of background (not part of character)
// erase the background to value of variable BackGroundColour

						draw_pixel(theX+column, theY+row, backgroundcolour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

/******************************************************************************************************************************
** This function draws a single ASCII character at the coord specified using the colour specified
** Font2(100,100, RED, 'A', TRUE, FALSE, 1, 1) ;	// display upper case 'A' in RED at coords 100,100, erase background
** no scroll, scale x,y= 1,1
**
******************************************************************************************************************************/
void Font2(int x, int y, int colour, int backgroundcolour, int c, int Erase)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					theRow, theColumn;


    if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		theRow = FONT2_YPIXELS;
		theColumn = FONT2_XPIXELS;

		for(row = 0; row < theRow ; row ++)	{
			pixels = Font10x14[theCharacter][row] ;		     								// get the pixels for row 0 of the character to be displayed
			BitMask = 512 ;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn;   )  	{
				if((pixels & BitMask))														// if valid pixel, then write it
					draw_pixel(theX+column, theY+row, theColour) ;
				else {																		// if not a valid pixel, do we erase or leave it along (no erase)
					if(Erase == TRUE)
						draw_pixel(theX+column, theY+row, backgroundcolour) ;
					// else leave it alone
				}
					column ++ ;
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void Font3(int x, int y, int colour, int c)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					offset, theColumn;


	if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
	        return ;

	if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
		theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
		offset = FONT3_YPIXELS*2;
		theColumn = FONT3_XPIXELS;

		for(row = 0; row < offset ; row ++)	{
			pixels = Font16x27[(theCharacter*54) + row] ;		     								// get the pixels for row 0 of the character to be displayed
			BitMask = 128;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn; column++)  	{
				if((pixels & BitMask)){
					// if valid pixel, then write it
					if(row % 2 == 0)
						draw_pixel(theX+column, theY+(row/2), theColour) ;
					else
						draw_pixel(theX+column+8, theY+(row/2), theColour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void Font4(int x, int y, int colour, int c)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					offset, theColumn;


	if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
	        return ;

		if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
			theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
			offset = FONT4_YPIXELS*3;
			theColumn = FONT4_XPIXELS;

		for(row = 0; row < offset ; row ++)	{
			pixels = Font22x40[(theCharacter*120) + row] ;	 	     								// get the pixels for row 0 of the character to be displayed
			BitMask = 128;							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn; column++)  	{
				if((pixels & BitMask)){
					// if valid pixel, then write it
					if(row % 3 == 0)
						draw_pixel(theX+column, theY+(row/3), theColour) ;
					else if(row % 3 == 1)
						draw_pixel(theX+column+8, theY+(row/3), theColour) ;
					else
						draw_pixel(theX+column+16, theY+(row/3), theColour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}

void Font5(int x, int y, int colour, int c)
{
	register int 	row,
					column,
					theX = x,
					theY = y ;
	register int 	pixels ;
	register char 	theColour = colour  ;
	register int 	BitMask,
					theCharacter = c,
					offset, theColumn;


	if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
	        return ;

		if(((short)(theCharacter) >= (short)(' ')) && ((short)(theCharacter) <= (short)('~'))) {			// if printable character
			theCharacter -= 0x20 ;																			// subtract hex 20 to get index of first printable character (the space character)
			offset = FONT5_YPIXELS*4;
			theColumn = FONT5_XPIXELS;

		for(row = 0; row < offset ; row ++)	{
			pixels = Font38x59[(theCharacter*236) + row] ;	 	     								// get the pixels for row 0 of the character to be displayed
			BitMask = 128; 							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
			for(column = 0; column < theColumn; column++)  	{
				if((pixels & BitMask)){
					// if valid pixel, then write it
					if(row % 4 == 0)
						draw_pixel(theX+column, theY+(row/4), theColour) ;
					else if(row % 4 == 1)
						draw_pixel(theX+column+8, theY+(row/4), theColour) ;
					else if(row % 4 == 2)
						draw_pixel(theX+column+16, theY+(row/4), theColour) ;
					else
						draw_pixel(theX+column+24, theY+(row/4), theColour) ;
				}
				BitMask = BitMask >> 1 ;
			}
		}
	}
}
/*********************************************************************************************
*********************************************************************************************/

void Sentence(int font, int x, int y, int fontcolour, int backgroundcolour, char sentence[], int Erase)
{
	int i;
	if(font == 1) { //font1
		for(i = 0; i < strlen(sentence); i++) {
			Font1(x+6*i, y, fontcolour, backgroundcolour, (int) sentence[i], Erase);
		}
	}
	else if (font == 2){ //font2
		for(i = 0; i < strlen(sentence); i++) {
			Font2(x+11*i, y, fontcolour, backgroundcolour, (int) sentence[i], Erase);
		}
	}
	else if (font == 3){ //font3
		for(i = 0; i < strlen(sentence); i++) {
			Font3(x+17*i, y, fontcolour,  (int) sentence[i]);
		}
	}
	else if (font == 4){ //font4
		for(i = 0; i < strlen(sentence); i++) {
			Font4(x+23*i, y, fontcolour, (int) sentence[i]);
		}
	}
	else{ //font5
		for(i = 0; i < strlen(sentence); i++) {
			Font5(x+39*i, y, fontcolour, (int) sentence[i]);
		}
	}
}

void CenteredSentence(int font, int leftx, int rightx, int topy, int boty, int fontcolour, int backgroundcolour, char sentence[], int Erase)
{
	int midx = (leftx+rightx+1)/2;
	int midy = (topy+boty+1)/2;
	int startingx;
	int startingy;
	int i;

	if(font == 1) { //font1 5x7
		startingx = midx-(6*strlen(sentence)-1)/2;
				 startingy = midy-3;
		for(i = 0; i < strlen(sentence); i++) {
			Font1(startingx+6*i, startingy, fontcolour, backgroundcolour, (int) sentence[i], Erase);
		}
	}
	else if (font == 2){ //font2 10x14
		startingx = midx-(11*strlen(sentence)-1)/2;
		startingy = midy-7;
		for(i = 0; i < strlen(sentence); i++) {
			Font2(startingx+11*i, startingy, fontcolour, backgroundcolour, (int) sentence[i], Erase);
		}
	}
	else if (font == 3){ //font3 16x27
		startingx = midx-(17*strlen(sentence)-1)/2;
			startingy = midy-13;
			for(i = 0; i < strlen(sentence); i++) {
				Font3(startingx+17*i, startingy, fontcolour, (int) sentence[i]);
		}
	}
	else if (font == 4){ //font4 22x40
		startingx = midx-(23*strlen(sentence)-1)/2;
			startingy = midy-20;
			for(i = 0; i < strlen(sentence); i++) {
				Font4(startingx+23*i, startingy, fontcolour, (int) sentence[i]);
		}
	}
	else if (font == 5){ //font5 38x59
		startingx = midx-(39*strlen(sentence)-1)/2;
			startingy = midy-29;
			for(i = 0; i < strlen(sentence); i++) {
				Font5(startingx+39*i, startingy, fontcolour, (int) sentence[i]);
		}

	}
}

void Paragraph(int x, int y, int fontcolour, int backgroundcolour, char * sentences[], int sentences_size, int Erase) {
	int row_gap = 3;
	for(int row = 0; row < sentences_size; row++) {
		Sentence(FONT2, x, y+row*(FONT2_YPIXELS+row_gap), fontcolour, backgroundcolour, sentences[row], Erase);
	}
}