#ifndef __LEDTASK__
#define __LEDTASK__

#include "Task.h"
#include "Led.h"

//global variables (read)
extern int wError;
extern int tError;
extern int sleep_mode;

class LedTask: public Task{
    public:
        LedTask(int green,int red);
        void init();
        void tick();

    private:
        int green_led_pin;
        int red_led_pin;
        Led* green_led;
        Led* red_led;
        enum {WORKING,ERROR} status;
};

#endif