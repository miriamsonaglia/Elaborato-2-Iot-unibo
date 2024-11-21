#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

//Code retrieved from the iot course (2024-2025)

#define MAX_TASKS 50

class Scheduler {
  
  int basePeriod;
  int nTasks;
  Task* taskList[MAX_TASKS];  

public:
  void init(int basePeriod);  
  virtual bool addTask(Task* task);  
  virtual void schedule();
};

#endif