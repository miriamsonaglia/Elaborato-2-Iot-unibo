#ifndef __BUTTON__
#define __BUTTON__

#include "DigitallyReadableDevice.h"

class Button:public DigitallyReadableDevice{
public:
  Button(int pin);
  bool isPressed();
  bool hasStatusSwitched();
};

#endif