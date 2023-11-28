#ifndef __GATE__
#define __GATE__

#include <Arduino.h>
#include <Servo.h>

class Gate{
    int pin;
    Servo myservo;
public:
    Gate(int pin);
    void open();
    void close();
    void stop();
};

#endif