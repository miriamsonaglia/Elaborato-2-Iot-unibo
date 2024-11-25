#ifndef __DOOR__
#define __DOOR__

#include "DigitallyReadableDevice.h"

class Door{
public:
  Door(int pin);
  void open();
  void close();
  void empty();
};

#endif