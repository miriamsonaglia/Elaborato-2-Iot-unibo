#ifndef __TEMPERATURETASK__
#define __TEMPERATURETASK__

#include "TemperatureSensor.h"

class TemperatureTask {
private:
    TemperatureSensor& tempSensor; // Riferimento al sensore
    void (*onOverheatCallback)();  // Funzione chiamata quando si supera la temperatura massima

public:
    TemperatureTask(TemperatureSensor& tempSensor, void (*onOverheatCallback)());
    void run(); // Esegue il monitoraggio della temperatura
};

#endif