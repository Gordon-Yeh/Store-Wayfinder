/*
 * Bluetooth.c
 *
 *  Created on: Jan 22, 2019
 *      Author: linli
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BT_ReceiverFifo          		(*(volatile unsigned char *)(0xFF210220))
#define BT_TransmitterFifo 				(*(volatile unsigned char *)(0xFF210220))
#define BT_InterruptEnableReg 			(*(volatile unsigned char *)(0xFF210222))
#define BT_InterruptIdentificationReg	(*(volatile unsigned char *)(0xFF210224))
#define BT_FifoControlReg				(*(volatile unsigned char *)(0xFF210224))
#define BT_LineControlReg				(*(volatile unsigned char *)(0xFF210226))
#define BT_ModemControlReg				(*(volatile unsigned char *)(0xFF210228))
#define BT_LineStatusReg				(*(volatile unsigned char *)(0xFF21022A))
#define BT_ModemStatusReg				(*(volatile unsigned char *)(0xFF21022C))
#define BT_ScratchReg					(*(volatile unsigned char *)(0xFF21022E))

#define BT_DivisorLatchLSB				(*(volatile unsigned char *)(0xFF210220))
#define BT_DivisorLatchMSB				(*(volatile unsigned char *)(0xFF210222))


void Init_BT(void){
//set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
  BT_LineControlReg = 0x80;
//set Divisor latch (LSB and RSB) with correct value for required baud rate
  BT_DivisorLatchLSB = 27;
  BT_DivisorLatchMSB = 0;

//set bit 7 of Line Control Register back to 0 and
//program other bits in that reg for 8 bit data, 1, stop bit, no parity etc
  BT_LineControlReg = 0x3;

//Reset the Fifo's in the FiFo Control Reg by setting bits 1 & 2
  BT_FifoControlReg = 0x6;

//Now clear all bits in the FiFo control registers
  BT_FifoControlReg = 0;
  printf("Bluetooth Initialization succeed\n");

}

void BT_Flush(void){

	while(BT_LineStatusReg & 0x1){
		BT_ReceiverFifo;
	}

}

int BT_TestForReceiveData(void){
	// if RS232_LineStatusReg bit 0 is set to 1
	//return TRUE, otherwise return FALSE
	if((BT_LineStatusReg & 0x1) == 1){
		return 1;
	}

	return 0;
}



int getcharBT(void){
	// wait for Data Ready bit (0) of line status register to be '1'
	// read new character from ReceiverFiFo register
	// return new character
	while(!(BT_LineStatusReg & 0x1));

	int result = BT_ReceiverFifo;
	return result;
}

int putcharBT(int c){
	// wait for Transmitter Holding Register bit (5) of line status register to be '1‘
	// indicating we can write to the device
	// write character to Transmitter fifo register
	// return the character we printed
  while(!(BT_LineStatusReg && 0x20));

  BT_TransmitterFifo = c;

  return c;
}

int bt_receive_message(char * buffer, unsigned int buffer_len) {
    int i = 0;

    while (1) {
        

    }
    for(int i = 0; i < 2000000; i ++) {
        if(BT_TestForReceiveData() == 1) {
            int c = getcharBT();
            // concat the character to end of message
            strncat(message, (char *) (&c), 1);
            i=0; // reset timer if we got something back
        }
    }
    return message;
}

void bt_send_message(char * message) {
    printf("sending message: %s\n", message);
	for (int i = 0; i < strlen(message); i ++) {
		int c = putcharBT((int)message[i]);
	}
    // terminating charaters
    putcharBT('\r');
    putcharBT('\n');
}
