#ifndef __LCD_DISPLAY__
#define __LCD_DISPLAY__

#define MAX_LENGTH 16
#define MAX_LINES 2

#include <LiquidCrystal_I2C.h> 
#include <Arduino.h>

/*
* Wiring: SDA => A4, SCL => A5
*/
class LcdDisplay{
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, MAX_LENGTH, MAX_LINES);
    bool printed;
public:
    void init();
    void print(const char* text);
    void print(const char* text, int row);
    void print(const char* text, int row, int line);
    void clear();
    bool getPrintStatus();
};

#endif