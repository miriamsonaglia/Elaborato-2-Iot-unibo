#ifndef __BUTTONSTASK__
#define __BUTTONSTASK__

#include "Task.h"
#include "Button.h"

//global variables (read/write)
extern int openDoor;
extern int closeDoor;
//global variables (read)
extern int emptyDoor;
extern int sleep_mode;

class ButtonsTask: public Task{
    public:
        ButtonsTask(int open,int close);
        void init(int period);
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