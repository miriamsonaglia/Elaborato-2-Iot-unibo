#ifndef __BUTTON__
#define __BUTTON__


class Button {
public:
  Button(int pin);
  bool isPressed();
  bool hasStatusSwitched();
private:
  int pin;
  int previous_status;
};

#endif