#ifndef __DIGITALLYREADABLEDEVICE__
#define __DIGITALLYREADABLEDEVICE__

#include <Arduino.h>

class DigitallyReadableDevice {
public:

  bool isHigh(){
    return digitalRead(pin) == HIGH;
  }

  bool hasStatusSwitched();

protected:
  int pin;
  int previous_status;
};

#endif