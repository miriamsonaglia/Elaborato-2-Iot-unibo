#include "TemperatureTask.h"
#include <Arduino.h>
#include "../lib/Scheduling/SharableData.h"

#define MAX_TIME_HEATING 2000

extern struct SharableData shareData;

TemperatureTask::TemperatureTask(int pin,int maxTemp){
    tempSensor = new TemperatureSensor(pin,maxTemp);
}

void TemperatureTask::init(int period) {
    Task::init(period);
    startTime = 0;
    status = STABLE;
    Serial.begin(9600);
}

void TemperatureTask::tick(){
    int overHeat = tempSensor->isOverheated();
    double measure = tempSensor->getTemperature();
    if(overHeat) {
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