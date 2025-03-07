#ifndef OLEDD_H
#define OLEDD_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

class OledD {
  private:
    static const int WIDTH = 128;
    static const int HEIGHT = 64;
    static const int RESET = -1;
    static const int ADDRESS = 0x3D; 

    Adafruit_SSD1306 display; 

  public:
    OledD() : display(128, 64, &Wire, -1) { 
      
      if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
        for(;;);
      } 
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0,10);
      display.setTextColor(WHITE);
    }

    void printText(String text) {
      display.println(text);
      display.display();
      delay(1000);
      display.clearDisplay();
    }
};

#endif




