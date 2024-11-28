#include "../lib/Tasks/SerialTask.h"
#include "../lib/Scheduling/SharableData.h"

extern struct sharableData shareData;
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
        if (strcmp(buffer,"EMPTY")==0) {
            // Simula svuotamento del contenitore
            Serial.println("Container emptied");
        } else if (strcmp(buffer,"RESTORE")==0) {
            // Simula ripristino
            Serial.println("Container restored");
        }
    }
    //send data to java GUI (temperature,percentage fill ecc...)
    handler->tryWrite(std::format("STATUS: Filling:{}% Temperature:{}°C",shareData.fillPercentage,shareData.temperature));
}