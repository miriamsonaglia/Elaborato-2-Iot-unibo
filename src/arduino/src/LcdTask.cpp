#include "../Tasks/LcdTask.h"
#include <Arduino.h>

LcdTask::LcdTask(int address, int cols, int rows){
    this->lcd = new Lcd(address, cols, rows);
    this->currentMsg = "Press open to enter waste";
}

void LcdTask::init(int period){
    Task::init(period);
    timerDelay = 0;
    lcd->init();
}

void LcdTask::updateMsg(const char* msg){
    currentMsg = msg;
}

void LcdTask::tick(){

    timerDelay = millis();

    if(sleep_mode){
        lcd->close();
    }else if(tError){
        lcd->message("PROBLEM DETECTED");

    }else if(wError){
        lcd->message("CONTAINER IS FULL");

    }else if(openDoor){
        lcd->message("PRESS CLOSE WHEN DONE");

    }else if(closeDoor){
        if(millis()-timerDelay>=5){
            lcd->message("WASTE RECIEVED"); 
        }

    }else if(emptyDoor){
        

    }else
    {
        lcd->message("PRESS OPEN TO ENTER WASTE");
    }
    
}