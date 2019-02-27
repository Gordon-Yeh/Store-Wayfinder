#ifndef BLUETOOTH_H_
#define BLUETOOTH_H_

void Init_BT(void);
int BT_TestForReceiveData(void);
int getcharBT(void);
void BTOutMessage(char* message);

#endif
