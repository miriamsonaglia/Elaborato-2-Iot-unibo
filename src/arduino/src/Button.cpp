#include "../lib/Components/Button.h"
#include <Arduino.h>


//Code retrieved (and modified) from the iot course (2024-2025)
Button::Button(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

bool Button::isPressed(){
    return digitalRead(pin)==HIGH;
}

