#include "../lib/LedTask.h";
#include "../lib/DoorTask.h";
#include "../lib/Scheduler.h"


#define RED_LED_PIN 12
#define GREEN_LED_PIN 13
#define DOOR_PIN 6
#define BASE_PERIOD 100

/*Scheduler + task definition*/
LedTask* task_for_leds;
Scheduler* sched;
DoorTask* task_for_door;

/*Global variables*/
int wError = 0;         //flag variable,checks if waste bin is full
int tError = 0;         //flag variable,checks if there is a temperature problem
int openDoor  = 0;      //flag command, if set to 1 indicates that the door should become open
int closeDoor = 0;      //flag command, if set to 1 indicates that the door should become closed
int emptyDoor = 1;      //flag command, if set to 1 indicates that the door should be in a -90 degree position to empty the waste bin,this flag should always take priority over open and close flags.
int sleep_mode = 0;     //flag variable,if set to 1 indicates that the system is in sleep mode,the LCD should be turned off and the leds freezed.

void setup(){
    sched = new Scheduler();
    sched->init(BASE_PERIOD);
    /*Setup tasks*/
    task_for_leds = new LedTask(GREEN_LED_PIN,RED_LED_PIN);
    task_for_leds->init(BASE_PERIOD);
    sched->addTask(task_for_leds);

    task_for_door = new DoorTask(DOOR_PIN);
    task_for_leds->init(BASE_PERIOD*2);
    sched->addTask(task_for_door);
}

void loop(){
    sched->schedule();
}