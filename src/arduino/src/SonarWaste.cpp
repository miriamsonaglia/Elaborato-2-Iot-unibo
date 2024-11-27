#include "SonarWaste.h"
#include <Arduino.h>

SonarWaste::SonarWaste(int trigPin, int echoPin, float threshold)
{
    this->echoPin = echoPin;
    this->trigPin = trigPin;
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
    this->threshold = threshold;
}

double SonarWaste::getDistance() {
    // Genera un impulso per il sensore a ultrasuoni
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(20);
    digitalWrite(trigPin, LOW);

    // Misura il tempo di ritorno
    long duration = pulseIn(echoPin, HIGH);

    // Calcola la distanza in centimetri
    double distance = duration * 0.0343 / 2.0;  // Velocità del suono: 343 m/s
    return distance;
}

bool SonarWaste::isFull() {
    // Controlla se la distanza rilevata è inferiore alla soglia
    return getDistance() < threshold;
}