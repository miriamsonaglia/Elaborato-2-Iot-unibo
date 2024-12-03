#include "WasteTask.h"
#include "../lib/Scheduling/SharableData.h"
#include <Arduino.h>
#define MAX_ALLOWED_SUCCESSIVE_LOW_READINGS 7
#define MAX_FREE_HEIGHT_EXPECTED 100.0

extern struct SharableData shareData;

WasteTask::WasteTask(int trigPin,int echoPin,double maxHeight){
    this->sonarSensor = new SonarWaste(trigPin,echoPin,maxHeight);
}

void WasteTask::init(int period){
    Task::init(period);
    last_measurment = -1.0;
    status = OPENABLE;
    successive_low_readings = 0;
}

void WasteTask::tick(){
    double measure = sonarSensor->getDistance();

    if(last_measurment!=-1.0){
        if(sonarSensor->isFull()){
            successive_low_readings++;
            if(successive_low_readings>MAX_ALLOWED_SUCCESSIVE_LOW_READINGS){
                status = FULL;
                wError = 1;
            }
        }
        else
        {
            status = OPENABLE;
            wError = 0;
            successive_low_readings = 0;
        }
    }
    last_measurment = measure;
    //update fill perc.
    double capped_measure = min(last_measurment,MAX_FREE_HEIGHT_EXPECTED);
    shareData.fillPercentage = ((max(MAX_FREE_HEIGHT_EXPECTED-capped_measure,0.0))/MAX_FREE_HEIGHT_EXPECTED)*100.0;
}