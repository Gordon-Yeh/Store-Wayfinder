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

void Circle(int centre_x, int centre_y, int colour){
	int row, column, pixel;
	int i = 0;
	
	int x = centre_x - 2;
	int y = centre_y - 2;

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

/*
 * draws a person on the map
 * screenx, screeny: top left corner of map -- set to 0 if not drawn on map
 * x, y: center of person on the map (not dependent on location of map on screen)
 */
void Person(int screenx, int screeny, int x, int y, int colour){
	int row, column, pixel;
	int i = 0;

	for(row = 0; row < 25; row ++)	{							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
		for(column = 0; column < 18; column++) {
			pixel = Walking_Person[i] ;
			if(pixel == 1)
				draw_pixel(screenx+x-9+column, screeny+y-12+row, colour) ;
			i++;
		}
	}
}