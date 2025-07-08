#include "Display.h"

void Display ::initDisplay (){
    Wire.begin (sda,scl);
    u8g2.begin();
    u8g2.enableUTF8Print();
}


void Display ::dhtDisplay (int valueTemp, int valueHumi){
  char buf1[20];
  char buf2[20];

  snprintf(buf1, sizeof(buf1), "Nhiet do : %d C", valueTemp);
  snprintf(buf2, sizeof(buf2), "Do am   : %d %%", valueHumi);

  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_7x14B_tf);

  uint8_t w1 = u8g2.getStrWidth(buf1);
  uint8_t w2 = u8g2.getStrWidth(buf2);

  u8g2.drawStr((128 - w1) / 2, 24, buf1);  // y = 24 px
  u8g2.drawStr((128 - w2) / 2, 48, buf2);  // y = 48 px

  u8g2.sendBuffer();
}