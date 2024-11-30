#ifndef __DOOR__
#define __DOOR__
#include <Servo.h>

extern int doorStatus;

class Door{
public:
  Door(int pin);
  void open();
  void close();
  void empty();
private:
  int pin;
  Servo handler;
};

#endif