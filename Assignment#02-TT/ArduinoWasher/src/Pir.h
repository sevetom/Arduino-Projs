#ifndef __PIR__
#define __PIR__

#include <Arduino.h>

#define CALIBRATION_TIME_SEC 10

class Pir {
    using interruptFun = void (*)(void);
    bool detectedStatus;
    int pin;
public:
    Pir(int pin);
    void init();
    bool isDetected();
    void setDetected(bool detected);
    void getDetectedStatus();
    void setInterrupt(interruptFun interruptFunction, bool attach);
};

#endif