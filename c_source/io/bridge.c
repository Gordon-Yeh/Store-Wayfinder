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
    graphics_bridge_init((unsigned int *) virtual_base);
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
    Switches = (unsigned int *) (virtual_base + (SWITCHES_PADDR & HW_REGS_MASK));
	PushButtons = (unsigned int *) (virtual_base + (PUSHBUTTONS_PADDR & HW_REGS_MASK));
	LEDs = (unsigned int *) (virtual_base + (RED_LEDS_PADDR & HW_REGS_MASK));
	Hex01 = (unsigned int *) (virtual_base + (HEX0_1_PADDR & HW_REGS_MASK));
	Hex23 = (unsigned int *) (virtual_base + (HEX2_3_PADDR & HW_REGS_MASK));
	Hex45 = (unsigned int *) (virtual_base + (HEX4_5_PADDR & HW_REGS_MASK));
}

static void graphics_bridge_init(unsigned int *virtual_base) {

}