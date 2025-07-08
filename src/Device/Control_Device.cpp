#include "Control_Device.h"

void ControlDevice ::bginUDP (){
    client.begin();
}

void ControlDevice ::initDevice (){
    pinMode (pinLatch,OUTPUT);
    pinMode (pinClock,OUTPUT);
    pinMode (pinData,OUTPUT);
    pinMode (pinPWM,OUTPUT);
    pinMode (pinBuzzer,OUTPUT);
}
void ControlDevice ::switchDevice (byte value) {
    digitalWrite (pinLatch, LOW);
    shiftOut (pinData,pinClock,MSBFIRST,value);
    digitalWrite (pinLatch, HIGH);
}
void ControlDevice :: buzzerDevice (int value) {
    if (value >= 1000){
        digitalWrite(pinBuzzer,HIGH);
    } else{
        digitalWrite(pinBuzzer,LOW);
    }
}

void ControlDevice :: pwmDevice (bool state, int hour, int minute, int time, int speed){
    client.update();
    currentHour = client.getHours();
    currentMinute = client.getMinutes();
    if (state == true && hour == currentHour  && minute == currentMinute){
        digitalWrite(pinPWM, HIGH);
        vTaskDelay(pdMS_TO_TICKS(time * 60 *1000));  
        digitalWrite(pinPWM, LOW);
    } else {
    }
}
