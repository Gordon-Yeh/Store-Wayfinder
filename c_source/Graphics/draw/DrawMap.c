/*
 * DrawMap.c
 *
 *  Created on: Feb 20, 2019
 *      Author: Nathalie
 */
#include <string.h>

#include "draw.h"
#include "../Defines.h"
#include "../Colours.h"
#include "DrawMap.h"

//Draws the map image at the given coordinates - 518x418 pixels
void DrawMap(int x, int y){
	int row, column;
	unsigned char colour;
	int i = 0;

	if(((short)(x) > (short)(XRES-1)) || ((short)(y) > (short)(YRES-1)))  // if start off edge of screen don't bother
		return ;

	for(row = 0; row < 418 ; row ++)	{							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
		for(column = 0; column < 518; column++) {
			colour = Map[i] ;
			if(colour == 10)
				draw_pixel(x+column, y+row, GRAY) ;
			if(colour == 30)
				draw_pixel(x+column, y+row, ORANGE) ;
			if(colour == 0)
				draw_pixel(x+column, y+row, BLACK) ;
			if(colour == 1)
				draw_pixel(x+column, y+row, WHITE) ; //DEBUG - we can remove this line once we're drawing a background
			i++;
		}
	}
}

/*
 * Draws a map section of the size of the person symbol
 * screenx, screeny: upper left corner of map if it were drawn in full
 * mapx, mapy: center of map section being drawn (relative to map coordinates - not dependent on
 * 		positioning of map on screen)
 */
void DrawMapSection(int screenx, int screeny, int mapx, int mapy){
	int row, column;
	unsigned char colour;
	int i = (mapy-12)*518+mapx-9; //person 18x25

	if(((short)(screenx) > (short)(XRES-1)) || ((short)(screeny) > (short)(YRES-1)))  // if start off edge of screen don't bother
		return ;

	for(row = mapy-12; row < mapy+13 ; row ++)	{							   											// set of hex 200 i.e. bit 7-0 = 0010 0000 0000
		for(column = mapx-9; column < mapx+9; column++) {
			colour = Map[i] ;
			if(colour == 10)
				draw_pixel(screenx+column, screeny+row, GRAY) ;
			if(colour == 30)
				draw_pixel(screenx+column, screeny+row, ORANGE) ;
			if(colour == 0)
				draw_pixel(screenx+column, screeny+row, BLACK) ;
			if(colour == 1)
				draw_pixel(screenx+column, screeny+row, WHITE) ;
			i++;
		}
		i = i+500;
	}
}
