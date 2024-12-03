#include "../lib/Tasks/DoorTask.h"
#include "../lib/Scheduling/SharableData.h"
#include <Arduino.h>
#define TIME_FOR_EMPTYING 3000
#define TIME_FOR_OPENING 5000

extern SharableData shareData;

DoorTask::DoorTask(int pin){
    this->pin = pin;
}

void DoorTask::init(int period){
    Task::init(period);
    door = new Door(pin);
    status = CLOSED;
    door->close();
    emptyingTimer = 0;
}

void DoorTask::tick(){
    if(status==EMPTYING){
        if(millis()-emptyingTimer>TIME_FOR_EMPTYING){
            status = CLOSED;
            door->close();
            emptyingTimer = 0;
        }
        shareData.emptyDoor = 0;
    }
    else if(shareData.wError || shareData.tError){
        shareData.openDoor = 0;
        if(status == OPEN){
            status = CLOSED;
            door->close();
            shareData.closeDoor = 0;
        }
        else if(shareData.emptyDoor){
            if(status == CLOSED){
                door->empty();
                status = EMPTYING;
                emptyingTimer = millis();
            }
            shareData.emptyDoor = 0;
        }

    }
    else if(status == OPEN){
        shareData.emptyDoor = 0;
        if(shareData.closeDoor || (millis()-emptyingTimer>TIME_FOR_OPENING)){
            status = CLOSED;
            door->close();
            shareData.closeDoor = 0;
            emptyingTimer = 0;
        }
    }
    else{
        shareData.emptyDoor = 0;
        if(shareData.openDoor){
            if(status==CLOSED){
                door->open();
                status = OPEN;
                emptyingTimer = millis();
            }
            shareData.openDoor = 0;
        }
    }
    shareData.doorStatus = (int)status;
}