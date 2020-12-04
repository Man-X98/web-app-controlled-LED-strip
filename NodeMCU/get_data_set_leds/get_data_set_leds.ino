#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

/*
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

//PinOut:
//Pin 2: D4 --> Red in WebApp
//Pin 0: D3 --> Green in WebApp
//Pin 4: D2 --> Blue in WebApp

const char* ssid = "ADD WIFI SSID HERE";
const char* password = "ADD WIFI PASSWORD HERE";

//Your Domain name with URL path or IP address with path
String serverIP = "http://192.168.0.20"; //Replace IP with IP of your raspberry
String serverName = serverIP+":80/get_values";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

void setup() {
  //Set all PWM Pins dutycyles to 0 (--> turn leds off)
  analogWrite(2, 0);
  analogWrite(0, 0);
  analogWrite(4, 0);
        
  Serial.begin(9600); 

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}



void loop() {
  //Send an HTTP POST request every 10 minutes
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;
      String serverPath = serverName;
      http.begin(serverPath.c_str());
      // Send HTTP GET request
      int httpResponseCode = http.GET();
      if (httpResponseCode>0) {        
        String payload = http.getString();
        //Split string and set PWM LEDs accordingly:        
        int Values[3];
        int i=0;
        int startNum = 0;
        int counter=0;
        while (i<payload.length()){
          if (payload.charAt(i)==','){
            Values[counter]=payload.substring(startNum, i).toInt();
            startNum=i+1;
            counter = counter+1;
          }
          else if (i==(payload.length()-1)){
            Values[counter]=payload.substring(startNum, i+1).toInt();
          }
          i=i+1;
        }
        //Set LEDs accordingly to recieved values:
        analogWrite(2, Values[0]);
        analogWrite(0, Values[1]);
        analogWrite(4, Values[2]);          
      }
      else {
        Serial.print("Error code: ");
        
      }
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
