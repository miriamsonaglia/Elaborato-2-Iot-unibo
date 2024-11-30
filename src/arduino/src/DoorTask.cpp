#include "../lib/Tasks/DoorTask.h"

DoorTask::DoorTask(int pin){
    this->pin = pin;
}

void DoorTask::init(int period){
    Task::init(period);
    door = new Door(pin);
    status = CLOSED;
    door->close();
}

void DoorTask::tick(){

    if(wError || tError){
        emptyDoor = 0;
        openDoor = 0;
        if(status != CLOSED){
            status = CLOSED;
            doorStatus = 0;
            door->close();
            closeDoor = 0;
        }
    }
    else if(status != CLOSED){
        if(closeDoor){
            status = CLOSED;
            doorStatus = 0;
            door->close();
            closeDoor = 0;
        }
    }
    else{
        if(openDoor){
            if(status==CLOSED){
                door->open();
                status = OPEN;
                doorStatus = 1;
            }
            openDoor = 0;
        }
        else if(emptyDoor){
            if(status == CLOSED){
                door->empty();
                status = EMPTYING;
                doorStatus = -1;
            }
            emptyDoor = 0;
        }
    }
}