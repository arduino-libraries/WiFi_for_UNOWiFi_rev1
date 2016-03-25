/*
****************************************************************************
* Copyright (c) 2015 Arduino srl. All right reserved.
*
* File : ArduinoWiFi.cpp
* Date : 2016/03/24
* Revision : 0.0.1 $
* Author: adriano[at]arduino[dot]org
*
****************************************************************************
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#include <ArduinoWiFi.h>
#include <stdarg.h>
#include <stdio.h>

#if defined(__AVR_ATmega328P__)

boolean wifiConnected = false;

WifiData espSerial;
ESP esp(&espSerial);
//REST rest(&esp);

void wifiCb(void* response)
{
	uint32_t status;
	RESPONSE res(response);

	if(res.getArgc() == 1) {
		res.popArgs((uint8_t*)&status, 4);
		if(status == STATION_GOT_IP){
			espSerial.println("DBG: Internet Connected");
			wifiConnected = true;
		}
		else {
			wifiConnected = false;
		}
	}
}

void ArduinoWifiClass::powerON(){ 		
}
void ArduinoWifiClass::powerOFF(){ 		
}

void ArduinoWifiClass::connect(char* ssid,char* pwd){
	esp.wifiConnect(ssid, pwd);
}
boolean ArduinoWifiClass::connected(){
	return wifiConnected;
}

void WifiBegin(short isCiao) {
	espSerial.begin(9600);
	if(espSerial.ping()!=1) {
		espSerial.println("DBG: esp not found");
		while(1);
	}
	else {
		//espSerial.println("device found");
	}
	//put GPIO control here !!!
	esp.enable();
	delay(1000);
	esp.reset();
	delay(1000);
	while(!esp.ready());
	if (isCiao == 0)
		esp.wifiCb.attach(&wifiCb);

	espSerial.println("\nDBG: UnoWiFi Start");
}
void ArduinoWifiClass::begin() {
	WifiBegin(0);	
}

ArduinoWifiClass Wifi;

#endif