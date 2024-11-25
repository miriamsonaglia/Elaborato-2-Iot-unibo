#ifndef __TIMER__
#define __TIMER__

#include <Arduino.h>

//Code retrieved from the iot course (2024-2025) 
class Timer {
    
public:  
  Timer();
  void setupFreq(int freq);  
  /* period in ms */
  void setupPeriod(int period);  
  void waitForNextTick();

};


#endif