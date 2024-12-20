#ifndef __DOORTASK__
#define __DOORTASK__

#include "Task.h"
#include "Door.h"


class DoorTask:public Task {
public:
  DoorTask(int pin);
  void init(int period);
  void tick();
private:
  int pin;
  Door* door;
  enum{CLOSED,OPEN,EMPTYING} status;
  long long emptyingTimer;
};

#endif