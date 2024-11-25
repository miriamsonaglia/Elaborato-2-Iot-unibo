#ifndef __DOORTASK__
#define __DOORTASK__

#include "Task.h"
#include "Door.h"

//global variables (read)
extern int tError;
extern int wError;
//global variables (read/write)
extern int openDoor  = 0;
extern int closeDoor = 0;
extern int emptyDoor = 0;

class DoorTask:public Task {
public:
  DoorTask(int pin);
  void init(int period);
  void tick();
private:
  int pin;
  Door* door;
  enum{CLOSED,OPEN,EMPTYING} status;
};

#endif