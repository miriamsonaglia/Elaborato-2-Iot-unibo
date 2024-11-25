#include <Arduino.h>
#include "../lib/DoorTask.h"


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
    //check presence of error
    if(status != CLOSED){
        if(wError || tError || closeDoor){
            status = CLOSED;
            door->close();
            closeDoor = 0;
            //if this code was reached due to an error,all command flags must be reset
            if(wError || tError){
                emptyDoor = 0;
                openDoor = 0;
            }
        }
    }
    else{
        if(openDoor){
            if(status==CLOSED){
                door->open();
                status = OPEN;
            }
            openDoor = 0;
        }
        else if(emptyDoor){
            if(status == CLOSED){
                door->empty();
                status = EMPTYING;
            }
            emptyDoor = 0;
        }
    }
}