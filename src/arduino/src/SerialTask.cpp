#include "../lib/Tasks/SerialTask.h"
#include "../lib/Scheduling/SharableData.h"

extern struct SharableData shareData;
#define MAX_BUFFER_SIZE 64

SerialTask::SerialTask(){
    handler = new SerialHandler();
}

void SerialTask::init(int period){
    Task::init(period);
    buffer = (char*)(malloc(MAX_BUFFER_SIZE));
}

void SerialTask::tick(){
    //read possible commands from java GUI
    int success = handler->tryRead(buffer);
    if(success){
        if (strcmp(buffer,"EMPTY\n")==0) {
            // Simula svuotamento del contenitore
            shareData.emptyDoor = 1;
        } else if (strcmp(buffer,"RESTORE\n")==0) {
            // Simula ripristino
            shareData.ignoreTempError = 1;
        }
    }
    //send data to java GUI (temperature,percentage fill ecc...)
    //handler->tryWrite(std::format("STATUS: Filling:{}% Temperature:{}°C",shareData.fillPercentage,shareData.temperature));

    handler->tryWrite("STATUS:Filling:");
    handler->tryWrite(shareData.fillPercentage);
    handler->tryWrite(" Temperature:");
    handler->tryWrite(shareData.temperature);
    handler->tryWrite("C Status:");
    handler->tryWriteLine(shareData.wError || shareData.tError? "Unvailable":"Available");
    memset(buffer,0,sizeof(buffer));
}
