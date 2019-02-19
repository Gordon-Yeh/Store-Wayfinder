#ifndef BRIDGE_H
#define BRIDGE_H

#define HW_REGS_BASE ( 0xff200000 )
#define HW_REGS_SPAN ( 0x00200000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )

/* ================ ONBOARD IO ============================================== */
#define SWITCHES_PADDR    0xFF200000
#define PUSHBUTTONS_PADDR 0xFF200010
#define RED_LEDS_PADDR    0xFF200020
#define HEX0_1_PADDR      0xFF200030
#define HEX2_3_PADDR      0xFF200040
#define HEX4_5_PADDR      0xFF200050

volatile unsigned short int *Switches;
volatile unsigned short int *PushButtons;
volatile unsigned short int *LEDs;
volatile unsigned short int *Hex01;
volatile unsigned short int *Hex23;
volatile unsigned short int *Hex45;

/* ================ SERIAL ================================================= */

/* ================ GRAPHICS ============================================== */
#define GRAPHICS_COMMAND_REG_PADDR           0xFF210000
#define GRAPHICS_STATUS_REG_PADDR            0xFF210000
#define GRAPHICS_X1_REG_PADDR                0xFF210002
#define GRAPHICS_Y1_REG_PADDR                0xFF210004
#define GRAPHICS_X2_REG_PADDR                0xFF210006
#define GRAPHICS_Y2_REG_PADDR                0xFF210008
#define GRAPHICS_COLOUR_REG_PADDR            0xFF21000E
#define GRAPHICS_BACKGROUND_COLOUR_REG_PADDR 0xFF210010

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