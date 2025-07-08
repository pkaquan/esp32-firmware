#ifndef SENSOR_H
#define SENSOR_H

#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>

class Sensor {
    private :
    uint8_t pinGas;
    DHT    dht;
    public :
    Sensor (uint8_t pinDHT,uint8_t typeDHT, uint8_t pinMQ2) : dht (pinDHT,typeDHT), pinGas(pinMQ2){};
    void begin ();
    int dhtHumidity ();
    int dhtTemperature ();
    int mq2 (); 
};
#endif
