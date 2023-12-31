#include "Button.h"

Button::Button(int pin){
    this->pin = pin;
    pinMode(pin, INPUT);
}

void Button::setInterrupt(InterruptFunction intFun, bool attach){
    if(attach){
        attachInterrupt(digitalPinToInterrupt(pin), intFun, RISING);
    }else{
        detachInterrupt(digitalPinToInterrupt(pin));
    }
}