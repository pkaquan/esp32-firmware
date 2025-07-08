#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

class Display {
    private :
    U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

    uint8_t sda;
    uint8_t scl;

    int temp;
    int hum;


    public :
    Display (uint8_t pinSDA, uint8_t pinSCL) : u8g2(U8G2_R0,U8X8_PIN_NONE), sda(pinSDA), scl(pinSCL){}
    void initDisplay ();
    void dhtDisplay (int valueTemp, int valueHumi);
};
#endif