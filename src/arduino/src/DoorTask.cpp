#include <Arduino.h>
#include "../lib/DoorTask.h"

DoorTask::DoorTask(int pin){
    this->pin = pin;
}