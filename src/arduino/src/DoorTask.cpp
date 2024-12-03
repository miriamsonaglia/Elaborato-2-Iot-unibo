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
        emptyDoor = 0;
    }
    else if(wError || tError){
        openDoor = 0;
        if(status == OPEN){
            status = CLOSED;
            doorStatus = 0;
            door->close();
            closeDoor = 0;
        }
        else if(emptyDoor){
            if(status == CLOSED){
                door->empty();
                status = EMPTYING;
                doorStatus = -1;
                emptyingTimer = millis();
            }
            emptyDoor = 0;
        }

    }
    else if(status == OPEN){
        emptyDoor = 0;
        if(closeDoor || (millis()-emptyingTimer>TIME_FOR_OPENING)){
            status = CLOSED;
            door->close();
            closeDoor = 0;
            emptyingTimer = 0;
        }
    }
    else{
        emptyDoor = 0;
        if(openDoor){
            if(status==CLOSED){
                door->open();
                status = OPEN;
                emptyingTimer = millis();
            }
            openDoor = 0;
        }
    }
    shareData.doorStatus = (int)status;
}