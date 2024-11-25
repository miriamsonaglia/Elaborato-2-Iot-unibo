#include "../lib/Button.h"
#include <Arduino.h>


//Code retrieved (and modified) from the iot course (2024-2025)
Button::Button(int pin){
  this->previous_status = 0;
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

bool Button::isPressed(){
    return digitalRead(pin)==HIGH;
}

bool Button::hasStatusSwitched(){
    int current_status = isPressed();
    int prev = previous_status;
    previous_status = current_status;
    return current_status!=prev;
};