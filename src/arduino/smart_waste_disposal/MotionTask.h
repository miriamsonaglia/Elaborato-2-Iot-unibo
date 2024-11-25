#ifndef __MOTIONTASK__
#define __MOTION_TASK__

#include "Task.h"
#include "MotionSensor.h";

//global variables (write)
extern int sleep_mode;

class MotionTask : public Task{
    public:
        MotionTask(int pin);
        void tick();
        void init();
    private:
        int sleep_mode_counter;
        int sensor_pin;
        MotionSensor* sensor;
        enum {MOVING,PENDING_SLEEP,SLEEP} status;
};

#endif