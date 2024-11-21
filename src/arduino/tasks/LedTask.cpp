#include "LedTask.h"
#include "Led.h"
using namespace std;

LedTask::LedTask(int green,int red){
    green_led_pin = green;
    red_led_pin = red;
}

void LedTask::init(){
    green_led = new Led(green_led_pin);
    red_led = new Led(red_led_pin);
}

void LedTask::tick(){
    
}