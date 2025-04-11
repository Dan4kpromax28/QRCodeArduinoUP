#include <HardwareSerial.h>
#include <WiFi.h>
#include "config.h"
#include "Relay.h"
#include "SupabaseC.h"
#include "OledD.h"

Relay relay;


#define QR_RX 16
#define QR_TX 17
HardwareSerial mySerial(1); 

SupabaseC* data;
OledD* dis;

void setup() {
  Serial.begin(9600);  

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  data = new SupabaseC();
  Serial.println("\nVeiksmigais pieslegums");
  mySerial.begin(9600, SERIAL_8N1, QR_RX, QR_TX);
  dis = new OledD();
}

void loop() {
  if (mySerial.available()) {  
    String qrCode = mySerial.readStringUntil('\n'); 
    qrCode.trim();
    Serial.println("QR Code: " + qrCode);
    if (data->checkCodeInDatabase(qrCode)){
      relay.onOff();
      dis->scrollText("Veiksmiga autorizacija");
    }
    else {
      dis->scrollText("Notika kluda");
    }
  }
}