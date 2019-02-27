#include "../Bluetooth/bluetooth.h"

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

int main(void)
{
    Init_BT();
    test_bt1();
    return 0;
}
