#ifndef __BUTTONSTASK__
#define __BUTTONSTASK__

#include "Task.h"
#include "Button.h"

class ButtonsTask: public Task{
    public:
        ButtonsTask(int open,int close);
        void init();
        void tick();
    private:
        int open_button_pin;
        int close_button_pin;
        Button* open_button;
        Button* close_button;
        int ticks_elapsed;
        enum {NO_COMMAND,OPEN_PENDING,CLOSE_PENDING} status;
};
#endif