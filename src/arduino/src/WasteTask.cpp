#include "WasteTask.h"
#include <Arduino.h>

WasteTask::WasteTask(SonarWaste& wasteSensor, void (*onFullCallback)())
    : sonarWaste(wasteSensor), onFullCallback(onFullCallback) {}

void WasteTask::run() {
    // Controlla se il contenitore è pieno
    if (sonarWaste.isFull()) {
        Serial.println("Container is full!");
        onFullCallback();  // Chiama la funzione di callback
    }
}