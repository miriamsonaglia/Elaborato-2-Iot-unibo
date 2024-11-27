#ifndef __SONARWASTE__
#define __SONARWASTE__

class SonarWaste {
private:
    int trigPin;       // Pin di trigger del sensore
    int echoPin;       // Pin di echo del sensore
    float threshold;   // Soglia in cm per il contenitore pieno

public:
    SonarWaste(int trigPin, int echoPin, float threshold);
    double getDistance();  // Legge la distanza attuale
    bool isFull();        // Verifica se il contenitore è pieno
};

#endif