# pragma once

#include <iostream>
#include "Defs.h"
#include "Task.h"


class TaskContainer {
public:
    TaskContainer();
    ~TaskContainer();

    unsigned int getRunTime();
    unsigned int getMaxTasksInSubCircle();

    void setTasks(Tasks& tasks);
    Tasks getTasks();

    void printTasks();

private:
    static unsigned int lcm(const unsigned int& first,
    						const unsigned int& second);

    static unsigned int gcd(const unsigned int& first,
    						const unsigned int& second);
private:
    Tasks tasks_;
};
