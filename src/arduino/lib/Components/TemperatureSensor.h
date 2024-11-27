#ifndef __TEMPERATURESENSOR__
#define __TEMPERATURESENSOR__

class TemperatureSensor {
private:
    int pin;           // Pin a cui è collegato il sensore
    float maxTemp;     // Soglia massima di temperatura
    unsigned long maxTime; // Tempo massimo consentito sopra la soglia
    unsigned long startTime; // Tempo iniziale sopra la soglia

public:
    TemperatureSensor(int pin, float maxTemp, unsigned long maxTime);
    void init();                 // Configura il sensore
    float getTemperature();      // Rileva la temperatura attuale
    bool isOverheated();         // Controlla se la temperatura è sopra la soglia per troppo tempo
};

#endif