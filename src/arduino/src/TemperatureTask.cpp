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
        shareData.ignoreTempError = 0;
        shareData.tError = 0;
        status = STABLE;
    }

    if(overHeat && !shareData.ignoreTempError) {
            if(status == STABLE) {
                startTime = millis();
                status = HEATING;
            }
            else if(status == HEATING && (millis()-startTime >= MAX_TIME_HEATING)){
                shareData.tError = 1;
            }
    }else{
        shareData.tError = 0;
        startTime = 0;
        status = STABLE;
    }

    //update for java GUI
    shareData.temperature = measure;
}