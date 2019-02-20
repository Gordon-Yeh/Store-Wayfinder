#include <stdio.h>
#include "../Colours.h"
#include "draw.h"
#include "../../io/bridge.h"

//NOTE: (20, 0) is top left, (799, 479) is bottom right
// graphics register addresses

// #define *GraphicsCommandReg   		(*(volatile unsigned short int *)(0xFF210000))
// #define *GraphicsStatusReg   		(*(volatile unsigned short int *)(0xFF210000))
// #define *GraphicsX1Reg   			(*(volatile unsigned short int *)(0xFF210002))
// #define *GraphicsY1Reg   			(*(volatile unsigned short int *)(0xFF210004))
// #define *GraphicsX2Reg   			(*(volatile unsigned short int *)(0xFF210006))
// #define *GraphicsY2Reg   			(*(volatile unsigned short int *)(0xFF210008))
// #define *GraphicsColourReg   		(*(volatile unsigned short int *)(0xFF21000E))
// #define *GraphicsBackGroundColourReg   	(*(volatile unsigned short int *)(0xFF210010))

/************************************************************************************************
** This macro pauses until the graphics chip status register indicates that it is idle
***********************************************************************************************/
#define WAIT_FOR_GRAPHICS		while((*GraphicsStatusReg & 0x0001) != 0x0001);


// #defined constants representing values we write to the graphics 'command' register to get
// it to draw something. You will add more values as you add hardware to the graphics chip
// Note Drawdraw_h_line, Drawdraw_v_line and DrawLine at the moment do nothing - you will modify these

#define DRAW_H_LINE		1
#define DRAW_V_LINE		2
#define DRAW_LINE		3
#define CLEAR_SCREEN 	4
#define FILL      		5

#define	PutAPixel		0xA
#define	GetAPixel		0xB
#define	ProgramPaletteColour    0x10

/*******************************************************************************************
* This function writes a single pixel to the x,y coords specified using the specified colour
* Note colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
********************************************************************************************/
void draw_pixel(int x, int y, int Colour)
{
	WAIT_FOR_GRAPHICS;				// is graphics ready for new command

	*GraphicsX1Reg = x;				// write coords to x1, y1
	*GraphicsY1Reg = y;
	*GraphicsColourReg = Colour;			// set pixel colour
	*GraphicsCommandReg = PutAPixel;			// give graphics "write pixel" command
}

/*********************************************************************************************
* This function read a single pixel from the x,y coords specified and returns its colour
* Note returned colour is a byte and represents a palette number (0-255) not a 24 bit RGB value
*********************************************************************************************/

int read_pixel(int x, int y)
{
	WAIT_FOR_GRAPHICS;			// is graphics ready for new command

	*GraphicsX1Reg = x;			// write coords to x1, y1
	*GraphicsY1Reg = y;
	*GraphicsCommandReg = GetAPixel;		// give graphics a "get pixel" command

	WAIT_FOR_GRAPHICS;			// is graphics done reading pixel
	return (int) (*GraphicsColourReg);	// return the palette number (colour)
}


/**********************************************************************************
** subroutine to program a hardware (graphics chip) palette number with an RGB value
** e.g. ProgramPalette(RED, 0x00FF0000) ;
**
************************************************************************************/

void ProgramPalette(int PaletteNumber, int RGB)
{
    WAIT_FOR_GRAPHICS;
    *GraphicsColourReg = PaletteNumber;
    *GraphicsX1Reg = RGB >> 16;        // program red value in ls.8 bit of X1 reg
    *GraphicsY1Reg = RGB ;                // program green and blue into ls 16 bit of Y1 reg
    *GraphicsCommandReg = ProgramPaletteColour; // issue command
}

/********************************************************************************************* This function draw a horizontal line, 1 pixel at a time starting at the x,y coords specified
*********************************************************************************************/

void draw_h_line(int x1, int y1, int x2, int Colour)
{
	WAIT_FOR_GRAPHICS;

	*GraphicsX1Reg = x1;
	*GraphicsY1Reg = y1;
	*GraphicsX2Reg = x2;			
	*GraphicsColourReg = Colour;
	*GraphicsCommandReg = DRAW_H_LINE;
}

/********************************************************************************************* This function draw a vertical line, 1 pixel at a time starting at the x,y coords specified
*********************************************************************************************/

void draw_v_line(int x1, int y1, int y2, int Colour)
{
	WAIT_FOR_GRAPHICS;

	*GraphicsX1Reg = x1;
	*GraphicsY1Reg = y1;
	*GraphicsY2Reg = y2;
	*GraphicsColourReg = Colour;
	*GraphicsCommandReg = DRAW_V_LINE;
}

/*******************************************************************************
*******************************************************************************/

void draw_line(int x1, int y1, int x2, int y2, int Colour)
{
	WAIT_FOR_GRAPHICS;

	*GraphicsX1Reg = x1;
	*GraphicsX2Reg = x2;
	*GraphicsY1Reg = y1;
	*GraphicsY2Reg = y2;
	*GraphicsColourReg = Colour;
	*GraphicsCommandReg = DRAW_LINE;
}

/*******************************************************************************
*******************************************************************************/

void clear(int Colour)
{
	WAIT_FOR_GRAPHICS;

	*GraphicsColourReg = Colour;
	*GraphicsCommandReg = CLEAR_SCREEN;
}

/*******************************************************************************
** FILLS INSIDE THE COORDINATES (DOES NOT INCLUDE THE COORDINATES THEMSELVES)
*******************************************************************************/

void fill_square(int x1, int x2, int y1, int y2, int Colour)
{
	WAIT_FOR_GRAPHICS;

	*GraphicsX1Reg = x1;
	*GraphicsX2Reg = x2;
	*GraphicsY1Reg = y1;
	*GraphicsY2Reg = y2;	
	*GraphicsColourReg = Colour;
	*GraphicsCommandReg = FILL;
}

/*********************************************************************************************
*********************************************************************************************/

void draw_square(int x1, int x2, int y1, int y2, int Colour)
{
	draw_h_line(x1, y1, x2, Colour);
	draw_v_line(x2, y1, y2, Colour);
	draw_v_line(x1, y1, y2, Colour);
	draw_h_line(x1, y2, x2, Colour);
}
