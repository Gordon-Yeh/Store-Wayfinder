/*
 * Wifi.c
 *
 *  Created on: Jan 24, 2019
 *      Author: Nathalie
 */

#ifndef WIFI_H
#define WIFI_H

#define Wifi_ReceiverFifo (*(volatile unsigned char *)(0xFF210240))
#define Wifi_TransmitterFifo (*(volatile unsigned char *)(0xFF210240))
#define Wifi_InterruptEnableReg (*(volatile unsigned char *)(0xFF210242))
#define Wifi_InterruptIdentificationReg (*(volatile unsigned char *)(0xFF210244))
#define Wifi_FifoControlReg (*(volatile unsigned char *)(0xFF210244))
#define Wifi_LineControlReg (*(volatile unsigned char *)(0xFF210246))
#define Wifi_ModemControlReg (*(volatile unsigned char *)(0xFF210248))
#define Wifi_LineStatusReg (*(volatile unsigned char *)(0xFF21024A))
#define Wifi_ModemStatusReg (*(volatile unsigned char *)(0xFF21024C))
#define Wifi_ScratchReg (*(volatile unsigned char *)(0xFF21024E))
#define Wifi_DivisorLatchLSB (*(volatile unsigned char *)(0xFF210240))
#define Wifi_DivisorLatchMSB (*(volatile unsigned char *)(0xFF210242))

void Init_Wifi(void);

char putcharWifi(char input);

unsigned char getcharWifi(void);

int WifiTestForReceivedData(void);

void saveAndPrintBuffer(void);

void WifiFlush(void);

void delay(double number_of_seconds);

void WifiSendLine(char* message);

int testWifi(void);

#endif // WIFI_H