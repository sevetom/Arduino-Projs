#ifndef __SLEEP_TASK__
#define __SLEEP_TASK__

#include "Task.h"
#include <avr/sleep.h>
#include <Arduino.h>

/**
 * Task that handles a sleep state
*/
class SleepTask: public Task {
  public:
    void init(int period);  
    void tick();
};

#endif