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
    OledD() : display(WIDTH, HEIGHT, &Wire, RESET) { 
      
      if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
        for(;;);
      } 
      display.clearDisplay();
      display.setTextSize(2);
      display.setCursor(0,32);
      display.setTextWrap(false);
      display.setTextColor(WHITE);
    }

    void printText(String text) {
      display.println(text);
      display.display();
      delay(1000);
      display.clearDisplay();
    }

    void scrollText(String text){
      int x = WIDTH;
      int texLen = text.length() * 10;
      int texEnd = -texLen;
      while(x > texEnd){
        display.clearDisplay();            
        display.setCursor(x, 32);          
        display.print(text);               
        display.display();                 
        delay(1);
        x--;
        x--;
      }
      display.clearDisplay();
      display.display();
    }
};

#endif




