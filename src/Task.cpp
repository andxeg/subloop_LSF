#include "../include/Task.h"

unsigned int get_word_transmission_time() {
    return 20;
}


Task::Task(const unsigned int& taskId,
           const unsigned int& transData,
           const unsigned int& frequency,
           const unsigned int& leftBorder,
           const unsigned int& rightBorder)
{
    taskId_ = taskId;
    duration_ = transData*get_word_transmission_time();
    period_ = static_cast<unsigned int>(1000000.0/frequency);
    leftBorder_ = leftBorder*1000;
    rightBorder_ = rightBorder==0 ? period_ : rightBorder*1000;
    lastExecutionTime_ = -period_;
}


Task::~Task() {}


bool Task::isTaskExecutable(const unsigned int& currentTime) {
    return true;
}


bool Task::isTaskReady(const unsigned int& currentTime) {
    return true;
}


bool Task::isTaskPassed(const unsigned int& currentTime) {
    return true;
}

