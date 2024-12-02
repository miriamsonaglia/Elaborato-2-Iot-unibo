#include "../Tasks/LcdTask.h"
#include <Arduino.h>

extern struct SharableData shareData;

LcdTask::LcdTask(int address, int cols, int rows){
    this->lcd = new Lcd(address, cols, rows);
    this->currentMsg = "";
}

void LcdTask::init(int period){
    Task::init(period);
    timerDelay = 0;
    lcd->init();
    Serial.begin(9600);
    timerOn = 0;
}

void LcdTask::updateMsg(const char* msg){
    currentMsg = msg;
}

void LcdTask::tick(){
    if(sleep_mode){
        lcd->close();
        timerDelay = 0;
    }else if(tError){
        lcd->message("PROBLEM DETECTED");
        doorStatus = 0;
        timerDelay = 0;

    }else if(wError){
        lcd->message("CONTAINER IS FULL");
        doorStatus = 0;
        timerDelay = 0;

    }else if(openDoor){
        timerDelay = millis();
    }else if(doorStatus == 1 && timerDelay !=0){
        if(millis() - timerDelay <= 3000){
            lcd->message("PRESS CLOSE WHEN DONE");
        }else{
            closeDoor = 1;
            timerDelay = millis();        }

    }else if(doorStatus == 0 && timerDelay != 0){
        if(millis() - timerDelay <= 3000){
            lcd->message("WASTE RECEIVED");
        }else{
            timerDelay = 0;
        }
        Serial.println("entra nel close door");

    }else if(doorStatus == -1 && timerDelay !=0){
        if(millis() - timerDelay <= 3000){
        }else{
            emptyDoor = 1;
            timerDelay = millis();
        }
        

    }else if(timerOn){

    }
    else
    {
        lcd->message("PRESS OPEN TO ENTER WASTE");
        timerDelay = 0;
    }
    
}