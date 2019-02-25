//define 7seg display
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../io/bridge.h"
#include "GPS.h"

void Init_GPS(void)
{
   // set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
   *GPS_LineControlReg = *GPS_LineControlReg | 0x80;
   // set Divisor latch (LSB and MSB) with correct value for required baud rate
   *GPS_DivisorLatchLSB = 0x45;
   *GPS_DivisorLatchMSB = 0x1;
   // set bit 7 of Line control register back to 0 and
   *GPS_LineControlReg = *GPS_LineControlReg & 0x7F;
   // program other bits in that reg for 8 bit data, 1 stop bit, no parity etc
   *GPS_LineControlReg = 0x3;
   // Reset the Fifo�s in the FiFo Control Reg by setting bits 1 & 2
   *GPS_FifoControlReg = *GPS_FifoControlReg | 0x6; // 0000 0110
                                                  // Now Clear all bits in the FiFo control registers
   *GPS_FifoControlReg = 0;


}

unsigned char getChar()
{
   while (!(*GPS_LineStatusReg & 0x1));
   return *GPS_ReceiverFifo;
}

char putChar(char c)
{
   while (!(*GPS_LineStatusReg & 0x20));
   *GPS_TransmitterFifo = c;
   return c;
}
void writeCmd(char* arr)
{
   for (int i = 0; i < sizeof(arr); i++)
   {
       putChar(arr[i]);
   }
}

void getData(char all_data[100])
{
   char val;
   int i;
   for (i = 0; val != '*' && i < 100; i++)
   {
   	val = getChar();
       all_data[i] = val;
   }

   if (i<100)
   		all_data[i] = '\0';
}

void GPSFlush(void)
{
   // while bit 0 of Line Status Register == �1�
   while (*GPS_LineStatusReg & 0x1)
   {
       *GPS_ReceiverFifo;
   }
   // read unwanted char out of fifo receiver buffer
   return; // no more characters so return
}
gps_point* getPoint(){
   char* msg = "$PMTK183*38<CR><LF>";
   writeCmd(msg);

   //read result
   char all_data[100];
   getData(all_data);

   GPSFlush();

   char* temp = strtok(all_data, ",");
   char* longitude, *latitude;
   for (int i=0; i<5 && temp != NULL; i++){
      longitude = i==2? temp : longitude;
      latitude = i==4? temp : latitude;      
      temp = strtok(NULL, ",");
   }

   char lon_H[3], lon_M[7];
   memcpy(lon_H, &longitude[0], 2);
   memcpy(lon_M, &longitude[2], 6);
   lon_H[2] = '\0';
   lon_M[6] = '\0';
   float h = atof((const char*)lon_H);
   float m = atof((const char*)lon_M)/60;
   float x = h+m;

   char lat_H[4], lat_M[7];
   memcpy(lat_H, &latitude[0], 3);
   memcpy(lat_M, &latitude[3], 6);
   lat_H[3] = '\0';
   lat_M[6] = '\0';
   float y = atof((const char*)lat_H) + atof((const char*)lat_M)/60;

   gps_point* p = malloc(sizeof(gps_point));
   p->lon = x;
   p->lat = y;

   return p;
}
