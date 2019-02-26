#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../GPS/GPS.h"
#include "../Graphics/gui.h"
#include "../Wifi/Wifi.h"
#include "../io/bridge.h"

void test_gps() {
    Init_GPS();

    gps_point * curr = getPoint();
    printf("current point: [ %f, %f ]\n",  curr->lon, curr->lat);

    free(curr);
}

void test_screen() {
    printf("The GUI should appear on the screen\n");
    gui_start();
}

void test_wifi() {
    Init_Wifi();

    int r = rand() % 20000;
    char message[50];

    snprintf(message, 50, "This is a test #%d", r);

    WifiSendText(message);
    printf("The message \"%s\" should have been sent to the set phone number via twilio\n", message);
}

void sys_init() {
    srand(time(NULL));
    bridge_init();  
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("[main] Error: must include either [ screen / wifi / gps ] as an argument\n");
		return 1;
	}

    sys_init();

	if (strcmp(argv[1], "wifi") == 0) {
		test_wifi();
	} else if (strcmp(argv[1], "screen") == 0) {
		test_screen();
	} else if (strcmp(argv[1], "gps") == 0) {
        test_gps();
    } else {
		printf("[main] Error: invalid argument\n");
	}
}
