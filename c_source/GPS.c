#include <stdio.h>
#include "io/bridge.h"

void Init_GPS(void){
    // set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
    *GPS_LineControlReg = *GPS_LineControlReg | 0x80;
 // set Divisor latch (LSB and MSB) with correct value for required baud rate
    *GPS_DivisorLatchLSB = 0x45;
    *GPS_DivisorLatchMSB = 0x1;
 // set bit 7 of Line control register back to 0 and
    *GPS_LineControlReg = *GPS_LineControlReg & 0x7F;
 // program other bits in that reg for 8 bit data, 1 stop bit, no parity etc
    *GPS_LineControlReg = 0x3;
 // Reset the Fifo’s in the FiFo Control Reg by setting bits 1 & 2
    *GPS_FifoControlReg = *GPS_FifoControlReg | 0x6; // 0000 0110
 // Now Clear all bits in the FiFo control registers
    *GPS_FifoControlReg = 0;
}

char readGPS(){
    while(!(*GPS_LineStatusReg & 0x1));
    return *GPS_ReceiverFifo;
}

char writeGPS(char c){
    while (!(*GPS_LineStatusReg & 0x20));
    *GPS_TransmitterFifo = c;
    return c;
}

void writeCmd(char *arr){
    for (int i=0; i < sizeof(arr); i++){
        writeGPS(arr[i]);
    }
}

void getDataGGA(void){
    char result = readGPS();
    char* all_data;
    for (int i=0; result != '*'; i++){
        all_data[i] = result;
        result = readGPS();
    }
}

void GPSFlush(void)
{
 // while bit 0 of Line Status Register == ‘1’
    while (*GPS_LineStatusReg & 0x1){
        *GPS_ReceiverFifo;
    }
 // read unwanted char out of fifo receiver buffer
    return; // no more characters so return
}
