#include "../Tasks/LcdTask.h"
#include <Arduino.h>
#include "../lib/Scheduling/SharableData.h"

#define TIMER_WASTE_RECIVED_MESSAGE 3000

extern SharableData shareData;
enum doorStatus {CLOSED,OPEN,EMPTYING};

LcdTask::LcdTask(int address, int cols, int rows){
    this->lcd = new Lcd(address, cols, rows);
    this->currentMsg = "";
}

void LcdTask::init(int period){
    Task::init(period);
    timerDelay = 0;
    lcd->init();
    timerOn = 0;
    previous_door_status = shareData.doorStatus;
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
        timerDelay = 0;

    }else if(wError){
        lcd->message("CONTAINER IS FULL");
        timerDelay = 0;
    }
    else if(shareData.doorStatus == (int)OPEN)
    {
        lcd->message("PRESS CLOSE WHEN DONE");
        timerDelay = 0;
    }
    else if(previous_door_status==(int)OPEN && shareData.doorStatus==(int)CLOSED)
    {
        timerDelay = millis();
    }
    else if(timerDelay !=0)
    {
        if(millis() - timerDelay >= TIMER_WASTE_RECIVED_MESSAGE)
        {
            timerDelay = 0;
        }
        else
        {
            lcd->message("WASTE RECEIVED");
        }
    }
    else
    {
        lcd->message("PRESS OPEN TO ENTER WASTE");
        timerDelay = 0;
    }
    previous_door_status = shareData.doorStatus;
}