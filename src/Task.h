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

    // Can task will be executed on time with new rightBorder
    bool isWillBeOnTimeWithNewRightBorder(const unsigned int& currentTime,
                                          const unsigned int& rightBorder);

    // Can task is executed now.
    // Check one execution on period.
    // Check that current time enter in the directive interval
    bool isReady(const unsigned int& currentTime);

    // Check task passed or not
    bool isPassed(const unsigned int& currentTime);

    // Only mean that task executed or not executed in current period
    bool isExecutedInCurrentPeriod(const unsigned int& currentTime);

    // Current time is either in the middle of period or at the end of period
    // Check that task was finished
    bool isFinishedToCurrentTimeInPeriod(const unsigned int& currentTime);

    // for Least Slack First criteria
    // return slack
    unsigned int getStock(const unsigned int& currentTime);

    //return directive interval
    unsigned int getDirectiveIntervalDuration();

    unsigned int getId();
    unsigned int getDuration();
    unsigned int getPeriod();
    unsigned int getLeftBorder();
    unsigned int getRightBorder();

    // get last end of execution
    unsigned int getLastExecutionTime();

    // set last end of execution
    void setLastExecutionTime(const unsigned int& lastExecutionTime );
    
private:
    unsigned int taskId_;
    unsigned int duration_;
    unsigned int period_;
    unsigned int leftBorder_, rightBorder_;

    // end of last execution time
    // need to control skip of task
    unsigned int lastExecutionTime_;
};
