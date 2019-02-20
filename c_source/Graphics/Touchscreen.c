#include "Touchscreen.h"

#define TS_ReceiverFifo 				(*(volatile unsigned char *)(0xFF210230))
#define TS_TransmitterFifo 				(*(volatile unsigned char *)(0xFF210230))
#define TS_InterruptEnableReg 			(*(volatile unsigned char *)(0xFF210232))
#define TS_InterruptIdentificationReg 	(*(volatile unsigned char *)(0xFF210234))
#define TS_FifoControlReg 				(*(volatile unsigned char *)(0xFF210234))
#define TS_LineControlReg 				(*(volatile unsigned char *)(0xFF210236))
#define TS_ModemControlReg				(*(volatile unsigned char *)(0xFF210238))
#define TS_LineStatusReg 				(*(volatile unsigned char *)(0xFF21023A))
#define TS_ModemStatusReg 				(*(volatile unsigned char *)(0xFF21023C))
#define TS_ScratchReg 					(*(volatile unsigned char *)(0xFF21023E))
#define TS_DivisorLatchLSB 				(*(volatile unsigned char *)(0xFF210230))
#define TS_DivisorLatchMSB 				(*(volatile unsigned char *)(0xFF210232))

/*****************************************************************************
** Initialise touch screen controller
*****************************************************************************/
void Init_Touch(void) {
	// Program serial port to communicate with touchscreen
	// send touchscreen controller an "enable touch" command
 // set bit 7 of Line Control Register to 1, to gain access to the baud rate registers
    TS_LineControlReg = 0x80;
 // set Divisor latch (LSB and MSB) with correct value for required baud rate (9600)
 // 50x10^6/(16*9600) = 325.5 = 325 rounded down
    TS_DivisorLatchLSB = 0x45;
    TS_DivisorLatchMSB = 0x1;
 // set bit 7 of Line control register back to 0 and
 // program other bits in that reg for 8 bit data, 1 stop bit, no parity etc
    TS_LineControlReg = 0x3;
 // Reset the Fifo’s in the FiFo Control Reg by setting bits 1 & 2
    TS_FifoControlReg = 0x6; // 0000 0110
 // Now Clear all bits in the FiFo control registers
    TS_FifoControlReg = 0;
	//TOUCH_ENABLE command
	while(!(TS_LineStatusReg & 0x20)) ; //wait for transmitter_fifo to not be empty
    TS_TransmitterFifo = 0x55;
    while(!(TS_LineStatusReg & 0x20)) ;
    TS_TransmitterFifo = 0x1;
    while(!(TS_LineStatusReg & 0x20)) ;
    TS_TransmitterFifo = 0x12;
}

/*****************************************************************************
** test if screen touched
*****************************************************************************/
int ScreenTouched( void ) {
	// return TRUE if any data received from serial port connected to
	// touchscreen or FALSE otherwise
	return (TS_ReceiverFifo & 0x1);
}

/*****************************************************************************
** wait for screen to be touched
*****************************************************************************/
void WaitForTouch() {
	while(!ScreenTouched())
	;
}

int getReceiverFifo(void) {
	while(!(TS_LineStatusReg & 0x1)) //wait for receiver_fifo to not be empty
		;
	return TS_ReceiverFifo;
}

/*****************************************************************************
* This function waits for a touch screen press event and returns X,Y coord
*****************************************************************************/
Point GetPress(void) {
	// wait for a pen down command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	UnscaledPoint unsca_p;
	WaitForTouch();
	while((getReceiverFifo() & 0x81) != 0x81) //wait for pen down command
		;
	unsca_p.x = getReceiverFifo(); //lower 7 bits
	unsca_p.x |= (getReceiverFifo() << 7); //upper 5 bits
	unsca_p.y = getReceiverFifo(); //lower 7 bits
	unsca_p.y |= (getReceiverFifo() << 7); //upper 5 bits
	
	Point p = ScalePoint(unsca_p);
	return p;
}

/*****************************************************************************
* This function waits for a touch screen release event and returns X,Y coord
*****************************************************************************/
Point GetRelease(void) {
	// wait for a pen up command then return the X,Y coord of the point
	// calibrated correctly so that it maps to a pixel on screen
	UnscaledPoint unsca_p;
	WaitForTouch();
	while((getReceiverFifo() & 0x81) != 0x80) //wait for pen up command
		;
	unsca_p.x = getReceiverFifo(); //lower 7 bits
	unsca_p.x |= (getReceiverFifo() << 7); //upper 5 bits
	unsca_p.y = getReceiverFifo(); //lower 7 bits
	unsca_p.y |= (getReceiverFifo() << 7); //upper 5 bits
	
	Point p = ScalePoint(unsca_p);
	return p;
}

Point ScalePoint(UnscaledPoint unsca_p) {
	Point p;
	p.x = (unsca_p.x) * 799/4000;
	p.y = (unsca_p.y - 120) *479/3900;
	return p;
}