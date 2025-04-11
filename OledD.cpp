#include "OledD.h"


OledD::OledD() : display(WIDTH, HEIGHT, &Wire, RESET) { 

  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    for(;;);
  } 
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0,28);
  display.setTextWrap(false);
  display.setTextColor(WHITE);

}

void OledD::printText(const String& text) {
  display.println(text);
  display.display();
  delay(1000);
  display.clearDisplay();
}

void OledD::scrollText(const String& text){
  int x = WIDTH;
  int texLen = text.length() * 10;
  int texEnd = -texLen;
  while(x > texEnd){
    display.clearDisplay();            
    display.setCursor(x, 28);          
    display.print(text);               
    display.display();                 
    delay(1);
    x -= 3;
  }
  display.clearDisplay();
  display.display();
}