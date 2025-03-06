#ifndef RELAY_H
#define RELAY_H

class Relay{

  private:
    const int RELAY_PIN = 23;
  public:
    Relay(){
      pinMode(RELAY_PIN, OUTPUT);
      digitalWrite(RELAY_PIN, LOW);
    }

    void onOff(){
      digitalWrite(RELAY_PIN, HIGH);
      delay(500);
      digitalWrite(RELAY_PIN, LOW);
    }

    void on(){
      digitalWrite(RELAY_PIN, HIGH);
    }

    void off(){
      digitalWrite(RELAY_PIN, LOW);
    }
};

#endif
