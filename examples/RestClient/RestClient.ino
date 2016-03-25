/*

http://labs.arduino.org/RestServer+and+RestClient

*/


#include <Wire.h>
#include <Ciao.h>

#define CONNECTOR     "rest" 
#define SERVER_ADDR   "192.168.1.1" // change ip address with your server ip address

int buttonState = LOW; //this variable tracks the state of the button, low if not pressed, high if pressed
int ledState = -1; //this variable tracks the state of the LED, negative if off, positive if on
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void setup() {
  Ciao.begin();
  pinMode(2, INPUT);
  
}
 
void loop() {
 
  //sample the state of the button - is it pressed or not?
  buttonState = digitalRead(2);
 
  //filter out any noise by setting a time buffer
  if ( (millis() - lastDebounceTime) > debounceDelay) {
 
    //if the button has been pressed, lets toggle the LED from "off to on" or "on to off"
    if ( (buttonState == HIGH) && (ledState < 0) ) {
 
      CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, "/arduino/digital/13/1"); //turn LED on
      ledState = -ledState; //now the LED is on, we need to change the state
      lastDebounceTime = millis(); //set the current time
    }
    else if ( (buttonState == HIGH) && (ledState > 0) ) {
      
      CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, "/arduino/digital/13/0"); //turn LED off
      ledState = -ledState; //now the LED is off, we need to change the state
      lastDebounceTime = millis(); //set the current time
        
      if (!data.isEmpty()){
        Ciao.println( "State: " + String (data.get(1)) );
        Ciao.println( "Response: " + String (data.get(2)) );
      }
      else{ 
        Ciao.println ("Write Error");
      }
              
    }
  }

 
}
