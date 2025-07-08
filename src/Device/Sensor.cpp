#include "Sensor.h"

void Sensor::begin (){
    dht.begin();
}

int Sensor :: dhtHumidity() {
    int value = dht.readHumidity();
    return isnan(value) ? 0 : value;
}

int Sensor :: dhtTemperature (){
    int value = dht.readTemperature();
    return isnan(value) ? 0 : value;
}

int Sensor :: mq2 (){
    int value = analogRead(pinGas);
    return isnan(value) ? 0 : value;
}
