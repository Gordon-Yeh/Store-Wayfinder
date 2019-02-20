#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>

#include "bridge.h"

static int dev_mem_fd;
static void *virtual_base;

static void onboard_bridge_init();
static void graphics_bridge_init();
static void gps_bridge_init();
static void serial_bridge_init();
static void wifi_bridge_init();

void bridge_init() {
    // Open memory as if it were a device for read and write access
    dev_mem_fd = open("/dev/mem", (O_RDWR | O_SYNC));
    if (dev_mem_fd == -1) {
        printf("ERROR: could not open \"/dev/mem\"...\n");
        return NULL;
    }

    // map 2Mbyte of memory starting at 0xFF200000 to user space
    virtual_base = mmap(NULL, HW_REGS_SPAN, (PROT_READ|PROT_WRITE), MAP_SHARED, dev_mem_fd, HW_REGS_BASE);

    if (virtual_base == MAP_FAILED) {
        printf("ERROR: mmap() failed...\n");
        close(dev_mem_fd);
        return NULL;
    }

    // initalize perherials mappings
    onboard_bridge_init();
    graphics_bridge_init();
    gps_bridge_init();
    serial_bridge_init();
    wifi_bridge_init();
}

void bridge_close() {
    if (munmap(virtual_base, HW_REGS_SPAN) != 0) {
        printf("bridge_close: munmap() failed...\n");
    }

    if (dev_mem_fd >= 0) {
        close(dev_mem_fd);
        dev_mem_fd = -1;
    }
}

static void onboard_bridge_init() {
    Switches = 	    (unsigned int *) (virtual_base + (SWITCHES_PADDR & HW_REGS_MASK));
    PushButtons = 	(unsigned int *) (virtual_base + (PUSHBUTTONS_PADDR & HW_REGS_MASK));
    LEDs = 			(unsigned int *) (virtual_base + (RED_LEDS_PADDR & HW_REGS_MASK));
    Hex01 = 		(unsigned int *) (virtual_base + (HEX0_1_PADDR & HW_REGS_MASK));
    Hex23 = 		(unsigned int *) (virtual_base + (HEX2_3_PADDR & HW_REGS_MASK));
    Hex45 = 		(unsigned int *) (virtual_base + (HEX4_5_PADDR & HW_REGS_MASK));
}

static void graphics_bridge_init() {
    GraphicsCommandReg =          (unsigned int *) (virtual_base + (GraphicsCommandReg_PADDR & HW_REGS_MASK));
    GraphicsStatusReg =           (unsigned int *) (virtual_base + (GraphicsStatusReg_PADDR & HW_REGS_MASK));
    GraphicsX1Reg = 	          (unsigned int *) (virtual_base + (GraphicsX1Reg_PADDR & HW_REGS_MASK));
    GraphicsY1Reg = 	          (unsigned int *) (virtual_base + (GraphicsY1Reg_PADDR & HW_REGS_MASK));
    GraphicsX2Reg = 	          (unsigned int *) (virtual_base + (GraphicsX2Reg_PADDR & HW_REGS_MASK));
    GraphicsY2Reg = 	          (unsigned int *) (virtual_base + (GraphicsY2Reg_PADDR & HW_REGS_MASK));
    GraphicsColourReg =           (unsigned int *) (virtual_base + (GraphicsColourReg_PADDR & HW_REGS_MASK));
    GraphicsBackGroundColourReg = (unsigned int *) (virtual_base + (GraphicsBackGroundColourReg_PADDR & HW_REGS_MASK));
}

static void gps_bridge_init() {
    RS232_ReceiverFifo = 				(unsigned int *) (virtual_base + (RS232_ReceiverFifo_PADDR & HW_REGS_MASK));
    RS232_TransmitterFifo = 			(unsigned int *) (virtual_base + (RS232_TransmitterFifo_PADDR & HW_REGS_MASK));
    RS232_InterruptEnableReg = 			(unsigned int *) (virtual_base + (RS232_InterruptEnableReg_PADDR & HW_REGS_MASK));
    RS232_InterruptIdentificationReg = 	(unsigned int *) (virtual_base + (RS232_InterruptIdentificationReg_PADDR & HW_REGS_MASK));
    RS232_FifoControlReg = 				(unsigned int *) (virtual_base + (RS232_FifoControlReg_PADDR & HW_REGS_MASK));
    RS232_LineControlReg = 				(unsigned int *) (virtual_base + (RS232_LineControlReg_PADDR & HW_REGS_MASK));
    RS232_ModemControlReg = 			(unsigned int *) (virtual_base + (RS232_ModemControlReg_PADDR & HW_REGS_MASK));
    RS232_LineStatusReg = 				(unsigned int *) (virtual_base + (RS232_LineStatusReg_PADDR & HW_REGS_MASK));
    RS232_ModemStatusReg = 				(unsigned int *) (virtual_base + (RS232_ModemStatusReg_PADDR & HW_REGS_MASK));
    RS232_ScratchReg = 				    (unsigned int *) (virtual_base + (RS232_ScratchReg_PADDR & HW_REGS_MASK));
    RS232_DivisorLatchLSB = 			(unsigned int *) (virtual_base + (RS232_DivisorLatchLSB_PADDR & HW_REGS_MASK));
    RS232_DivisorLatchMSB = 			(unsigned int *) (virtual_base + (RS232_DivisorLatchMSB_PADDR & HW_REGS_MASK));
}

static void serial_bridge_init() {
    GPS_ReceiverFifo = 				  (unsigned int *) (virtual_base + (GPS_ReceiverFifo_PADDR & HW_REGS_MASK));
    GPS_TransmitterFifo = 		      (unsigned int *) (virtual_base + (GPS_TransmitterFifo_PADDR & HW_REGS_MASK));
    GPS_InterruptEnableReg = 	      (unsigned int *) (virtual_base + (GPS_InterruptEnableReg_PADDR & HW_REGS_MASK));
    GPS_InterruptIdentificationReg =  (unsigned int *) (virtual_base + (GPS_InterruptIdentificationReg_PADDR & HW_REGS_MASK));
    GPS_FifoControlReg = 			  (unsigned int *) (virtual_base + (GPS_FifoControlReg_PADDR & HW_REGS_MASK));
    GPS_LineControlReg = 			  (unsigned int *) (virtual_base + (GPS_LineControlReg_PADDR & HW_REGS_MASK));
    GPS_ModemControlReg = 			  (unsigned int *) (virtual_base + (GPS_ModemControlReg_PADDR & HW_REGS_MASK));
    GPS_LineStatusReg = 			  (unsigned int *) (virtual_base + (GPS_LineStatusReg_PADDR & HW_REGS_MASK));
    GPS_ModemStatusReg = 			  (unsigned int *) (virtual_base + (GPS_ModemStatusReg_PADDR & HW_REGS_MASK));
    GPS_ScratchReg = 				  (unsigned int *) (virtual_base + (GPS_ScratchReg_PADDR & HW_REGS_MASK));
    GPS_DivisorLatchLSB =             (unsigned int *) (virtual_base + (GPS_DivisorLatchLSB_PADDR & HW_REGS_MASK));
    GPS_DivisorLatchMSB =             (unsigned int *) (virtual_base + (GPS_DivisorLatchMSB_PADDR & HW_REGS_MASK));
}

static void wifi_bridge_init() {
    Wifi_ReceiverFifo =                 (unsigned int *) (virtual_base + (Wifi_ReceiverFifo_PADDR & HW_REGS_MASK));
    Wifi_TransmitterFifo =              (unsigned int *) (virtual_base + (Wifi_TransmitterFifo_PADDR & HW_REGS_MASK));
    Wifi_InterruptEnableReg =           (unsigned int *) (virtual_base + (Wifi_InterruptEnableReg_PADDR & HW_REGS_MASK));
    Wifi_InterruptIdentificationReg =   (unsigned int *) (virtual_base + (Wifi_InterruptIdentificationReg_PADDR & HW_REGS_MASK));
    Wifi_FifoControlReg =               (unsigned int *) (virtual_base + (Wifi_FifoControlReg_PADDR & HW_REGS_MASK));
    Wifi_LineControlReg =               (unsigned int *) (virtual_base + (Wifi_LineControlReg_PADDR & HW_REGS_MASK));
    Wifi_ModemControlReg =              (unsigned int *) (virtual_base + (Wifi_ModemControlReg_PADDR & HW_REGS_MASK));
    Wifi_LineStatusReg =                (unsigned int *) (virtual_base + (Wifi_LineStatusReg_PADDR & HW_REGS_MASK));
    Wifi_ModemStatusReg =               (unsigned int *) (virtual_base + (Wifi_ModemStatusReg_PADDR & HW_REGS_MASK));
    Wifi_ScratchReg =                   (unsigned int *) (virtual_base + (Wifi_ScratchReg_PADDR & HW_REGS_MASK));
    Wifi_DivisorLatchLSB =              (unsigned int *) (virtual_base + (Wifi_DivisorLatchLSB_PADDR & HW_REGS_MASK));
    Wifi_DivisorLatchMSB =              (unsigned int *) (virtual_base + (Wifi_DivisorLatchMSB_PADDR & HW_REGS_MASK));
}
