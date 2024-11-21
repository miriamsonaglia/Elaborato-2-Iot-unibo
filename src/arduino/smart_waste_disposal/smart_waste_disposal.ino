#include "LedTask.h"
#include "Scheduler.h"
#include "Arduino.h"

#define RED_LED_PIN 12
#define GREEN_LED_PIN 13

/*Scheduler + task definition*/
LedTask* task_for_leds;
Scheduler* sched;

/*Global variables*/
int wError = 0;
int tError = 1;


void setup(){
    sched = new Scheduler();
    sched->init(200);
    /*Setup tasks*/
     task_for_leds = new LedTask(GREEN_LED_PIN,RED_LED_PIN);
    task_for_leds->init();
    sched->addTask(task_for_leds);    
}

void loop(){
    sched->schedule();
}