/*
Martin Kibernich - 63708
Nicolai Otto - 63790

Multiple code snippets have been borrowed from our 
teacher at: https://github.com/EbbeVang
*/

#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"

//Wifi name & password
const char * ssid = "OnePlus 7 Pro";
const char * password = "hej12345";

//initiate drone button
int inPin = 18;
int val = 0;

//Controller pins
int x = 35;
int y = 34;
//int click = 32;

char cmd[256];

//UDP variable
AsyncUDP udp;

void setup() {
  Serial.begin(9600);

//Setup wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }

  //Instantiate controller pinModes
  pinMode(inPin, INPUT);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  //pinMode(click, INPUT_PULLUP);
}

//Send message function with receiving IP and port specified
void sendMessage(String msg){
  udp.writeTo((const uint8_t *)msg.c_str(), msg.length(), IPAddress(192, 168, 43, 205), 41516);
  Serial.println(msg); 
}

void loop() {
 
//Init button pressed
  if (digitalRead(inPin) == HIGH) {
    sendMessage("Init 10 10");
  }

  //Controls for up, down, left & right
  else if(analogRead(x) > 3200){
    sendMessage("UP");
  } 
  else if (analogRead(x) < 500) {
    sendMessage("DOWN");
  }
  else if (analogRead(y) > 3200){
    sendMessage("RIGHT");
  }
  else if (analogRead(y) < 500){
    sendMessage("LEFT");
  }
  

/*Test print in console
Serial.print("X: ");
Serial.println(analogRead(x));
Serial.print("Y: ");
Serial.println(analogRead(y));
Serial.print("\n\n");
*/ 
delay(300);
}
