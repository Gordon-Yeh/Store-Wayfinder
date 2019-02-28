#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#define BUFFER_OVERFLOW 1
#define TIME_OUT 2

/**
 * initalizes the bluetooth module
 * call this before any other bluetooth functions
 */
void Init_BT(void);

/**
 * receive and stores the next message received by bluetooth
 * the string should be termincated via the null char '\0'
 * @effects point buffer_ptr to the message buffer
 * @returns 0 if successful
 *          otherwise - error code
 */
int bt_receive_message(char ** buffer_ptr);

/**
 * sends a message through the bluetooth module
 * @param message to send
 */
void bt_send_message(char * message);

#endif