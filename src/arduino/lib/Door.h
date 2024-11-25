#ifndef __DOOR__
#define __DOOR__
#include <PWMServo.h>

#include "DigitallyReadableDevice.h"

class Door{
public:
  Door(int pin);
  void open();
  void close();
  void empty();
private:
  int pin;
  PWMServo* handler;
};

#endif