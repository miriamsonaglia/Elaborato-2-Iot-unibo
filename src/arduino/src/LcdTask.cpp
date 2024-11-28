#include "../Tasks/LcdTask.h"

LcdTask::LcdTask(int address, int cols, int rows){
    this->lcd = new Lcd(address, cols, rows);
    this->currentMsg = "Ciao";
}

void LcdTask::init(int period){
    Task::init(period);
    lcd->init();
}

void LcdTask::updateMsg(const char* msg){
    currentMsg = msg;
}

void LcdTask::tick(){
    lcd->message(currentMsg);
}