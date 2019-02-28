/*
 * Wifi.c
 *
 *  Created on: Jan 24, 2019
 *      Author: Nathalie
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "Wifi.h"
#include "../io/bridge.h"

/*
 * Puts character into Transmitter Fifo so it can be read by wifi module
 */
char putcharWifi(char input)
{
 // wait for Transmitter Holding Register bit (5) of line status register to be '1'
    while (!(*Wifi_LineStatusReg && 0x20));
    *Wifi_TransmitterFifo = input;
    return input;
}

/*
 * Reads character from Reciever Fifo
 */
unsigned char getcharWifi( void )
{
 // wait for Data Ready bit (0) of line status register to be '1'
    while (!(*Wifi_LineStatusReg & 0x1));
    return *Wifi_ReceiverFifo;
}

/*
 * the following function polls the UART to determine if any character
 * has been received. It doesn't wait for one, or read it, it simply tests
 * to see if one is available to read from the FIFO
 */
int WifiTestForReceivedData(void)
{
 // if *Wifi_LineStatusReg bit 0 is set to 1
    if (*Wifi_LineStatusReg & 0x1){
        return 1;
    }
 //return TRUE, otherwise return FALSE
    return 0;

}

/*
 * Sends contents of char pointer to UART
 */
void WifiSendLine(char* message){
	for(int i = 0; i < strlen(message); i ++){
			usleep(10000);
	}
}

/*
 * saves the data received from the wifi chip to a buffer
 */
void saveBuffer(void)
{
	 char Buffer[100];
	 int i = 0;
	 while (*Wifi_LineStatusReg & 0x1){
	        Buffer[i] = *Wifi_ReceiverFifo;
	        i++;
	 }

	 return;
}

/*
 * Remove/flush the UART receiver buffer by removing any unread characters
 */
void WifiFlush(void)
{
 // while bit 0 of Line Status Register == �1�
    while (*Wifi_LineStatusReg & 0x1){
        *Wifi_ReceiverFifo;
    }
    return;
}

/*
 * initializes wifi module and connects to wifi
 */
void Init_Wifi(void)
{
	//set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
	  *Wifi_LineControlReg = 0x80;
	//set Divisor latch (LSB and RSB) with correct value for required baud rate
	  *Wifi_DivisorLatchLSB = 0x1B;
	  *Wifi_DivisorLatchMSB = 0;

	//set bit 7 of Line Control Register back to 0 and
	  *Wifi_LineControlReg = *Wifi_LineControlReg & 0x7F;
	//program other bits in that reg for 8 bit data, 1, stop bit, no parity etc
	  *Wifi_LineControlReg = 0x3;

	//Reset the Fifo's in the FiFo Control Reg by setting bits 1 & 2
	  *Wifi_FifoControlReg = 0x6;

	//Now clear all bits in the FiFo control registers
	  *Wifi_FifoControlReg = 0;

	  //connect to wifi
	  char EndLine[2] = "\r\n" ;
	  char StartFile[35] = "dofile(\"send_text_message.lua\")\r\n";
	  WifiSendLine(EndLine);
	  saveBuffer();
	  WifiSendLine(EndLine);
	  saveBuffer();
	  WifiSendLine(EndLine);
	  saveBuffer();

	  //open wifi file and execute send msg function
	  WifiSendLine(StartFile);
	  saveBuffer();
}

/*
 * sends text through twillio containing the content to the char* message
 */
void WifiSendText(char* message){
	char CheckWifi1[12] = "check_wifi(\"";
	char CheckWifi2[4] = "\")\r\n";
	WifiSendLine(CheckWifi1);
	WifiSendLine(message);
	WifiSendLine(CheckWifi2);
	saveBuffer();

	WifiFlush();
}

