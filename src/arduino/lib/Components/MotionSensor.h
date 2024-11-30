#ifndef __MOTIONSENSOR__
#define __MOTIONSENSOR__

extern int wError;
extern int tError;
extern int openDoor;
extern int closeDoor;
extern int emptyDoor;

class MotionSensor {
public:
  MotionSensor(int pin);
  bool movementDetected();
  bool hasStatusSwitched();
private:
  int pin;
  int previous_status;
};

#endif