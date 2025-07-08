#include "Control_Device.h"

//Initialize the DHT temperature and humidity sensor
void ControlDevice ::bginUDP (){
    client.begin();
}

//Set the GPIO pin as an output for the device
void ControlDevice ::initDevice (){
    pinMode (pinLatch,OUTPUT);
    pinMode (pinClock,OUTPUT);
    pinMode (pinData,OUTPUT);
    pinMode (pinPWM,OUTPUT);
    pinMode (pinBuzzer,OUTPUT);
}

//Control the power switching of multiple devices through a relay module
void ControlDevice ::switchDevice (byte value) {
    digitalWrite (pinLatch, LOW);
    shiftOut (pinData,pinClock,MSBFIRST,value);
    digitalWrite (pinLatch, HIGH);
}

//Control the activation state of the alarm buzzer
void ControlDevice :: buzzerDevice (int value) {
    if (value >= 1000){
        digitalWrite(pinBuzzer,HIGH);
    } else{
        digitalWrite(pinBuzzer,LOW);
    }
}

//Set up and adjust the operation of the irrigation pump motor
void ControlDevice :: pwmDevice (bool state, int hour, int minute, int time, int speed){
    client.update();
    currentHour = client.getHours();
    currentMinute = client.getMinutes();
    if (state == true && hour == currentHour  && minute == currentMinute){
        digitalWrite(pinPWM, HIGH);
        vTaskDelay(pdMS_TO_TICKS(time * 60 *1000));  
        digitalWrite(pinPWM, LOW);
    }
}
