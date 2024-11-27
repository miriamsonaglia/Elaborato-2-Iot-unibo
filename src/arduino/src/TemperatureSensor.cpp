#include "TemperatureSensor.h"
#include <Arduino.h>

#define CONVERT_FOR_V5(x) ((((x) * (5.0 / 1024.0)-0.5))*100)

TemperatureSensor::TemperatureSensor(int pin, float maxTemp){
    this->pin = pin;
    this->maxTemp = maxTemp;
}

void TemperatureSensor::init() {
    pinMode(pin, INPUT);
}

float TemperatureSensor::getTemperature() {
    // Lettura analogica e conversione in °C (per esempio con LM35)
    int analogValue = analogRead(pin);
    float temperature = CONVERT_FOR_V5(analogValue); // Conversione
    return temperature;
}

bool TemperatureSensor::isOverheated() {
    float currentTemp = getTemperature();
    return currentTemp > maxTemp;
}