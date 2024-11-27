#include "../lib/Tasks/LedTask.h"
#include "../lib/Tasks/DoorTask.h"
#include "../lib/Tasks/ButtonsTask.h"
#include "../lib/Tasks/TemperatureTask.h"
#include "../lib/Tasks/WasteTask.h"
#include "../lib/Scheduling/Scheduler.h"

#include <Arduino.h>

#define TRIG_PIN 10
#define ECHO_PIN 9
#define RED_LED_PIN 12
#define GREEN_LED_PIN 13
#define DOOR_PIN 6
#define OPEN_BUTTON 2
#define CLOSE_BUTTON 4
#define TEMPERATURE_PIN A0
#define BASE_PERIOD 50
#define MAX_TEMPERATURE_FOR_ERROR 23.0
#define MIN_HEIGHT_ACCEPTED 10.0

/*Scheduler + task definition*/
LedTask* task_for_leds;
Scheduler* sched;
DoorTask* task_for_door;
ButtonsTask* task_for_button;
TemperatureTask* task_for_temp;
WasteTask * task_for_waste;

/*Global variables*/
int wError = 0;         //flag variable,checks if waste bin is full
int tError = 0;         //flag variable,checks if there is a temperature problem
int openDoor  = 0;      //flag command, if set to 1 indicates that the door should become open
int closeDoor = 0;      //flag command, if set to 1 indicates that the door should become closed
int emptyDoor = 0;      //flag command, if set to 1 indicates that the door should be in a -90 degree position to empty the waste bin,this flag should always take priority over open and close flags.
int sleep_mode = 0;     //flag variable,if set to 1 indicates that the system is in sleep mode,the LCD should be turned off and the leds freezed.

void setup(){
    sched = new Scheduler();
    sched->init(BASE_PERIOD);
    /*Setup tasks*/
    task_for_temp = new TemperatureTask(TEMPERATURE_PIN,MAX_TEMPERATURE_FOR_ERROR);
    task_for_temp->init(BASE_PERIOD*5);
    sched->addTask(task_for_temp);

    task_for_waste = new WasteTask(TRIG_PIN,ECHO_PIN,MIN_HEIGHT_ACCEPTED);
    task_for_waste->init(BASE_PERIOD*2);
    sched->addTask(task_for_waste);

    task_for_button = new ButtonsTask(OPEN_BUTTON,CLOSE_BUTTON);
    task_for_button->init(BASE_PERIOD);
    sched->addTask(task_for_button);

    task_for_leds = new LedTask(GREEN_LED_PIN,RED_LED_PIN);
    task_for_leds->init(BASE_PERIOD*3);
    sched->addTask(task_for_leds);

    task_for_door = new DoorTask(DOOR_PIN);
    task_for_door->init(BASE_PERIOD*2);
    sched->addTask(task_for_door);
    
}

void loop(){
    sched->schedule();
}