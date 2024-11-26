#ifndef __DIGITALLYWRITABLEDEVICE__
#define __DIGITALLYWRITABLEDEVICE__

#include <Arduino.h>

class DigitallyWritableDevice {
public:
  void setValue(int value){
    digitalWrite(pin,value);
  }
protected:
  int pin;
};

#endif