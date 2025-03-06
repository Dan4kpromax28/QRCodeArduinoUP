#include <HardwareSerial.h>

HardwareSerial mySerial(1); 

void setup() {
  Serial.begin(9600);  
  mySerial.begin(9600, SERIAL_8N1, 16, 17);  
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