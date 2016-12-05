#include "Task.h"


unsigned int getWordTransmissionTime() {
    return 20;
}


Task::Task(const unsigned int& taskId,
           const unsigned int& transData,
           const unsigned int& frequency,
           const unsigned int& leftBorder,
           const unsigned int& rightBorder)
{
    taskId_ = taskId;
    duration_ = transData*getWordTransmissionTime();
    period_ = static_cast<unsigned int>(1000000.0/frequency);
    leftBorder_ = leftBorder*1000;
    rightBorder_ = rightBorder==0 ? period_ : rightBorder*1000;
    lastExecutionTime_ = -period_;
}


Task::~Task() {}


bool Task::isTaskWillBeOnTime(const unsigned int& currentTime) {
    bool result = true;

    if ((currentTime+duration_) > ((currentTime/period_)*period_ + rightBorder_))
        result = false;

    return result;
}


bool Task::isTaskReady(const unsigned int& currentTime) {
    bool result = false;
    unsigned int currPeriod = (currentTime/period_)*period_;

    // Check on one execution in period
    if (  lastExecutionTime_ >=  (currPeriod + leftBorder_)  &&
            lastExecutionTime_ < (currPeriod + rightBorder_) )
        return false;

    // Check availability of execution
    if (  currentTime >=  (currPeriod + leftBorder_)  &&
            currentTime < (currPeriod + rightBorder_) )
        result = true;

    return result;
}


bool Task::isTaskPassed(const unsigned int& currentTime) {
    bool result = false;

    unsigned int lastEndOfDirectiveInterval = (lastExecutionTime_/period_)*period_ +
                                              rightBorder_;

    if (currentTime > (lastEndOfDirectiveInterval+period_))
        result = true;

    return result;
}



unsigned int Task::getTaskId() {
    return taskId_;
}


unsigned int Task::getDuration() {
    return duration_;
}


unsigned int Task::getPeriod() {
    return period_;
}


unsigned int Task::getLeftBorder() {
    return leftBorder_;
}


unsigned int Task::getRightBorder() {
    return rightBorder_;
}


unsigned int Task::getLastExecutionTime() {
    return lastExecutionTime_;
}

void Task::setLastExecutionTime(const unsigned int& lastExecutionTime ) {
    lastExecutionTime_ = lastExecutionTime;
}
