#ifndef BRIDGE_H
#define BRIDGE_H

#define HW_REGS_BASE ( 0xff200000 )
#define HW_REGS_SPAN ( 0x00200000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

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

/* ================ SERIAL ================================================= */
#define RS232_ReceiverFifo_PADDR                    0xFF210200
#define RS232_TransmitterFifo_PADDR                     0xFF210200
#define RS232_InterruptEnableReg_PADDR                  0xFF210202
#define RS232_InterruptIdentificationReg_PADDR                  0xFF210204
#define RS232_FifoControlReg_PADDR                  0xFF210204
#define RS232_LineControlReg_PADDR                  0xFF210206
#define RS232_ModemControlReg_PADDR                     0xFF210208
#define RS232_LineStatusReg_PADDR                   0xFF21020A
#define RS232_ModemStatusReg_PADDR                  0xFF21020C
#define RS232_ScratchReg_PADDR                  0xFF21020E
#define RS232_DivisorLatchLSB_PADDR                     0xFF210200
#define RS232_DivisorLatchMSB_PADDR                     0xFF210202

/* ================ GRAPHICS ============================================== */
#define GRAPHICS_COMMAND_REG_PADDR           0xff210000
#define GRAPHICS_STATUS_REG_PADDR            0xff210000
#define GRAPHICS_X1_REG_PADDR                0xff210002
#define GRAPHICS_Y1_REG_PADDR                0xff210004
#define GRAPHICS_X2_REG_PADDR                0xff210006
#define GRAPHICS_Y2_REG_PADDR                0xff210008
#define GRAPHICS_COLOUR_REG_PADDR            0xff21000E
#define GRAPHICS_BACKGROUND_COLOUR_REG_PADDR 0xff210010

volatile unsigned short int *GraphicsCommandReg;   		
volatile unsigned short int *GraphicsStatusReg;   		
volatile unsigned short int *GraphicsX1Reg;   			
volatile unsigned short int *GraphicsY1Reg;   			
volatile unsigned short int *GraphicsX2Reg;   			
volatile unsigned short int *GraphicsY2Reg;   			
volatile unsigned short int *GraphicsColourReg;   		
volatile unsigned short int *GraphicsBackGroundColourReg;   	

/* ================ GPS ================================================= */

// initalize 
void bridge_init();

// 
void bridge_close();

#endif // BRIDGE_H