#ifndef __DOORTASK
#define __DOORTASK__

#include "Task.h"

//global variables (read)
extern int tError;
extern int wError;
//NOTE: following flags should be mutually exclusive or all turned off (open=close=empty=0 OR open xor close xor empty = 1)
extern int openDoor  = 0;
extern int closeDoor = 0;
extern int emptyDoor = 0;

class DoorTask:public Task {
public:
  DoorTask(int pin);
  void init(int period);
  void tick();
private:
  enum{CLOSED,OPEN,EMPTYING} status;
};

#endif