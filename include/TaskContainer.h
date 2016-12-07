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

	unsigned int getMaxTresholdTasksInSubCircle(const unsigned int& subCircleTime, double& reserve);
    unsigned int getMinTresholdTasksInSubCircle(const unsigned int& subCircleTime);

	unsigned int getOverallTasksCount();

    void setTasks(Tasks& tasks);
    Tasks getTasks();

    void printTasks();

    static bool taskCompare(Task* first, Task* second);
private:
    static unsigned long long lcm(const unsigned long long& first,
								  const unsigned long long& second);

    static unsigned long long gcd(const unsigned long long& first,
								  const unsigned long long & second);

private:
    Tasks tasks_;
};
