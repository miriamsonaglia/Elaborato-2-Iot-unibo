#ifndef __LED__
#define __LED__

#include "DigitallyWritableDevice.h"

//Code retrieved from the iot course (2024-2025) 

class Led :  DigitallyWritableDevice {
public:
  Led(int pin);
  void switchOn();
  void switchOff();
};

#endif