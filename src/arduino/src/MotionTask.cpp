#include "../lib/Tasks/MotionTask.h"

#define MAX_NO_MOVEMENT_BEFORE_SLEEP 20



MotionTask::MotionTask(int pin){
    sensor_pin = pin;
}

void MotionTask::init(int period){
    Task::init(period);
    sensor = new MotionSensor(sensor_pin);
    sleep_mode_counter = 0;
}

void MotionTask::tick(){
    if(sensor->movementDetected()){
        sleep_mode = 0;
        sleep_mode_counter = 0;
        status = MOVING;
    }
    else{
        if(status == MOVING){
            status = PENDING_SLEEP;
            sleep_mode_counter = 0;
        }
        else if(status==PENDING_SLEEP){
            sleep_mode_counter++;
            if(sleep_mode_counter>=MAX_NO_MOVEMENT_BEFORE_SLEEP){
                status = SLEEP;
                sleep_mode = 1;
            }
        }
    }
}