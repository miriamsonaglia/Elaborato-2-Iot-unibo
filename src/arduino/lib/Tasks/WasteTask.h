#ifndef __WASTETASK__
#define __WASTETASK__

#include "SonarWaste.h"

class WasteTask {
private:
    SonarWaste& sonarWaste;  // Riferimento al sensore
    void (*onFullCallback)();  // Funzione da chiamare quando il contenitore è pieno

public:
    WasteTask(SonarWaste& sonarWaste, void (*onFullCallback)());
    void run();  // Esegue il monitoraggio
};

#endif