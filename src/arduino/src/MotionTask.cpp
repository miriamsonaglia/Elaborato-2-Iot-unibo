#include "../lib/Tasks/MotionTask.h"
#include <Arduino.h>

#define SECONDS_TO_MILLS(x) ((x)*1000)

MotionTask::MotionTask(int pin,int maxInactiveTime){
    sensor_pin = pin;
    this->maxInactiveTime = SECONDS_TO_MILLS(maxInactiveTime);
}

void MotionTask::init(int period){
    Task::init(period);
    sensor = new MotionSensor(sensor_pin);
    sleep_mode_counter = 0;
    status = MOVING;
    errorControll = 0;
}

void MotionTask::tick() {
        if(openDoor || closeDoor){
            if(status!=MOVING){
                sleep_mode = 0;
                sleep_mode_counter = 0;
                status = MOVING;
            }
        }else if(sensor->movementDetected()){
            sleep_mode = 0;
            sleep_mode_counter = 0;
            status = MOVING;
        }
        else
        {
            if(status == MOVING){
                status = PENDING_SLEEP;
                sleep_mode_counter = millis();
            }
            else if(status==PENDING_SLEEP){
                if(millis()-sleep_mode_counter>=maxInactiveTime){
                    status = SLEEP;
                    sleep_mode = 1;
                }
            }
        }
}