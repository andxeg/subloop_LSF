# pragma once

#include <iostream>
#include "Defs.h"
#include "Task.h"


class TaskContainer {
public:
    TaskContainer();
    ~TaskContainer();

	// set last execution time to start value == 0
    void setTasksInStartCondition();

    // return schedule interval
    unsigned long long getRunTime();

    // return MAX(runTime/minPeriod,tasks count)
    unsigned int getMaxTasksInSubCircle();

	// estimation of Rmcc(max)
    unsigned int getMaxTresholdTasksInSubCircle(const unsigned int& subCircleTime, double& reserve);

    // estimation of Rmcc(min)
    unsigned int getMinTresholdTasksInSubCircle(const unsigned int& subCircleTime);

    // get all task which must be executed during schedule interval
	unsigned int getOverallTasksCount();

    // set tasks and sort it by duration
    // sorting need for estimation of Rmcc(max)
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
