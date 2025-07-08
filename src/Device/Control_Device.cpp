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
    float voltage = value * 3.3 / 4095.0;
    Serial.print (voltage);
    if (voltage == 0.00){
        digitalWrite(pinBuzzer, HIGH);
    } else  if (voltage > 0){
        digitalWrite(pinBuzzer,LOW);
    }
}

void ControlDevice :: pwmDevice (bool state, int hour, int minute, int time, int speed){
    client.update();
    currentHour = client.getHours();
    currentMinute = client.getMinutes();
    Serial.println (currentHour);
    Serial.println (currentMinute);
    Serial.println ("Trang thai bom");
    Serial.println (state);
    Serial.println (hour);
    Serial.println (minute);
    Serial.println (time);
    Serial.println (speed);
    if (state == true && hour == currentHour  && minute == currentMinute){
        digitalWrite(pinPWM, HIGH);
        vTaskDelay(pdMS_TO_TICKS(time * 60 *1000));  
        digitalWrite(pinPWM, LOW);
    } else {
    }
}