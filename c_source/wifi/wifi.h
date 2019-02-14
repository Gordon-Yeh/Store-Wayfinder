/*
 * wifi.h
 *
 *  Created on: Feb 14, 2019
 *      Author: Nathalie
 */

#ifndef WIFI_H_
#define WIFI_H_

/*
 * initializes wifi module and connects to wifi
 */
void Init_Wifi(void);

/*
 * sends text through twillio containing the content to the char* message
 */
void WifiSendText(char* message);


#endif /* WIFI_H_ */
