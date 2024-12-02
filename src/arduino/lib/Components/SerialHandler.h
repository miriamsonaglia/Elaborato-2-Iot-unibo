#ifndef __SERIALHANDLER__
#define __SERIALHANDLER__

#include <Arduino.h>

extern int doorStatus;

class SerialHandler
{
private:
public:
    SerialHandler();
    int tryRead(char* reader);
    int tryWrite(char* message);
};



#endif