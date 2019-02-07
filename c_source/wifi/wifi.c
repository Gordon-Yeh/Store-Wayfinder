/*
 * Wifi.c
 *
 *  Created on: Jan 24, 2019
 *      Author: Nathalie
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define Wifi_ReceiverFifo (*(volatile unsigned char *)(0xFF210240))
#define Wifi_TransmitterFifo (*(volatile unsigned char *)(0xFF210240))
#define Wifi_InterruptEnableReg (*(volatile unsigned char *)(0xFF210242))
#define Wifi_InterruptIdentificationReg (*(volatile unsigned char *)(0xFF210244))
#define Wifi_FifoControlReg (*(volatile unsigned char *)(0xFF210244))
#define Wifi_LineControlReg (*(volatile unsigned char *)(0xFF210246))
#define Wifi_ModemControlReg (*(volatile unsigned char *)(0xFF210248))
#define Wifi_LineStatusReg (*(volatile unsigned char *)(0xFF21024A))
#define Wifi_ModemStatusReg (*(volatile unsigned char *)(0xFF21024C))
#define Wifi_ScratchReg (*(volatile unsigned char *)(0xFF21024E))
#define Wifi_DivisorLatchLSB (*(volatile unsigned char *)(0xFF210240))
#define Wifi_DivisorLatchMSB (*(volatile unsigned char *)(0xFF210242))

void Init_Wifi(void)
{
	//set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
	  Wifi_LineControlReg = 0x80;
	//set Divisor latch (LSB and RSB) with correct value for required baud rate
	  Wifi_DivisorLatchLSB = 0x1B;
	  Wifi_DivisorLatchMSB = 0;

	//set bit 7 of Line Control Register back to 0 and
	  Wifi_LineControlReg = Wifi_LineControlReg & 0x7F;
	//program other bits in that reg for 8 bit data, 1, stop bit, no parity etc
	  Wifi_LineControlReg = 0x3;

	//Reset the Fifo's in the FiFo Control Reg by setting bits 1 & 2
	  Wifi_FifoControlReg = 0x6;

	//Now clear all bits in the FiFo control registers
	  Wifi_FifoControlReg = 0;
	  printf("Initialization succeeded\n");
}

char putcharWifi(char input)
{
 // wait for Transmitter Holding Register bit (5) of line status register to be '1'
    while (!(Wifi_LineStatusReg && 0x20));
    Wifi_TransmitterFifo = input;
    return input;
}

unsigned char getcharWifi( void )
{
 // wait for Data Ready bit (0) of line status register to be '1'
    while (!(Wifi_LineStatusReg & 0x1));
    return Wifi_ReceiverFifo;
}

// the following function polls the UART to determine if any character
// has been received. It doesn't wait for one, or read it, it simply tests
// to see if one is available to read from the FIFO
int WifiTestForReceivedData(void)
{
 // if Wifi_LineStatusReg bit 0 is set to 1
    if (Wifi_LineStatusReg & 0x1){
        return 1;
    }
 //return TRUE, otherwise return FALSE
    return 0;

}

void saveAndPrintBuffer(void)
{
	 char Buffer[100];
	 int i = 0;
	 while (Wifi_LineStatusReg & 0x1){
	        Buffer[i] = Wifi_ReceiverFifo;
	        //printf("%c\n", Buffer[i]); //DEBUG
	        i++;
	 }
	 printf("%s\n", Buffer);

	 return;
}


//
// Remove/flush the UART receiver buffer by removing any unread characters
//
void WifiFlush(void)
{
 // while bit 0 of Line Status Register == ‘1’
    while (Wifi_LineStatusReg & 0x1){
        Wifi_ReceiverFifo;
    }
    return;
}

void delay(double number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = (int) (1000 * number_of_seconds);

    // Saving start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void WifiSendLine(char* message){
	for(int i = 0; i < strlen(message); i ++){
			char c = putcharWifi(message[i]);
			delay(0.01);
	}
}

int main (void){

	   Init_Wifi();
	   WifiFlush();

	   char EndLine[2] = "\r\n" ;
	   char StartFile[35] = "dofile(\"send_text_message.lua\")\r\n";
	   char CheckWifi[14] = "check_wifi()\r\n";


	  //send new line characters to get wifi dongle to lock onto baud rate
      WifiSendLine(EndLine);
	  saveAndPrintBuffer();
	  delay(0.5);
	  WifiSendLine(EndLine);
	  saveAndPrintBuffer();
	  delay(0.5);
	  WifiSendLine(EndLine);
	  saveAndPrintBuffer();
	  delay(0.5);

	  //open wifi file and execute send msg function
      WifiSendLine(StartFile);
      saveAndPrintBuffer();
      delay(0.5);
      WifiSendLine(CheckWifi);
      saveAndPrintBuffer();
      delay(0.5);

      WifiFlush();

      return 0;

}
