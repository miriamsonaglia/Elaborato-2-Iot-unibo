#ifndef __BUTTON__
#define __BUTTON__

extern int doorStatus;

class Button{
public:
  Button(int pin);
  bool isPressed();
  bool hasStatusSwitched();
private:
  int pin;
};

#endif