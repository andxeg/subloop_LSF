#include "Algorithm.h"


Algorithm::Algorithm() {
    reserve_ = 0.0;
    maxTasksInSubCircle_ = 0;
    runTime_ = 0;
    subCircleTime_ = 0;
}

Algorithm::~Algorithm() {}


void Algorithm::printParameters() {
    std::cout <<
            "Reserve -> " << reserve_ << std::endl <<
            "Max tasks in subcircle -> " << maxTasksInSubCircle_ << std::endl <<
            "Schedule interval -> " << runTime_ << std::endl <<
            "Subcircle duration-> " << subCircleTime_ << std::endl <<
            std::endl;
}

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

