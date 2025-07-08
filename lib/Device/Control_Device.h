#ifndef CONTROLDEVICE_H
#define CONTROLDEVICE_H

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

class ControlDevice {
    private :
    WiFiUDP udp;
    NTPClient client;

    uint8_t pinLatch;
    uint8_t pinClock;
    uint8_t pinData;
    uint8_t pinPWM;
    uint8_t pinBuzzer;

    int currentHour ;
    int currentMinute;

    unsigned long loadMillis = 0;
    bool isState = false;
    uint8_t isSwitch = 0;
    public : 
    ControlDevice (uint8_t latch,uint8_t clock, uint8_t data, uint8_t pwm, uint8_t buzzer) 
    : client (udp,"pool.ntp.org", 7 * 3600,60000),pinLatch(latch),pinClock (clock),pinData(data),pinPWM(pwm), pinBuzzer (buzzer){
    };
    void initDevice ();
    void bginUDP ();
    void switchDevice (byte value);
    void pwmDevice (bool state, int hour, int minute, int time, int speed);
    void buzzerDevice (int value);
};
#endif