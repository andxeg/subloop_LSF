# pragma once


class Task {
public:
    Task(const unsigned int& taskId,
         const unsigned int& transData,
         const unsigned int& frequency,
         const unsigned int& leftBorder,
         const unsigned int& rightBorder);

    ~Task();

    // Can tasl will be executed on time
    bool isTaskWillBeOnTime(const unsigned int& currentTime);

    // Can do task be executed now.
    // Check one execution on period.
    // Check that current time in directive interval
    bool isTaskReady(const unsigned int& currentTime);


    bool isTaskPassed(const unsigned int& currentTime);

    unsigned int getTaskId();
    unsigned int getDuration();
    unsigned int getPeriod();
    unsigned int getLeftBorder();
    unsigned int getRightBorder();
    unsigned int getLastExecutionTime();

    void setLastExecutionTime(const unsigned int& lastExecutionTime );
    
private:
    unsigned int taskId_;
    unsigned int duration_;
    unsigned int period_;
    unsigned int leftBorder_, rightBorder_;

    unsigned int lastExecutionTime_;
};