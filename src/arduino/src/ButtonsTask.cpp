#include "../lib/Tasks/ButtonsTask.h"
#include "../lib/Components/Button.h"
#include <Arduino.h> 

#define ALLOWED_TICKS_FOR_COMMAND_RESOLUTIONS 20


ButtonsTask::ButtonsTask(int open,int close){
    open_button_pin = open;
    close_button_pin = close;
}

void ButtonsTask::init(int period){
    Task::init(period);
    open_button = new Button(open_button_pin);
    close_button = new Button(close_button_pin);
    status =NO_COMMAND;
    Serial.begin(9600);
}

void ButtonsTask::tick(){
    if(!sleep_mode){
        if(status == NO_COMMAND){
            if(open_button->isPressed() && !close_button->isPressed()){
                status = OPEN_PENDING;
                closeDoor = 0;
                openDoor = 1;
                doorStatus = 1;
                
            }
            else if(!open_button->isPressed() && close_button->isPressed()){
                status = CLOSE_PENDING;
                closeDoor = 1;
                openDoor = 0;
                doorStatus = 0;
            }
        }
        else if(!(emptyDoor | openDoor | closeDoor)){
            status = NO_COMMAND;
            ticks_elapsed = 0;
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
}