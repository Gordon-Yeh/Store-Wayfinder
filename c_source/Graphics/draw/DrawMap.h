/*
 * DrawMap.h
 *
 *  Created on: Feb 20, 2019
 *      Author: Nathalie
 */

#ifndef DRAWMAP_H_
#define DRAWMAP_H_

extern const unsigned char Map[];

void DrawMap(int x, int y);
void DrawMapSection(int screenx, int screeny, int mapx, int mapy);

#endif /* DRAWMAP_H_ */
