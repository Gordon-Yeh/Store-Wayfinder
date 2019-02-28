/*
 * Bluetooth.c
 *
 *  Created on: Jan 22, 2019
 *      Author: linli
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../io/bridge.h"
#include "bluetooth.h"

void Init_BT(void){
//set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
  *BT_LineControlReg = 0x80;
//set Divisor latch (LSB and RSB) with correct value for required baud rate
  *BT_DivisorLatchLSB = 27;
  *BT_DivisorLatchMSB = 0;

//set bit 7 of Line Control Register back to 0 and
//program other bits in that reg for 8 bit data, 1, stop bit, no parity etc
  *BT_LineControlReg = 0x3;

//Reset the Fifo's in the FiFo Control Reg by setting bits 1 & 2
  *BT_FifoControlReg = 0x6;

//Now clear all bits in the FiFo control registers
  *BT_FifoControlReg = 0;
  printf("Bluetooth Initialization succeed\n");

}

void BT_Flush(void){

	while(*BT_LineStatusReg & 0x1){
		*BT_ReceiverFifo;
	}

}

int BT_TestForReceiveData(void){
	// if RS232_LineStatusReg bit 0 is set to 1
	//return TRUE, otherwise return FALSE
	if((*BT_LineStatusReg & 0x1) == 1){
		return 1;
	}

	return 0;
}



int getcharBT(void){
	// wait for Data Ready bit (0) of line status register to be '1'
	// read new character from ReceiverFiFo register
	// return new character
	while(!(*BT_LineStatusReg & 0x1));

	int result = *BT_ReceiverFifo;
	return result;
}

int putcharBT(int c){
	// wait for Transmitter Holding Register bit (5) of line status register to be '1‘
	// indicating we can write to the device
	// write character to Transmitter fifo register
	// return the character we printed
  while(!(*BT_LineStatusReg && 0x20));

  *BT_TransmitterFifo = c;

  return c;
}

int bt_receive_message(char ** buffer_ptr) {
    char curr_char;

    const int buffer_size = 300;
    int start = 0;
    int char_count = 0;
 
    char * buffer = malloc(buffer_size);
    buffer[0] = '\0';
    unsigned int i = 0;
    while (1) {
        if (BT_TestForReceiveData() == 1) {
            curr_char = (char) getcharBT();
            // starting case
            if (!start && curr_char == '@') {
                start = 1;
                continue;
            }

            // terminating case
            if (start && curr_char == '?')
                break;

            // concat the character to end of buffer
            if (start) {
                if (++char_count > buffer_size) {
                    free(buffer);
                    return BUFFER_OVERFLOW;
                }
                strncat(buffer, (char *) (&curr_char), 1);
                i = 0;
            }

            if (++i > 50000000) {
              return TIME_OUT;
            }
        }
    }

    *buffer_ptr = buffer;
    return 0;
}

void bt_send_message(char * message) {
    printf("sending message: %s\n", message);
	for (int i = 0; i < strlen(message); i++) {
		putcharBT((int) message[i]);
	}
    // terminating charaters
    putcharBT('\r');
    putcharBT('\n');
}
