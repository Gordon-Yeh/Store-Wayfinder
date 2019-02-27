#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "tests.h"

void test_bt1() {
    char * respond;
    bt_send_message("p,");
    int result = bt_receive_message(&respond);
    printf("test_bt1: respond: %s\n", respond);

    bt_send_message("c,Tools");
    result = bt_receive_message(&respond);
    printf("test_bt1: respond: %s\n", respond);

    bt_send_message("p,");    
    result = bt_receive_message(&respond);
    printf("test_bt1: respond: %s\n", respond);

    bt_send_message("c,Tools");
    result = bt_receive_message(&respond);
    printf("test_bt1: respond: %s\n", respond);

    bt_send_message("p,");
    result = bt_receive_message(&respond);
    printf("test_bt1: respond: %s\n", respond);

    bt_send_message("p,");
    result = bt_receive_message(&respond);
    printf("test_bt1: respond: %s\n", respond);

    bt_send_message("p,");
    result = bt_receive_message(&respond);
    printf("test_bt1: respond: %s\n", respond);
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
    srand(time(NULL));

    int r = rand() % 20000;
    char message[50];

    snprintf(message, 50, "This is a test #%d", r);

    WifiSendText(message);
    printf("The message \"%s\" should have been sent to the set phone number via twilio\n", message);
}
