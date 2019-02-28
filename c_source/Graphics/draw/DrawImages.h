/*
 * DrawImages.h
 *
 *  Created on: Feb 20, 2019
 *      Author: Nathalie
 */

#ifndef DRAWIMAGES_H_
#define DRAWIMAGES_H_

extern const unsigned char Next_Arrow[];
extern const unsigned char Back_Arrow[];
extern const unsigned char Small_Circle[];
extern const unsigned char Walking_Person[];

void NextArrow(int x, int y, int colour);
void BackArrow(int x, int y, int colour);
void Circle(int centre_x, int centre_y, int colour);
void Person(int screenx, int screeny, int x, int y, int colour);

#endif /* DRAWIMAGES_H_ */
