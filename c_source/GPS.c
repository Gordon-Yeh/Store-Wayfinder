#define GPS_ReceiverFifo (*(volatile unsigned char *)(0xFF210210))
#define GPS_TransmitterFifo (*(volatile unsigned char *)(0xFF210210))
#define GPS_InterruptEnableReg (*(volatile unsigned char *)(0xFF210212))
#define GPS_InterruptIdentificationReg (*(volatile unsigned char *)(0xFF210214))
#define GPS_FifoControlReg (*(volatile unsigned char *)(0xFF210214))
#define GPS_LineControlReg (*(volatile unsigned char *)(0xFF210216))
#define GPS_ModemControlReg (*(volatile unsigned char *)(0xFF210218))
#define GPS_LineStatusReg (*(volatile unsigned char *)(0xFF21021A))
#define GPS_ModemStatusReg (*(volatile unsigned char *)(0xFF21021C))
#define GPS_ScratchReg (*(volatile unsigned char *)(0xFF21021E))
#define GPS_DivisorLatchLSB (*(volatile unsigned char *)(0xFF210210))
#define GPS_DivisorLatchMSB (*(volatile unsigned char *)(0xFF210212))

//define 7seg display
#include <stdio.h>
#include <stdlib.h>

void Init_GPS(void)
{
   // set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
   GPS_LineControlReg = GPS_LineControlReg | 0x80;
   // set Divisor latch (LSB and MSB) with correct value for required baud rate
   GPS_DivisorLatchLSB = 0x45;
   GPS_DivisorLatchMSB = 0x1;
   // set bit 7 of Line control register back to 0 and
   GPS_LineControlReg = GPS_LineControlReg & 0x7F;
   // program other bits in that reg for 8 bit data, 1 stop bit, no parity etc
   GPS_LineControlReg = 0x3;
   // Reset the Fifo�s in the FiFo Control Reg by setting bits 1 & 2
   GPS_FifoControlReg = GPS_FifoControlReg | 0x6; // 0000 0110
                                                  // Now Clear all bits in the FiFo control registers
   GPS_FifoControlReg = 0;


}

unsigned char getChar()
{
   while (!(GPS_LineStatusReg & 0x1));
   //printf("%x\n", GPS_ReceiverFifo);
   return GPS_ReceiverFifo;
}

char putChar(char c)
{
   while (!(GPS_LineStatusReg & 0x20));
   GPS_TransmitterFifo = c;
   return c;
}
void writeCmd(char* arr)
{
   for (int i = 0; i < sizeof(arr); i++)
   {
       putChar(arr[i]);
   }
}

int swapEndian(char *s)
{
   register int val;
   val = strtoul(s, NULL, 16);
   val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF );
   val = (val << 16) | ((val >> 16) & 0xFFFF);
   return val;
}

void getData(char* all_data)
{
   //while (!(GPS_LineStatusReg & 0x1));
   //char result = readGPS();
   char val;
   //char* all_data;
   //wait for a new cmd
   //while (readGPS() != '$');
   int i;
   for (i = 0; val != '*' && i < 100; i++)
   {
   	val = getChar();
       all_data[i] = val;
   }

   if (i<100)
   		all_data[i] = '\0';
   //int data = swapEndian(&all_data);

}

void GPSFlush(void)
{
   // while bit 0 of Line Status Register == �1�
   while (GPS_LineStatusReg & 0x1)
   {
       GPS_ReceiverFifo;
   }
   // read unwanted char out of fifo receiver buffer
   return; // no more characters so return
}


int mainGPS(void)
{
   Init_GPS();

   char* msg = "$PMTK183*38<CR><LF>";
   writeCmd(msg);

   //read result
   char* all_data = (char*) malloc(100);
   getData(all_data);
   printf("%s\n", all_data);

   GPSFlush();

   return 0;

}