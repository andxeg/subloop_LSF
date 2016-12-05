#pragma once

#include "Defs.h"
#include "TaskContainer.h"

class Algorithm {
public:
    Algorithm();
    ~Algorithm();

    void setReserve(const double& reserve);
    void setMaxTasksInSubCircle(const unsigned& maxTasksInSubCircle);

    void setRunTime(const unsigned& runTime);
    void setSubCircleTime(const unsigned& subCircleTime);

    Schedule schedule(TaskContainer* taskContainer);

private:
    double reserve_;
    unsigned int maxTasksInSubCircle_;

    unsigned int runTime_;
    unsigned int subCircleTime_;
};
