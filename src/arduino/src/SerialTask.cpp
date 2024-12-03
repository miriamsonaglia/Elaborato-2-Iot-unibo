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
    //This 
    String piece1 = "STATUS:Filling:";
    String piece2 = " Temperature:";
    String piece3 = "C Status:";
    String piece4 = shareData.wError || shareData.tError? "Unvailable":"Available";
    char* dataOutput = (char*)(malloc(128));
    String fullData = piece1+shareData.fillPercentage+piece2+shareData.temperature+piece3+piece4;
    fullData.toCharArray(dataOutput,128,0);
    handler->tryWriteLine(dataOutput);
    free(dataOutput);
    memset(buffer,0,sizeof(buffer));
}
