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


bool Algorithm::existPassedTasks(Tasks tasks, unsigned int currentTime) {
    bool result = false;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (tasks[i]->isPassed(currentTime)) {
            result = true;
            break;
        }
    }

    return result;
}


bool Algorithm::checkAllTasksExecutedInCurrentPeriod(Tasks tasks, unsigned int currentTime) {
    bool result = true;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (!tasks[i]->isExecutedInCurrentPeriod(currentTime)) {
            result = false;
            break;
        }
    }

    return result;
}


bool Algorithm::checkAllTasksFinishedToCurrentTimeInPeriod(Tasks tasks, unsigned int currentTime) {
    bool result = true;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (!tasks[i]->isFinishedToCurrentTimeInPeriod(currentTime)) {
            result = false;
            break;
        }
    }

    return result;
}


bool Algorithm::existImpossibleTasks(Tasks tasks, unsigned int currentTime) {
    bool result = false;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (!tasks[i]->isWillBeOnTime(currentTime)) {
            result = true;
            break;
        }
    }

    return result;
}


Tasks Algorithm::getReadyTasks(Tasks tasks, unsigned int currentTime) {
    Tasks readyTasks;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (tasks[i]->isReady(currentTime))
            readyTasks.push_back(tasks[i]);
    }

    return readyTasks;
}

Tasks Algorithm::getTasksCanFinishedWithReserveLimitation(Tasks tasks, unsigned int chainDuration) {
    Tasks result;
    unsigned int limitDuration = subCircleTime_*(1-reserve_);
    for (unsigned int i=0; i < tasks.size(); i++) {
        if ((chainDuration+tasks[i]->getDuration()) <= limitDuration)
            result.push_back(tasks[i]);
    }

    return result;
}


Task* Algorithm::getTaskByLsfCriteria(Tasks tasks) {
    Task * result = tasks[0];
    unsigned minStock = tasks[0]->getStock();
    for (unsigned int i=1; i < tasks.size(); i++) {
        unsigned stock = tasks[i]->getStock();
        if (stock < minStock) {
            result = tasks[i];
            minStock = stock;
        }
    }

    return result;
}


bool Algorithm::existNotFinishedBeforeRunTime(Tasks readyTasks,
                                             unsigned int currentTime)
{
    bool result = false;
    for (unsigned int i=1; i < tasks.size(); i++) {
        if ((currentTime+tasks[i]->getDuration()) > runTime_) {
            result = true;
            break;
        }
    }

    return result;
}


typedef std::vector<Task*> Tasks;

typedef std::vector< std::pair < unsigned int, Tasks>> Schedule;


Schedule Algorithm::schedule(TaskContainer* taskContainer) {
    bool result = true;
    Schedule finalSchedule;
    Tasks tasks = taskContainer->getTasks();
    unsigned int currentTime = 0; // (1)
    unsigned int chainStart = 0;


    while (true) {
        //(2) Create empty chain.
        Tasks chain;
        unsigned int chainDuration = 0;

        //(3) Shift to start time chain.
        unsigned int shiftFromStartTimeChain = currentTime%subCircleTime_;
        if (shiftFromStartTimeChain!= 0) {
            currentTime += (subCircleTime_ - shiftFromStartTimeChain);
        }

        chainStart = currentTime;

        while (true) {

            //(4) Check if schedule interval is exhausted.
            if (currentTime >= runTime_) {
                if (existPassedTasks(tasks, runTime_))
                    result = false; // return finalSchedule.clear();
                else {
                    if (checkAllTasksFinishedToCurrentTimeInPeriod(tasks, runTime_))
                        result = true; // return finalSchedule;
                    else
                        result = false; // return finalSchedule.clear();
                }
                break;
            }


            // Time is not exhausted.
            //(4.5) Check if tasks is passed after shift.
            if (existPassedTasks(tasks, currentTime)) {
                result = false; // return finalSchedule.clear();
                break;
            }

            //(5,6,7) All task could be potential executed on time
            // Check it!
            if (existImpossibleTasks(tasks, currentTime)) {
                result = false; // return finalSchedule.clear();
                break;
            }


            // Now all tasks could be exactly executed on time
            //(8) Check current time in the middle of any task directive interval
            // return tasks that ready and not execute in their current period
            Tasks readyTasks = getReadyTasks(tasks, currentTime);
            if (readyTasks.empty()) {
                if (!chain.empty()) {
                    schedule.push_back(std::make_pair(chainStart,
                                                      chain));
                    // goto 2
                } else {
                    // goto 3
                }
            }


            // Check if tasks from readyTasks can
            // finished before runTime_ will be exhausted
            bool flag = existNotFinishedBeforeRunTime(readyTasks, currentTime);
            if (flag) {
                result = false; // return finalSchedule.clear();
                break;
            }


            // (9) check if tasks from readyTasks can be added to chain without excess R_rf
            // if cannot be added then continue
            Tasks tasksCanFinishedWithReserveLimitation =
                    getTasksCanFinishedWithReserveLimitation(readyTasks, chainDuration);

            if (tasksCanFinishedWithReserveLimitation.empty()) {
                if (chain.empty()) {
                    result = false; // return finalSchedule.clear();
                    break;
                } else {
                    schedule.push_back(std::make_pair(chainStart,
                                                      chain));
                    //goto 2
                }
            }



            // (9.a) If such tasks exist
            // get one of them by CRITERIA LSF
            Task *task = getTaskByLsfCriteria(tasksCanFinishedWithReserveLimitation);

            // (9.b) Add task to chain
            chain.push_back(task);
            chainDuration += task->getDuration();

            // (9.c) shift current time on task duration
            currentTime += task->getDuration();

            // (9.d) in current period task was executed
            task->setLastExecutionTime(currentTime);

            // Check if task passed when current task was processing
            if (existPassedTasks(tasks, currentTime)) {
                result = false; // return finalSchedule.clear();
                break;
            }

            // (9.e) Check R_mcc of chain
            if (chain.size() == maxTasksInSubCircle_) {
                schedule.push_back(std::make_pair(chainStart,
                                                  chain));
                // goto 2
            } else {
                // goto 4
            }

        }


    }

    if (!result)
        finalSchedule.clear();

    return finalSchedule;
}



