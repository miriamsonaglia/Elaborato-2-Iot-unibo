#include "../lib/Tasks/LedTask.h"
#include "../lib/Tasks/DoorTask.h"
#include "../lib/Tasks/ButtonsTask.h"
#include "../lib/Tasks/TemperatureTask.h"
#include "../lib/Tasks/WasteTask.h"
#include "../lib/Tasks/MotionTask.h"
#include "../lib/Tasks/LcdTask.h"
#include "../lib/Tasks/SerialTask.h"
#include "../lib/Scheduling/Scheduler.h"
#include "../lib/Scheduling/SharableData.h"

#include <Arduino.h>

#define TRIG_PIN 10
#define ECHO_PIN 9
#define RED_LED_PIN 12
#define GREEN_LED_PIN 13
#define DOOR_PIN 6
#define OPEN_BUTTON 2
#define CLOSE_BUTTON 4
#define TEMPERATURE_PIN A0
#define MOVEMENT_PIN 8

#define LCDADDRESS 0x27
#define LCDCOLS 20
#define LCDROWS 4

#define BASE_PERIOD 50
#define MAX_TEMPERATURE_FOR_ERROR 35.0
#define MIN_HEIGHT_ACCEPTED 10.0
#define MAX_INACTIVITY_TIME 10

/*Scheduler + task definition*/
LedTask* task_for_leds;
Scheduler* sched;
SharableData shareData;
DoorTask* task_for_door;
ButtonsTask* task_for_button;
TemperatureTask* task_for_temp;
WasteTask * task_for_waste;
MotionTask* task_for_motion;
LcdTask* task_for_lcd;
SerialTask* task_for_serial;


void setup(){
    sched = new Scheduler();
    shareData.doorStatus=0;
    shareData.fillPercentage = 0.0;
    shareData.temperature = 0.0;
    shareData.closeDoor = 0;
    shareData.openDoor = 0;
    shareData.emptyDoor = 0;
    shareData.tError = 0;
    shareData.sleep_mode = 0;
    shareData.wError = 0;
    shareData.tError = 0;
    shareData.ignoreTempError = 0;

    sched->init(BASE_PERIOD);
    /*Setup tasks*/
    task_for_temp = new TemperatureTask(TEMPERATURE_PIN,MAX_TEMPERATURE_FOR_ERROR);
    task_for_temp->init(BASE_PERIOD*5);
    sched->addTask(task_for_temp);

    task_for_waste = new WasteTask(TRIG_PIN,ECHO_PIN,MIN_HEIGHT_ACCEPTED);
    task_for_waste->init(BASE_PERIOD*5);
    sched->addTask(task_for_waste);

    task_for_motion = new MotionTask(MOVEMENT_PIN,MAX_INACTIVITY_TIME);
    task_for_motion->init(BASE_PERIOD*5);
    sched->addTask(task_for_motion);

    task_for_button = new ButtonsTask(OPEN_BUTTON,CLOSE_BUTTON);
    task_for_button->init(BASE_PERIOD);
    sched->addTask(task_for_button);

    task_for_serial = new SerialTask();
    task_for_serial->init(BASE_PERIOD*4);
    sched->addTask(task_for_serial);

    task_for_leds = new LedTask(GREEN_LED_PIN,RED_LED_PIN);
    task_for_leds->init(BASE_PERIOD*5);
    sched->addTask(task_for_leds);

    task_for_door = new DoorTask(DOOR_PIN);
    task_for_door->init(BASE_PERIOD);
    sched->addTask(task_for_door);

    task_for_lcd = new LcdTask(LCDADDRESS, LCDCOLS, LCDROWS);
    task_for_lcd->init(BASE_PERIOD*2);
    sched->addTask(task_for_lcd);
}

void loop(){
    sched->schedule();
}