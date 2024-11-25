#include "LedTask.h"
#include "Scheduler.h"
#include "Arduino.h"

#define RED_LED_PIN 12
#define GREEN_LED_PIN 13

/*Scheduler + task definition*/
LedTask* task_for_leds;
Scheduler* sched;

/*Global variables*/
int wError = 0;         //flag variable,checks if waste bin is full
int tError = 0;         //flag variable,checks if there is a temperature problem
int openDoor  = 0;      //flag command, if set to 1 indicates that the door should become open
int closeDoor = 0;      //flag command, if set to 1 indicates that the door should become closed
int emptyDoor = 0;      //flag command, if set to 1 indicates that the door should be in a -90 degree position to empty the waste bin,this flag should always take priority over open and close flags.


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