#include "../lib/Tasks/ButtonsTask.h"
#include "../lib/Components/Button.h"

#define ALLOWED_TICKS_FOR_COMMAND_RESOLUTIONS 2


ButtonsTask::ButtonsTask(int open,int close){
    open_button_pin = open;
    close_button_pin = close;
}

void ButtonsTask::init(int period){
    Task::init(period);
    open_button = new Button(open_button_pin);
    close_button = new Button(close_button_pin);
    status =NO_COMMAND;
}

void ButtonsTask::tick(){
    if(status == NO_COMMAND){
        if(open_button->isPressed() && !close_button->isPressed()){
            status = OPEN_PENDING;
            closeDoor = 0;
            openDoor = 1;
        }
        else if(!open_button->isPressed() && close_button->isPressed()){
            status = CLOSE_PENDING;
            closeDoor = 1;
            openDoor = 0;
        }
    }
    else{
        ticks_elapsed++;
        if(ticks_elapsed>=ALLOWED_TICKS_FOR_COMMAND_RESOLUTIONS){
            ticks_elapsed = 0;
            status = NO_COMMAND;
            closeDoor = 0;
            openDoor = 0;
        }
    }
}