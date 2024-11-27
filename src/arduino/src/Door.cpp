#include "../lib/Components/Door.h"
#include <Arduino.h>

#define CLOSED_DEGREE 90
#define OPEN_DEGREE 180
#define EMPTY_DEGREE 0
//Code retrieved (and modified) from the iot course (2024-2025)
Door::Door(int pin){
  this->pin = pin;
  handler.attach(pin);
  pinMode(pin,OUTPUT);
}

void Door::close(){
    handler.write(CLOSED_DEGREE);
    delay(5);
}

void Door::open(){
    handler.write(OPEN_DEGREE);
    delay(5);
}

void Door::empty(){
    handler.write(EMPTY_DEGREE);
    delay(5);
}