#ifndef __WASTETASK__
#define __WASTETASK__

#include "SonarWaste.h"
#include "../lib/Tasks/Task.h"

extern int wError;

class WasteTask : public Task {
private:
    SonarWaste* sonarSensor; // Riferimento al sensore
    enum {OPENABLE,FULL} status;
    double last_measurment;
    int successive_low_readings;
public:
    WasteTask(int trigPin,int echoPin,double maxHeight);
    void init(int period);
    void tick();
};

#endif