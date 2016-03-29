#include <Wire.h>
#include <ArduinoWiFi.h>
/*
on your borwser, you type http://<IP>/arduino/webserver/ or http://<hostname>.local/arduino/webserver/

http://labs.arduino.org/WebServer

*/
void setup() {
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

  if (command == "webserver") {
    WebServer(client);
  }
}
void WebServer(WifiData client) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  
          client.println("Refresh: 20");  // refresh the page automatically every  sec
          client.println();      
          client.println("<html>");
          client.println("<head> <title>UNO WIFI Example</title> </head>");
          client.print("<body>");
          
          for (int analogChannel = 0; analogChannel < 4; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.print("<br/>"); 
          }
            
          client.print("</body>"); 
          client.println("</html>"); 
          client.print(DELIMITER); // very important to end the communication !!!          
}
