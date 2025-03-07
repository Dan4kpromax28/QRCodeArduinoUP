#ifndef RELAY_H
#define RELAY_H

#include <Arduino.h>

class Relay{

  private:
    const int RELAY_PIN{23};
  public:
    Relay();

    void onOff();

    void on();

    void off();
};

#endif
