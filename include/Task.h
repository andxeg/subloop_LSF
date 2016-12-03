# pragma once

class Task {
public:
    Task(const unsigned int& taskId,
         const unsigned int& transData,
         const unsigned int& frequency,
         const unsigned int& leftBorder,
         const unsigned int& rightBorder);

    ~Task();

    bool isTaskExecutable(const unsigned int& currentTime);
    bool isTaskReady(const unsigned int& currentTime);
    bool isTaskPassed(const unsigned int& currentTime);
private:
    unsigned int taskId_;
    unsigned int duration_;
    unsigned int period_;
    unsigned int leftBorder_, rightBorder_;

    unsigned int lastExecutionTime_;
};