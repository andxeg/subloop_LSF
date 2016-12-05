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

typedef std::vector<Task*> Tasks;

typedef std::vector< std::pair < unsigned int, Tasks>> Schedule;


Schedule Algorithm::schedule(TaskContainer* taskContainer) {
    bool result = false;
    Schedule finalSchedule;
    Tasks tasks = taskContainer->getTasks();
    unsigned int currentTime = 0;
    Tasks chain;

    while (true) {
        // Shift to start time chain
        unsigned int shiftFromStartTimeChain = currentTime%subCircleTime_;
        if (shiftFromStartTimeChain!= 0) {
            currentTime += (subCircleTime_ - shiftFromStartTimeChain);
            if (!chain.empty()) {
                schedule.push_back(std::make_pair(currentTime - subCircleTime_, chain));
                chain.clear();
            }
        }


        // Check if schedule interval is exhausted. (1)
        if (currentTime >= runTime_) {
            if (existPassedTasks(tasks, runTime_))
                result = false;
            else {
                if (checkAllTasksFinishedToCurrentTimeInPeriod(tasks, runTime_))
                    result = true;
                else
                    result = false;
            }
            break;
        }


        // Time is not exhausted.
        // Check if tasks is passed after shift.
        if (existPassedTasks(tasks, currentTime)) {
            result = false;
            break;
        }

        // All task could be potential executed on time
        // Check it!
        if (existImpossibleTasks(tasks, currentTime)) {
            result = false;
            break;
        }


        // Now all tasks could be exactly executed on time
        // Check current time in the middle of any task directive interval
        Tasks readyTasks = getReadyTasks(tasks, currentTime);
        if (readyTasks.empty()) {
            continue;
        }


        // check if tasks from readyTasks can be added to chain without excess R_rf and R_mcc
        // if cannot be added then continue

        // if such tasks exist
        // get one of them by CRITERIA
        //  point 9 from algo description







    }

    if (!result)
        finalSchedule.clear();

    return finalSchedule;
}



