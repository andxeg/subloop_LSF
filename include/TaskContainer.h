# pragma once

#include <iostream>
#include "Defs.h"
#include "Task.h"


class TaskContainer {
public:
    TaskContainer();
    ~TaskContainer();

    unsigned long long getRunTime();
    unsigned int getMaxTasksInSubCircle();

    void setTasks(Tasks& tasks);
    Tasks getTasks();

    void printTasks();

private:
    static unsigned long long lcm(const unsigned long long& first,
								  const unsigned long long& second);

    static unsigned long long gcd(const unsigned long long& first,
								  const unsigned long long & second);
private:
    Tasks tasks_;
};
