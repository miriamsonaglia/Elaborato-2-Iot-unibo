#ifndef __MOTIONSENSOR__
#define __MOTIONSENSOR__


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