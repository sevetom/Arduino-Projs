#include "LcdDisplay.h"

void LcdDisplay::init() {
  this->lcd.init();
  this->lcd.backlight();
  this->lcd.clear();
}

void LcdDisplay::print(const char* text) {
  this->lcd.clear();
  this->lcd.setCursor(0, 0);
  this->lcd.print(text);
}

void LcdDisplay::print(const char* text, int line) {
  this->lcd.setCursor(0, line);
  this->lcd.print(text);
}

void LcdDisplay::clear() {
  this->lcd.clear();
}