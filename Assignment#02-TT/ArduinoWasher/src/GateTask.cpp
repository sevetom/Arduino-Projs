#include "GateTask.h"

GateTask::GateTask(Gate* gate, gateMode mode) {
  this->gate = gate;
  this->mode = mode;
  this->cycles = 0;
  this->interruptFunction = NULL;
}

void GateTask::init(int period) {
  Task::init(period);
}

void GateTask::tick() {
  /**
   * First checks if the gate is already opening/closing
   * If not it opens/closes the gate and starts counting the cycles
  */
  delay(10);
  if (this->cycles == 0) {
    this->gate->on();
    switch (this->mode) {
      case OPEN:
        this->gate->open();
        break;
      case CLOSE:
        this->gate->close();
        break;
    }
  }
  /**
   * When the cycles are done it stops the gate and turns it off
  */
  this->cycles += this->cycles != -1 ? 1 : 0;
  if (this->cycles >= (this->mode == OPEN ? OPEN_CYCLES : CLOSE_CYCLES)) {
    this->cycles = -1;
    this->gate->stop();
    this->gate->off();
    /**
     * If needed it calls the interrupt function
    */
    if (this->interruptFunction != NULL) {
      this->interruptFunction();
    }
  }
}

void GateTask::restart() {
  this->timeElapsed = 0;
  this->cycles = 0;
}

void GateTask::setInterruptFun(InterruptFun f, bool state) {
  if (state) {
    this->interruptFunction = f;
  } else {
    this->interruptFunction = NULL;
  }
}