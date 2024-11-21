#ifndef __LED__
#define __LED__


//Code retrieved from the iot course (2024-2025) 

class Led { 
public:
  Led(int pin);
  void switchOn();
  void switchOff();    
private:
  int pin;  
};

#endif