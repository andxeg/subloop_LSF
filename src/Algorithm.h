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
    unsigned int getSubCircleTime();

    // algo with while-while in bad style
    Schedule schedule(TaskContainer* taskContainer);

    // See it! algo with for-for in acceptable view
    Schedule scheduleNew(TaskContainer* taskContainer);

private:
    bool existPassedTasks(Tasks& tasks, unsigned int& currentTime);
    bool existImpossibleTasks(Tasks& tasks, unsigned int& currentTime);
    bool existNotFinishedBeforeRunTime(Tasks& readyTasks, unsigned int& currentTime);
    bool checkAllTasksExecutedInCurrentPeriod(Tasks& tasks, unsigned int& currentTime);
    bool checkAllTasksFinishedToCurrentTimeInPeriod(Tasks& tasks, unsigned int& currentTime);


    Tasks getReadyTasks(Tasks& tasks, unsigned int& currentTime);
    Tasks getTasksCanFinishedWithReserveLimitation(Tasks& tasks, unsigned int& chainDuration);
    Task* getTaskByLsfCriteria(Tasks& tasks, unsigned int& currentTime);

    void printSchedule(Schedule& schedule);

private:
    double reserve_;
    unsigned int maxTasksInSubCircle_;

    unsigned int runTime_;
    unsigned int subCircleTime_;
};
