#include <Wire.h>
#include <Ciao.h>

#define CONNECTOR     "rest" 
#define SERVER_ADDR   "192.168.1.1" // change ip address with your server ip address

int buttonState; //this variable tracks the state of the button, low if not pressed, high if pressed
int ledState = HIGH; //this variable tracks the state of the LED, negative if off, positive if on
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers
String command = "/arduino/mode/13/output";
int previous_value = LOW;

void setup() {
  Ciao.begin();
  Ciao.write(CONNECTOR, SERVER_ADDR, command);
  pinMode(2, INPUT);
  
}
 
void loop() {
 
  //sample the state of the button - is it pressed or not?
  buttonState = digitalRead(2);
  
  //filter out any noise by setting a time buffer
  if ( (buttonState == HIGH) && (previous_value == LOW) && (millis() - lastDebounceTime) > debounceDelay ) {
     if (ledState == HIGH){
         command = "/arduino/digital/13/0";
         ledState = LOW;
     }
     else{
         command = "/arduino/digital/13/1";
         ledState = HIGH;
     }
     
     lastDebounceTime = millis(); //set the current time
     CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, command);  
      if (!data.isEmpty()){
        Ciao.println( "State: " + String (data.get(1)) );
        Ciao.println( "Response: " + String (data.get(2)) );
     }
     else{ 
       Ciao.println ("Write Error");
     }

  }
 
 previous_value = buttonState;
 
}
