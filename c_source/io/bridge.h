/**
 * Contains the the virtual memories access to the peripherals connected to the DE1
 * Since processes cannot access physical addresses directly on Linux
 * - Serial port
 * - GPS
 * - Touchscreen
 * - builtin DE1
 * 
 * Call bridge_init() before accessing these addresses
 */

#ifndef BRIDGE_H
#define BRIDGE_H

#define HW_REGS_BASE ( 0xff200000 )
#define HW_REGS_SPAN ( 0x00200000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

/* ========================================================================== */
/* ================ ONBOARD IO ============================================== */
#define SWITCHES_PADDR    0xff200000
#define PUSHBUTTONS_PADDR 0xff200010
#define RED_LEDS_PADDR    0xff200020
#define HEX0_1_PADDR      0xff200030
#define HEX2_3_PADDR      0xff200040
#define HEX4_5_PADDR      0xff200050

volatile unsigned short int *Switches;
volatile unsigned short int *PushButtons;
volatile unsigned short int *LEDs;
volatile unsigned short int *Hex01;
volatile unsigned short int *Hex23;
volatile unsigned short int *Hex45;

/* ========================================================================== */
/* ================ SERIAL ================================================== */
#define RS232_ReceiverFifo_PADDR                0xf210200
#define RS232_TransmitterFifo_PADDR             0xf210200
#define RS232_InterruptEnableReg_PADDR          0xf210202
#define RS232_InterruptIdentificationReg_PADDR  0xf210204
#define RS232_FifoControlReg_PADDR              0xf210204
#define RS232_LineControlReg_PADDR              0xf210206
#define RS232_ModemControlReg_PADDR             0xf210208
#define RS232_LineStatusReg_PADDR               0xf21020A
#define RS232_ModemStatusReg_PADDR              0xf21020C
#define RS232_ScratchReg_PADDR                  0xf21020E
#define RS232_DivisorLatchLSB_PADDR             0xf210200
#define RS232_DivisorLatchMSB_PADDR             0xf210202

volatile unsigned short int *RS232_ReceiverFifo;
volatile unsigned short int *RS232_TransmitterFifo;
volatile unsigned short int *RS232_InterruptEnableReg;
volatile unsigned short int *RS232_InterruptIdentificationReg;
volatile unsigned short int *RS232_FifoControlReg;
volatile unsigned short int *RS232_LineControlReg;
volatile unsigned short int *RS232_ModemControlReg;
volatile unsigned short int *RS232_LineStatusReg;
volatile unsigned short int *RS232_ModemStatusReg;
volatile unsigned short int *RS232_ScratchReg;
volatile unsigned short int *RS232_DivisorLatchLSB;
volatile unsigned short int *RS232_DivisorLatchMSB;

/* =========================================================================== */
/* ================ TOUCHSCREEN ============================================== */
#define GraphicsCommandRegD_PADDR          0xff210000
#define GraphicsStatusReg_PADDR            0xff210000
#define GraphicsX1Reg_PADDR                0xff210002
#define GraphicsY1Reg_PADDR                0xff210004
#define GraphicsX2Reg_PADDR                0xff210006
#define GraphicsY2Reg_PADDR                0xff210008
#define GraphicsColourReg_PADDR            0xff21000E
#define GraphicsBackGroundColourReg_PADDR  0xff210010

volatile unsigned short int *GraphicsCommandReg;   		
volatile unsigned short int *GraphicsStatusReg;   		
volatile unsigned short int *GraphicsX1Reg;   			
volatile unsigned short int *GraphicsY1Reg;   			
volatile unsigned short int *GraphicsX2Reg;   			
volatile unsigned short int *GraphicsY2Reg;   			
volatile unsigned short int *GraphicsColourReg;   		
volatile unsigned short int *GraphicsBackGroundColourReg;   	

/* ========================================================================== */
/* ================ GPS ===================================================== */
#define GPS_ReceiverFifo                0xff210200
#define GPS_TransmitterFifo             0xff210200
#define GPS_InterruptEnableReg          0xff210202
#define GPS_InterruptIdentificationReg  0xff210204
#define GPS_FifoControlReg              0xff210204
#define GPS_LineControlReg              0xff210206
#define GPS_ModemControlReg             0xff210208
#define GPS_LineStatusReg               0xff21020a
#define GPS_ModemStatusReg              0xff21020c
#define GPS_ScratchReg                  0xff21020e
#define GPS_DivisorLatchLSB             0xff210200
#define GPS_DivisorLatchMSB             0xff210202

volatile unsigned short int *GPS_ReceiverFifo;
volatile unsigned short int *GPS_TransmitterFifo;
volatile unsigned short int *GPS_InterruptEnableReg;
volatile unsigned short int *GPS_InterruptIdentificationReg;
volatile unsigned short int *GPS_FifoControlReg;
volatile unsigned short int *GPS_LineControlReg;
volatile unsigned short int *GPS_ModemControlReg;
volatile unsigned short int *GPS_LineStatusReg;
volatile unsigned short int *GPS_ModemStatusReg;
volatile unsigned short int *GPS_ScratchReg;
volatile unsigned short int *GPS_DivisorLatchLSB;
volatile unsigned short int *GPS_DivisorLatchMSB;

/* ========================================================================== */
/**
 * initalize and set up the virtual addresses, call before accessing them
 */
void bridge_init();

/**
 * free and clean up the addresses
 */
void bridge_close();

#endif // BRIDGE_H