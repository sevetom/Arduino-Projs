#include "Gate.h"

Gate::Gate(int pin) {
  this->pin = pin;
}

void Gate::setAngle(int angle) {
  if (angle >= GATE_MIN_ANGLE && angle <= GATE_MAX_ANGLE) {
    this->servo.attach(this->pin);
    for (int a = this->currentAngle; a != angle; a += (angle > this->currentAngle) ? 1 : -1) {
      this->servo.write(a);
      delay(10);
    }
    this->servo.detach();
  }
}

int Gate::getMinAngle() {
  return GATE_MIN_ANGLE;
}

int Gate::getMaxAngle() {
  return GATE_MAX_ANGLE;
}