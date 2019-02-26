/*
 * drawImages.c
 *
 *  Created on: Feb 20, 2019
 *      Author: Nathalie
 */

#include <string.h>

#include "draw.h"
#include "../Defines.h"
#include "../Colours.h"
#include "DrawImages.h"
//TODO: 5x5 circle

void NextArrow(int x, int y, int colour){
	int row, column, pixel;
	int i = 0;

	if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
		return ;

	for(row = 0; row < 50 ; row ++)	{							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
		for(column = 0; column < 50; column++) {
			pixel = Next_Arrow[i] ;
			if(pixel == 1)
				draw_pixel(x+column, y+row, colour) ; //DEBUG - we can remove this line once we're drawing a background
			i++;
		}
	}
}

void BackArrow(int x, int y, int colour){
	int row, column, pixel;
	int i = 0;

	if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
		return ;

	for(row = 0; row < 50 ; row ++)	{							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
		for(column = 0; column < 50; column++) {
			pixel = Back_Arrow[i] ;
			if(pixel == 1)
				draw_pixel(x+column, y+row, colour) ; //DEBUG - we can remove this line once we're drawing a background
			i++;
		}
	}
}

void Circle(int x, int y, int colour){
	int row, column, pixel;
	int i = 0;

	if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
		return ;

	for(row = 0; row < 5 ; row ++)	{							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
		for(column = 0; column < 5; column++) {
			pixel = Small_Circle[i] ;
			if(pixel == 1)
				draw_pixel(x+column, y+row, colour) ; //DEBUG - we can remove this line once we're drawing a background
			i++;
		}
	}
}

void Person(int x, int y, int colour){
	int row, column, pixel;
	int i = 0;

	if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
		return ;

	for(row = 0; row < 30 ; row ++)	{							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
		for(column = 0; column < 21; column++) {
			pixel = Walking_Person[i] ;
			if(pixel == 1)
				draw_pixel(x+column, y+row, colour) ; //DEBUG - we can remove this line once we're drawing a background
			i++;
		}
	}
}
