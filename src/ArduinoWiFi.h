#if defined(__AVR_ATmega328P__)
#ifndef ARDUINOWIFI_H_
#define ARDUINOWIFI_H_

#include <Arduino.h>

#include <Stream.h>
#include "lib/crc16.h"
#include "lib/rest.h"
#include "lib/espduino.h"
#include "lib/ringbuf.h"
#include "lib/FP.h"
#include "lib/SC16IS750.h"
#include <string.h> 

class ArduinoWifiClass : public WifiData
{

	public:
		void begin();		
		boolean connected();
		void connect(char* , char*);

		void powerON();
		void powerOFF();

};

extern ArduinoWifiClass Wifi;

#endif

#endif /* WIFI_H_ */
