#include <HardwareSerial.h>
#include <WiFi.h>
#include "config.h"

#define QR_RX 16
#define QR_TX 17
HardwareSerial mySerial(1); 

void setup() {
  Serial.begin(9600);  

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);

  }
  Serial.print("\nVeiksmigais pieslegums");

  mySerial.begin(9600, SERIAL_8N1, QR_RX, QR_TX);  
}

void loop() {
  if (mySerial.available()) {  
    while (mySerial.available()) {  
      char input = mySerial.read();  
      Serial.print(input);  
      delay(5);
    }
    Serial.println();
  }
}