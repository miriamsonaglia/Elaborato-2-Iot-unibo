#ifndef __MOTIONSENSOR__
#define __MOTIONSENSOR__

#include "DigitallyReadableDevice.h"

class MotionSensor : public DigitallyReadableDevice {
public:
  MotionSensor(int pin);
  bool movementDetected();
  bool hasStatusSwitched();
private:
  int pin;
  int previous_status;
};

#endif