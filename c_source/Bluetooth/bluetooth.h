/*
 * Bluetooth.h
 *
 *  Created on: Jan 22, 2019
 *      Author: linli
 */
#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#define BUFFER_OVERFLOWS 1
#define TIME_OUT 2

/**
 * initalizes the bluetooth module
 * call this before any other bluetooth functions
 */
void Init_BT(void);

/**
 * @effects stores the next message received from bluetooth into buffer
 * @returns 0 if successful
 *          otherwise - error code
 */
int bt_receive_message(char * buffer);

/**
 * sends a message through the bluetooth module
 * @param message to send
 */
void bt_send_message(char * message);

#endif