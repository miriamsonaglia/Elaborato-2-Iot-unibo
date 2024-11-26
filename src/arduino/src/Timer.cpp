#include "../lib/Timer.h"
#include <TimerOne.h>
#define NANOSECONDS(x) ((x)*1000)

volatile bool timerFlag;

void startTick(){
  timerFlag = true;
}

Timer::Timer(){
  timerFlag = false;
}

/* period in ms */
void Timer::setupPeriod(int period){
    //for timer one,it must be converted in ns
    Timer1.initialize(NANOSECONDS(period));
    Timer1.attachInterrupt(startTick);
}

void Timer::waitForNextTick(){
  /* wait for timer signal */
  while (!timerFlag){}
  timerFlag = false;
  
}