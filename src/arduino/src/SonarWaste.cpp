#include "SonarWaste.h"
#include <Arduino.h>

SonarWaste::SonarWaste(int trigPin, int echoPin, float threshold)
    : trigPin(trigPin), echoPin(echoPin), threshold(threshold) {}

void SonarWaste::init() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float SonarWaste::getDistance() {
    // Genera un impulso per il sensore a ultrasuoni
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Misura il tempo di ritorno
    long duration = pulseIn(echoPin, HIGH);

    // Calcola la distanza in centimetri
    float distance = duration * 0.034 / 2;  // Velocità del suono: 343 m/s
    return distance;
}

bool SonarWaste::isFull() {
    // Controlla se la distanza rilevata è inferiore alla soglia
    return getDistance() < threshold;
}