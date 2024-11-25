#include "../lib/MotionSensor.h"
#include <Arduino.h>

MotionSensor::MotionSensor(int pin){
  this->previous_status = 0;
  this->pin = pin;
  pinMode(pin,INPUT);
}

bool MotionSensor::movementDetected(){
    return digitalRead(pin)==HIGH;
}

bool MotionSensor::hasStatusSwitched(){
    int current_status = movementDetected();
    int prev = previous_status;
    previous_status = current_status;
    return current_status!=prev;
};