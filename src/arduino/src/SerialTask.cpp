#include "../lib/Tasks/SerialTask.h"
#include "../lib/Scheduling/SharableData.h"

extern struct SharableData shareData;
#define MAX_BUFFER_SIZE 64

SerialTask::SerialTask(){
    handler = new SerialHandler();
    buffer = (char*)(malloc(MAX_BUFFER_SIZE));
}

void SerialTask::init(int period){
    Task::init(period);
    Serial.begin(9600);
}

void SerialTask::tick(){
    //read possible commands from java GUI
    int success = handler->tryRead(buffer);
    if(success){
        if (strcmp(buffer,"EMPTY")==0) {
            // Simula svuotamento del contenitore
            doorStatus = -1;
            Serial.println("Container emptied");
        } else if (strcmp(buffer,"RESTORE")==0) {
            // Simula ripristino
            Serial.println("Container restored");
        }
    }
    //send data to java GUI (temperature,percentage fill ecc...)
    //handler->tryWrite(std::format("STATUS: Filling:{}% Temperature:{}°C",shareData.fillPercentage,shareData.temperature));
    char statusMessage[1024]; // Buffer per il messaggio formattato
    sprintf(statusMessage, "STATUS:Filling:%f%% Temperature:%f%%°C", shareData.fillPercentage, shareData.temperature);
    handler->tryWrite("STATUS:Filling:30% Temperature:15°C\n");
    Serial.println(statusMessage);

}
