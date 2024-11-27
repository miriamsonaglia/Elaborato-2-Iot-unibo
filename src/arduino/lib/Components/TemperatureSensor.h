#ifndef __TEMPERATURESENSOR__
#define __TEMPERATURESENSOR__

class TemperatureSensor {
private:
    int pin;           // Pin a cui è collegato il sensore
    double maxTemp;     // Soglia massima di temperatura
public:
    TemperatureSensor(int pin, float maxTemp);
    void init();                 // Configura il sensore
    float getTemperature();      // Rileva la temperatura attuale
    bool isOverheated();         // Controlla se la temperatura è sopra la soglia per troppo tempo
};

#endif