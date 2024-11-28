#include "../lib/Tasks/SerialTask.h"
#include "../lib/Scheduling/SharableData.h"

extern struct sharableData writeData;
#define MAX_BUFFER_SIZE 64

SerialTask::SerialTask(){
    SerialHandler = new SerialHandler();
    buffer = (char*)(malloc(MAX_BUFFER_SIZE));
}

SerialTask::init(int period){
    Task::init(period);
}

SerialTask::tick(){
    //read possible commands from java GUI
    int success = handler->tryRead(buffer);
    if(success){
        //TODO: setup a communication protocol
    }
    //send data to java GUI (temperature,percentage fill ecc...)
    handler->tryWrite(std::format("STATUS: Filling:{}% Temperature:{}°C",writeData.fillPercentage,writeData.temperature));
}