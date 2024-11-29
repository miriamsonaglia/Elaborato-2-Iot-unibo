/*#include "../lib/Components/SerialHandler.h"

#define MAX_BUFFER_SIZE 64


SerialHandler::SerialHandler(){
    Serial.begin(9600);
}

//integer returns success of operation (success=1 and failure=0),if operation is successful,reader will contain the values
int SerialHandler::tryRead(char* reader){
    if(Serial.available()>0){
        return Serial.readBytesUntil('\n', reader, MAX_BUFFER_SIZE) > 0;
    }
    return 0;
}

int SerialHandler::tryWrite(char* message){
    Serial.println(message);
    return 1;
}
*/