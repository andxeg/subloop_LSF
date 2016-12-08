#include "Task.h"

#define MAX(a,b) (((a)>(b))?(a):(b))


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
    lastExecutionTime_ = 0;
}


Task::~Task() {}


bool Task::isWillBeOnTime(const unsigned int& currentTime) {
    bool result = true;
    unsigned int currPeriod = (currentTime/period_)*period_;


    if (currentTime == currPeriod) {
        // start of period

        if ((currentTime+duration_) > (currPeriod + rightBorder_))
            result = false;
    } else {
        // in the middle of period

        // Task has already been executed in current period
        if (lastExecutionTime_  > currPeriod + leftBorder_)
            return true;

        if ((currentTime+duration_) > (currPeriod + rightBorder_))
            result = false;
    }

    return result;
}

bool Task::isWillBeOnTimeWithNewRightBorder(const unsigned int& currentTime,
                                            const unsigned int& rightBorder)
{
    bool result = true;
    unsigned int currPeriod = (currentTime/period_)*period_;


    if (currentTime == currPeriod) {
        // start of period

        if ((currentTime+duration_) > rightBorder)
            result = false;
    } else {
        // in the middle of period

        // Task has already been executed in current period
        if (lastExecutionTime_  > currPeriod + leftBorder_)
            return true;

        if ((currentTime+duration_) > rightBorder)
            result = false;
    }

    return result;
}



bool Task::isReady(const unsigned int& currentTime) {
    bool result = false;
    unsigned int currPeriod = (currentTime/period_)*period_;

    if (currentTime == currPeriod) {
        if (leftBorder_ == 0)
            return true;
    } else {
        // Check on one execution in period
        if (  lastExecutionTime_ >  (currPeriod + leftBorder_)  &&
              lastExecutionTime_ <= (currPeriod + rightBorder_) )
            return false;

        // Check availability of execution
        if (  currentTime >=  (currPeriod + leftBorder_)  &&
              currentTime < (currPeriod + rightBorder_) )
            result = true;
    }

    return result;
}


bool Task::isPassed(const unsigned int& currentTime) {
    bool result = false;

    if (lastExecutionTime_%period_ == 0) {
        if (currentTime > (lastExecutionTime_+rightBorder_))
            result = true;
    } else {
        unsigned int lastEndOfDirectiveInterval = (lastExecutionTime_/period_)*period_ +
                                                  rightBorder_;
        if (currentTime > (lastEndOfDirectiveInterval+period_))
            result = true;
    }

    return result;
}


bool Task::isExecutedInCurrentPeriod(const unsigned int& currentTime) {
    bool result;
    unsigned int startOfPeriod = (currentTime/period_)*period_;
    if (lastExecutionTime_ <= startOfPeriod)
        result = false;
    else
        result = true;

    return result;

}

// two variant when task finish
// 1) when last exec in current period and period didn't finished
// 2) when period just finished and last exec <= this time
bool Task::isFinishedToCurrentTimeInPeriod(const unsigned int& currentTime) {
    bool result = false;
    unsigned int startOfPeriod = (currentTime/period_)*period_;

    if (currentTime == 0)
        return false;

    if (currentTime == startOfPeriod) {
        if (lastExecutionTime_ <= startOfPeriod - period_ + rightBorder_ &&
            lastExecutionTime_ > (startOfPeriod - period_ + leftBorder_))
            return true;
    } else {
        // if (lastExecutionTime_ > startOfPeriod- period_ + leftBorder_ &&
        //         lastExecutionTime_ <= currentTime)
        if (lastExecutionTime_ > startOfPeriod)
            result = true;
    }

    return result;
}


unsigned int Task::getStock(const unsigned int& currentTime) {
    // phi2 - phi1* - duration
    // phi1* = max(phi1, currentTime)

    unsigned int currentPeriod = (currentTime/period_)*period_;
    unsigned int endOfInterval = currentPeriod+rightBorder_;
    unsigned int startOfInterval = currentPeriod+leftBorder_;

    if (currentTime >= endOfInterval)
        return 0;


    return (endOfInterval - MAX(currentTime, startOfInterval)) - duration_;
}


unsigned int Task::getDirectiveIntervalDuration() {
    return rightBorder_ - leftBorder_;
}


unsigned int Task::getId() {
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
