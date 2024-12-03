#ifndef __MOTIONTASK__
#define __MOTION_TASK__

#include "Task.h"
#include "MotionSensor.h"

class MotionTask : public Task{
    public:
        MotionTask(int pin,int maxInactiveTime);
        void tick();
        void init(int period);
    private:
        unsigned long sleep_mode_counter;
        int sensor_pin;
        int errorControll;
        unsigned long maxInactiveTime;
        MotionSensor* sensor;
        enum {MOVING,PENDING_SLEEP,SLEEP} status;
};

#endif