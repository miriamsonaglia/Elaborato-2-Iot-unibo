#include "TemperatureSensor.h"
#include <Arduino.h>

TemperatureSensor::TemperatureSensor(int pin, float maxTemp, unsigned long maxTime)
    : pin(pin), maxTemp(maxTemp), maxTime(maxTime), startTime(0) {}

void TemperatureSensor::init() {
    pinMode(pin, INPUT);
}

float TemperatureSensor::getTemperature() {
    // Lettura analogica e conversione in °C (per esempio con LM35)
    int analogValue = analogRead(pin);
    float temperature = analogValue * (5.0 / 1023.0) * 100.0; // Conversione
    return temperature;
}

bool TemperatureSensor::isOverheated() {
    float currentTemp = getTemperature();
    
    if (currentTemp > maxTemp) {
        if (startTime == 0) {
            startTime = millis(); // Inizia a contare il tempo sopra la soglia
        }
        return (millis() - startTime) >= maxTime;
    } else {
        startTime = 0; // Resetta il timer quando la temperatura scende sotto la soglia
        return false;
    }
}