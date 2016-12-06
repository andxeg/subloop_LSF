# pragma once


class Task {
public:
    Task(const unsigned int& taskId,
         const unsigned int& transData,
         const unsigned int& frequency,
         const unsigned int& leftBorder,
         const unsigned int& rightBorder);

    ~Task();

    // Can task will be executed on time
    bool isWillBeOnTime(const unsigned int& currentTime);

    // Can do task be executed now.
    // Check one execution on period.
    // Check that current time in directive interval
    bool isReady(const unsigned int& currentTime);

    // passed forever
    bool isPassed(const unsigned int& currentTime);

    // only mean that task executed or not executed in current period
    bool isExecutedInCurrentPeriod(const unsigned int& currentTime);

    // current time is either in the middle of period or at the end of period
    bool isFinishedToCurrentTimeInPeriod(const unsigned int& currentTime);


    unsigned int getStock(const unsigned int& currentTime);
    unsigned int getDirectiveIntervalDuration();

    unsigned int getId();
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

    // end of last execution time
    unsigned int lastExecutionTime_;
};