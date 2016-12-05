#pragma once

#include "Defs.h"
#include "TaskContainer.h"

class Algorithm {
public:
    Algorithm();
    ~Algorithm();

    void printParameters();

    void setReserve(const double& reserve);
    void setMaxTasksInSubCircle(const unsigned& maxTasksInSubCircle);

    void setRunTime(const unsigned& runTime);
    void setSubCircleTime(const unsigned& subCircleTime);

    Schedule schedule(TaskContainer* taskContainer);

private:
    bool existPassedTasks(Tasks tasks, unsigned int currentTime);
    bool checkAllTasksExecutedInCurrentPeriod(Tasks tasks, unsigned int currentTime);
    bool checkAllTasksFinishedToCurrentTimeInPeriod(Tasks tasks, unsigned int currentTime);
    bool existImpossibleTasks(Tasks tasks, unsigned int currentTime);

    Tasks getReadyTasks(Tasks tasks, unsigned int currentTime);

private:
    double reserve_;
    unsigned int maxTasksInSubCircle_;

    unsigned int runTime_;
    unsigned int subCircleTime_;
};
