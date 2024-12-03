#ifndef __TEMPERATURETASK__
#define __TEMPERATURETASK__

#include "TemperatureSensor.h"
#include "../lib/Tasks/Task.h"

class TemperatureTask: public Task {
private:
    TemperatureSensor* tempSensor; // Riferimento al sensore
    unsigned long maxTime; // Tempo massimo consentito sopra la soglia
    unsigned long startTime; // Tempo iniziale sopra la soglia
    enum {STABLE,HEATING,OVERHEATING} status;
public:
    TemperatureTask(int pin,int maxTemp);
    void tick();
    void init(int period);
};

#endif