
#include "Relay.h"

Relay::Relay(){
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
}

void Relay::onOff(){
  digitalWrite(RELAY_PIN, HIGH);
  delay(500);
  digitalWrite(RELAY_PIN, LOW);
}
void Relay::on(){
  digitalWrite(RELAY_PIN, HIGH);
}

void Relay::off(){
  digitalWrite(RELAY_PIN, LOW);
}