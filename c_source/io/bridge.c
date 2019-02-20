#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "bridge.h"
#include "graphics_bridge.h"

static int bridge_mmap_fd;
static void onboard_bridge_init(unsigned int *virtual_base);
static void graphics_bridge_init(unsigned int *virtual_base);
static void gps_bridge_init(unsigned int *virtual_base);
static void serial_bridge_init(unsigned int *virtual_base);

void bridge_init() {
    void *virtual_base;

    // Open memory as if it were a device for read and write access
    bridge_mmap_fd = open("/dev/mem", (O_RDWR | O_SYNC));
    if (bridge_mmap_fd == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return NULL;
    }

    // map 2Mbyte of memory starting at 0xFF200000 to user space
    virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ|PROT_WRITE), MAP_SHARED, bridge_mmap_fd, HW_REGS_BASE);

    if (virtual_base == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(bridge_mmap_fd);
        return NULL;
    }

    // initalize perherials mappings
    onboard_bridge_init((unsigned int *) virtual_base);
    graphics_bridge_init((unsigned int *) virtual_base);
    gps_bridge_init((unsigned int *) virtual_base);
    serial_bridge_init((unsigned int *) virtual_base);
}

void bridge_close() {
    if (munmap(p->base, HW_REGS_SPAN) != 0) {
        printf("bridge_close: munmap() failed...\n");
    }

    if (bridge_mmap_fd >= 0) {
        close(bridge_mmap_fd);
        bridge_mmap_fd = -1;
    }

    free(p);
}

static void onboard_bridge_init(unsigned int *virtual_base) {
    Switches = 	    (unsigned int *) (virtual_base + (SWITCHES_PADDR & HW_REGS_MASK));
    PushButtons = 	(unsigned int *) (virtual_base + (PUSHBUTTONS_PADDR & HW_REGS_MASK));
    LEDs = 			(unsigned int *) (virtual_base + (RED_LEDS_PADDR & HW_REGS_MASK));
    Hex01 = 		(unsigned int *) (virtual_base + (HEX0_1_PADDR & HW_REGS_MASK));
    Hex23 = 		(unsigned int *) (virtual_base + (HEX2_3_PADDR & HW_REGS_MASK));
    Hex45 = 		(unsigned int *) (virtual_base + (HEX4_5_PADDR & HW_REGS_MASK));
}

static void graphics_bridge_init(unsigned int *virtual_base) {
    GraphicsCommandReg =          (virtual_base + (GraphicsCommandReg & HW_REGS_MASK));
    GraphicsStatusReg =           (virtual_base + (GraphicsStatusReg & HW_REGS_MASK));
    GraphicsX1Reg = 	          (virtual_base + (GraphicsX1Reg & HW_REGS_MASK));
    GraphicsY1Reg = 	          (virtual_base + (GraphicsY1Reg & HW_REGS_MASK));
    GraphicsX2Reg = 	          (virtual_base + (GraphicsX2Reg & HW_REGS_MASK));
    GraphicsY2Reg = 	          (virtual_base + (GraphicsY2Reg & HW_REGS_MASK));
    GraphicsColourReg =           (virtual_base + (GraphicsColourReg & HW_REGS_MASK));
    GraphicsBackGroundColourReg = (virtual_base + (GraphicsBackGroundColourReg & HW_REGS_MASK));
}

static void gps_bridge_init(unsigned int *virtual_base) {
    RS232_ReceiverFifo = 				(virtual_base + (RS232_ReceiverFifo & HW_REGS_MASK));
    RS232_TransmitterFifo = 			(virtual_base + (RS232_TransmitterFifo & HW_REGS_MASK));
    RS232_InterruptEnableReg = 			(virtual_base + (RS232_InterruptEnableReg & HW_REGS_MASK));
    RS232_InterruptIdentificationReg = 	(virtual_base + (RS232_InterruptIdentificationReg & HW_REGS_MASK));
    RS232_FifoControlReg = 				(virtual_base + (RS232_FifoControlReg & HW_REGS_MASK));
    RS232_LineControlReg = 				(virtual_base + (RS232_LineControlReg & HW_REGS_MASK));
    RS232_ModemControlReg = 			(virtual_base + (RS232_ModemControlReg & HW_REGS_MASK));
    RS232_LineStatusReg = 				(virtual_base + (RS232_LineStatusReg & HW_REGS_MASK));
    RS232_ModemStatusReg = 				(virtual_base + (RS232_ModemStatusReg & HW_REGS_MASK));
    RS232_ScratchReg = 				    (virtual_base + (RS232_ScratchReg & HW_REGS_MASK));
    RS232_DivisorLatchLSB = 			(virtual_base + (RS232_DivisorLatchLSB & HW_REGS_MASK));
    RS232_DivisorLatchMSB = 			(virtual_base + (RS232_DivisorLatchMSB & HW_REGS_MASK));
}

static void serial_bridge_init(unsigned int *virtual_base) {
    GPS_ReceiverFifo = 				  (virtual_base + (GPS_ReceiverFifo & HW_REGS_MASK))
    GPS_TransmitterFifo = 		      (virtual_base + (GPS_TransmitterFifo & HW_REGS_MASK))
    GPS_InterruptEnableReg = 	      (virtual_base + (GPS_InterruptEnableReg & HW_REGS_MASK))
    GPS_InterruptIdentificationReg =  (virtual_base + (GPS_InterruptIdentificationReg & HW_REGS_MASK))
    GPS_FifoControlReg = 			  (virtual_base + (GPS_FifoControlReg & HW_REGS_MASK))
    GPS_LineControlReg = 			  (virtual_base + (GPS_LineControlReg & HW_REGS_MASK))
    GPS_ModemControlReg = 			  (virtual_base + (GPS_ModemControlReg & HW_REGS_MASK))
    GPS_LineStatusReg = 			  (virtual_base + (GPS_LineStatusReg & HW_REGS_MASK))
    GPS_ModemStatusReg = 			  (virtual_base + (GPS_ModemStatusReg & HW_REGS_MASK))
    GPS_ScratchReg = 				  (virtual_base + (GPS_ScratchReg & HW_REGS_MASK))
    GPS_DivisorLatchLSB =             (virtual_base + (GPS_DivisorLatchLSB & HW_REGS_MASK))
    GPS_DivisorLatchMSB =             (virtual_base + (GPS_DivisorLatchMSB & HW_REGS_MASK))
}
