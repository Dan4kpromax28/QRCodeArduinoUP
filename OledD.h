#ifndef OLEDD_H
#define OLEDD_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>


class OledD {
  private:

    static const int WIDTH{128};
    static const int HEIGHT{64};
    static const int RESET{-1};
    static const int ADDRESS{0x3D}; 

    Adafruit_SSD1306 display; 

  public:

    OledD();

    void printText(const String& text);

    void scrollText(const String& text);
};

#endif




