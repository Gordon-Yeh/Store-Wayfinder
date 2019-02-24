/**
 * GPS.h
 * Serial communicstion between GPS chip and DE1.
 * Parse longtitude and latitude data into double long for later use
 * 
 * Author: Skylar
 * Date: Feb 20, 2019
*/
#ifndef GPS_H
#define GPS_H

typedef struct {
	double lon;
	double lat;
} gps_point;

void Init_GPS();
unsigned char getChar();
char putChar(char c);
void writeCmd(char* arr);
void getData(char alldata[100]);
void GPSFlush();
gps_point* getPoint();

#endif