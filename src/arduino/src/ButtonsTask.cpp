#include "../lib/Tasks/ButtonsTask.h"
#include "../lib/Components/Button.h"
#include "../lib/Scheduling/SharableData.h"
#include <Arduino.h>

#define ALLOWED_TICKS_FOR_COMMAND_RESOLUTIONS 10

extern SharableData shareData;

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
    if(!shareData.sleep_mode){
        if(status == NO_COMMAND){
            if(open_button->isPressed() && !close_button->isPressed()){
                status = OPEN_PENDING;
                shareData.closeDoor = 0;
                shareData.openDoor = 1;
            }
            else if(!open_button->isPressed() && close_button->isPressed()){
                status = CLOSE_PENDING;
                shareData.closeDoor = 1;
                shareData.openDoor = 0;
            }
        }
        //(This shouuld never happened,but just in case: if no command is pending we put the status to NO_COMMAND)
        else if(!(shareData.emptyDoor | shareData.openDoor | shareData.closeDoor)){
            status = NO_COMMAND;
            ticks_elapsed = 0;
        }
        else{
            ticks_elapsed++;
            if(ticks_elapsed>=ALLOWED_TICKS_FOR_COMMAND_RESOLUTIONS){
                ticks_elapsed = 0;
                status = NO_COMMAND;
                shareData.closeDoor = 0;
                shareData.openDoor = 0;
            }
        }
    }
}