#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../GPS/GPS.h"
#include "../Graphics/gui.h"
#include "../Wifi/Wifi.h"
#include "../Bluetooth/bluetooth.h"
#include "../io/bridge.h"

void test_bt1() {
    char * respond;
    bt_send_message("p,");
    int result = bt_receive_message(&respond);
    printf("respond: %s\n", respond);

    bt_send_message("c,Tools");
    result = bt_receive_message(&respond);
    printf("respond: %s\n", respond);

    bt_send_message("p,");    
    result = bt_receive_message(&respond);
    printf("respond: %s\n", respond);

    bt_send_message("c,Tools");
    result = bt_receive_message(&respond);
    printf("respond: %s\n", respond);

    bt_send_message("p,");
    result = bt_receive_message(&respond);
    printf("respond: %s\n", respond);

    bt_send_message("p,");
    result = bt_receive_message(&respond);
    printf("respond: %s\n", respond);

    bt_send_message("p,");
    result = bt_receive_message(&respond);
    printf("respond: %s\n", respond);
}

void test_gps() {
    gps_point * curr = getPoint();
    printf("current point: [ %f, %f ]\n",  curr->lon, curr->lat);

    free(curr);
}

void test_screen() {
    printf("The GUI should appear on the screen\n");
    gui_start();
}

void test_wifi() {
    int r = rand() % 20000;
    char message[50];

    snprintf(message, 50, "This is a test #%d", r);

    WifiSendText(message);
    printf("The message \"%s\" should have been sent to the set phone number via twilio\n", message);
}

void sys_init() {
    srand(time(NULL));
    bridge_init();  
    Init_BT();
    Init_Wifi();
    Init_GPS();
}

int main(int argc, char **argv) {
	if (argc < 2) {
		printf("[main] Error: must include either [ screen / wifi / gps / bt ] as an argument\n");
		return 1;
	}

    sys_init();

	if (strcmp(argv[1], "wifi") == 0) {
		test_wifi();
	} else if (strcmp(argv[1], "screen") == 0) {
		test_screen();
	} else if (strcmp(argv[1], "gps") == 0) {
        test_gps();
    } else if (strcmp(argv[1], "bt") == 0) {
        test_bt1();
    } else {
		printf("[main] Error: invalid argument\n");
	}
}
