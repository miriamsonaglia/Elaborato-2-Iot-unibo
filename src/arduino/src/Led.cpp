#include "../lib/Components/Led.h"
#include <Arduino.h>

//Code retrieved (and modified) from the iot course (2024-2025)
Led::Led(int pin){
  this->pin = pin;
  pinMode(pin,OUTPUT);
}

void Led::switchOn(){
  DigitallyWritableDevice::setValue(HIGH);
}

void Led::switchOff(){
  DigitallyWritableDevice::setValue(LOW);
};