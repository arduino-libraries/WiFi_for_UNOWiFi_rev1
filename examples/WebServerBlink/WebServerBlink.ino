#include <Wire.h>
#include <ArduinoWiFi.h>
/*
on your borwser, you type http://<IP>/arduino/webserver/ or http://<hostname>.local/arduino/webserver/

http://labs.arduino.org/WebServerBlink

*/
void setup() {
    pinMode(13,OUTPUT);
    Wifi.begin();
    Wifi.println("WebServer Server is up"); 
}
void loop() {
  
    while(Wifi.available()){
      process(Wifi);
    }
  delay(50);
}

void process(WifiData client) {
  // read the command
  String command = client.readStringUntil('/');

  // is "digital" command?
  if (command == "webserver") {
    WebServer(client);
  }
  
  if (command == "digital") {
    digitalCommand(client);
  }
}

void WebServer(WifiData client) {
  
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<html>");
          
          client.println("<head> </head>");
          client.print("<body>");
                     
          client.print("Click<input type=button onClick=\"var w=window.open('/arduino/digital/13/1','_parent');w.close();\"value='ON'>pin13 ON<br>");
          client.print("Click<input type=button onClick=\"var w=window.open('/arduino/digital/13/0','_parent');w.close();\"value='OFF'>pin13 OFF<br>");
          
          client.print("</body>");
          client.println("</html>");
          client.print(DELIMITER); // very important to end the communication !!! 
 
}

void digitalCommand(WifiData client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL
  // with a value like: "/digital/13/1"
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  }
  
  // Send feedback to client
  client.println("Status: 200 OK\n");
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" set to "));
  client.print(value);
  client.print(EOL);    //char terminator

}


