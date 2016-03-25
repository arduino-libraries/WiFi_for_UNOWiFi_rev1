/*

http://labs.arduino.org/RestServer+and+RestClient

*/

#include <Wire.h>
#include <ArduinoWiFi.h>

#define SERVER_ADDR   "192.168.1.1" // change ip address with your server ip address

int buttonState = LOW; //this variable tracks the state of the button, low if not pressed, high if pressed
int ledState = -1; //this variable tracks the state of the LED, negative if off, positive if on
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

WifiData espStream;
ESP espRest(&espStream);
REST rest(&espRest);

void setup() {

  Serial.begin(9600);
  pinMode(2, INPUT);
  Wifi.begin();
  rest.begin(SERVER_ADDR);
  rest.get("/arduino/mode/13/output");
  delay(1000);
  
}
 
void loop() {
  
  //sample the state of the button - is it pressed or not?
  buttonState = digitalRead(2);

  if ( (millis() - lastDebounceTime) > debounceDelay) {
 
    //if the button has been pressed, lets toggle the LED from "off to on" or "on to off"
    if ( (buttonState == HIGH) && (ledState < 0) ) {
      
      rest.begin(SERVER_ADDR);
      rest.get("/arduino/digital/13/1");      //turn on led
      ledState = -ledState; //now the LED is on, we need to change the state
      lastDebounceTime = millis(); //set the current time
    }
    else if ( (buttonState == HIGH) && (ledState > 0) ) {
      
      rest.begin(SERVER_ADDR);
      rest.get("/arduino/digital/13/0");      //turn off led
      ledState = -ledState; //now the LED is off, we need to change the state
      lastDebounceTime = millis(); //set the current time
                     
    }
  }

 
}
