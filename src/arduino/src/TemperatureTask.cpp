#include "TemperatureTask.h"
#include <Arduino.h>

#define MAX_TIME_HEATING 2000

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
    if(overHeat) {
        if(status!=OVERHEATING){
            if(status == STABLE) {
                startTime = millis();
                status = HEATING;
            }
            else if(millis()-startTime >= MAX_TIME_HEATING){
                tError = 1;
            }
        }
    }else{
        tError = 0;
        startTime = 0;
        status = STABLE;
    }
}