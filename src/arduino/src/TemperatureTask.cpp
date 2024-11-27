#include "TemperatureTask.h"
#include <Arduino.h>

TemperatureTask::TemperatureTask(TemperatureSensor& tempSensor, void (*onOverheatCallback)())
    : tempSensor(tempSensor), onOverheatCallback(onOverheatCallback) {}

void TemperatureTask::run() {
    if (tempSensor.isOverheated()) {
        Serial.println("Temperature threshold exceeded!");
        onOverheatCallback(); // Chiama la funzione di callback
    }
}