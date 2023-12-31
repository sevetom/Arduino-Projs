#ifndef __LEAVEDHANDLER__
#define __LEAVEDHANDLER__

#include "TaskHandler.h"
#include "LedTask.h"
#include "GateTask.h"
#include "CountDown.h"

#define LEAVED_TASKS_COUNT 3

/**
 * Task handler that handles the tasks when the car has leaved the washing machine
*/
class LeavedHandler : public TaskHandler {
private:
  GateTask* gate; // 21
  LedTask* led1; // 22
  LedTask* led3; // 23
public:
  void initTasks();
  void setChangeState(bool state);
  int getTasksCount();
};

#endif