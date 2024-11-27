#include "WasteTask.h"
#include <Arduino.h>

#define MARGINAL_ERROR 2
#define MAX_ALLOWED_SUCCESSIVE_LOW_READINGS 7

WasteTask::WasteTask(int trigPin,int echoPin,double maxHeight){
    this->sonarSensor = new SonarWaste(trigPin,echoPin,maxHeight);
}

void WasteTask::init(int period){
    Task::init(period);
    last_measurment = -1.0;
    status = OPENABLE;
    Serial.begin(9600);
    successive_low_readings = 0;
}

void WasteTask::tick(){
    double measure = sonarSensor->getDistance();
    Serial.println(measure);

    if(last_measurment!=-1.0){
        //if lower height found,bin is being emptied,do not run errors
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
}