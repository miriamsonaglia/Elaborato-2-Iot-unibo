#include "../lib/LedTask.h"
#include "../lib/Led.h"


LedTask::LedTask(int green,int red){
    green_led_pin = green;
    red_led_pin = red;
}

void LedTask::init(int period){
    Task::init(period);
    green_led = new Led(green_led_pin);
    red_led = new Led(red_led_pin);
    status = WORKING;
    green_led->switchOn();
    red_led->switchOff();
}

void LedTask::tick(){
    if(!sleep_mode){
        if(tError || wError){
            if(status==WORKING){
                status = ERROR;
                green_led->switchOff();
                red_led->switchOn();
            }
        }
        else{
            if(status==ERROR){
                status = WORKING;
                green_led->switchOn();
                red_led->switchOff();
            }
        }
    }
}