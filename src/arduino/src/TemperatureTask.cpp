#include "TemperatureTask.h"
#include <Arduino.h>
#include "../lib/Scheduling/SharableData.h"

#define MAX_TIME_HEATING 2000

extern struct SharableData shareData;
extern int ignoreTempError;

TemperatureTask::TemperatureTask(int pin,int maxTemp){
    tempSensor = new TemperatureSensor(pin,maxTemp);
}

void TemperatureTask::init(int period) {
    Task::init(period);
    startTime = 0;
    status = STABLE;
}

void TemperatureTask::tick(){
    int overHeat = tempSensor->isOverheated();
    double measure = tempSensor->getTemperature();

    if(!overHeat){
        ignoreTempError = 0;
        tError = 0;
        status = STABLE;
    }

    if(overHeat && !ignoreTempError) {
            if(status == STABLE) {
                startTime = millis();
                status = HEATING;
            }
            else if(status == HEATING && (millis()-startTime >= MAX_TIME_HEATING)){
                tError = 1;
            }
    }else{
        tError = 0;
        startTime = 0;
        status = STABLE;
    }

    //update for java GUI
    shareData.temperature = measure;
}