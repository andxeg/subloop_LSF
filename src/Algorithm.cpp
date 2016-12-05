#include "Algorithm.h"


Algorithm::Algorithm() {};
Algorithm::~Algorithm() {};

void Algorithm::setReserve(const double& reserve) {
    reserve_ = reserve;
}


void Algorithm::setMaxTasksInSubCircle(const unsigned& maxTasksInSubCircle) {
    maxTasksInSubCircle_ = maxTasksInSubCircle;
}


void Algorithm::setRunTime(const unsigned& runTime) {
    runTime_ = runTime;
}


void Algorithm::setSubCircleTime(const unsigned& subCircleTime) {
    subCircleTime_ = subCircleTime;
}


Schedule Algorithm::schedule(TaskContainer* taskContainer) {
    Schedule finalSchedule;
    // TODO
    // write algorithm

    return finalSchedule;
}

