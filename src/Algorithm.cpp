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


unsigned int Algorithm::getSubCircleTime(){
    return subCircleTime_;
}


bool Algorithm::existPassedTasks(Tasks& tasks, unsigned int& currentTime) {
    bool result = false;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (tasks[i]->isPassed(currentTime)) {
            result = true;
            break;
        }
    }

    return result;
}


bool Algorithm::checkAllTasksExecutedInCurrentPeriod(Tasks& tasks, unsigned int& currentTime) {
    bool result = true;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (!tasks[i]->isExecutedInCurrentPeriod(currentTime)) {
            result = false;
            break;
        }
    }

    return result;
}


bool Algorithm::checkAllTasksFinishedToCurrentTimeInPeriod(Tasks& tasks, unsigned int& currentTime) {
    bool result = true;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (!tasks[i]->isFinishedToCurrentTimeInPeriod(currentTime)) {
            result = false;
            break;
        }
    }

    return result;
}


bool Algorithm::existImpossibleTasks(Tasks& tasks, unsigned int& currentTime) {
    bool result = false;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (!tasks[i]->isWillBeOnTime(currentTime)) {
            result = true;
            break;
        }
    }

    return result;
}


Tasks Algorithm::getReadyTasks(Tasks& tasks, unsigned int& currentTime) {
    Tasks readyTasks;
    for (unsigned int i=0; i<tasks.size(); i++) {
        if (tasks[i]->isReady(currentTime))
            readyTasks.push_back(tasks[i]);
    }

    return readyTasks;
}

Tasks Algorithm::getTasksCanFinishedWithReserveLimitation(Tasks& tasks,
                                                          unsigned int& chainDuration)
{
    Tasks result;
    unsigned int limitDuration = subCircleTime_*(1-reserve_);
    for (unsigned int i=0; i < tasks.size(); i++) {
        if ((chainDuration+tasks[i]->getDuration()) <= limitDuration)
            result.push_back(tasks[i]);
    }

    return result;
}


Task* Algorithm::getTaskByLsfCriteria(Tasks& tasks, unsigned int& currentTime) {
    Task * result = tasks[0];
    unsigned minStock = tasks[0]->getStock(currentTime);
    for (unsigned int i=1; i < tasks.size(); i++) {
        unsigned stock = tasks[i]->getStock(currentTime);
        if (stock < minStock) {
            result = tasks[i];
            minStock = stock;
        }
    }

    return result;
}


bool Algorithm::existNotFinishedBeforeRunTime(Tasks& tasks,
                                              unsigned int& currentTime)
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


//typedef std::vector<Task*> Tasks;
//
//typedef std::vector< std::pair < unsigned int, Tasks>> Schedule;


Schedule Algorithm::schedule(TaskContainer* taskContainer) {

    // std::cout << "Start algo" << std::endl;


//    bool result = true;
    Schedule finalSchedule;
    Tasks tasks = taskContainer->getTasks();
    unsigned int currentTime = 0; // (1)
    unsigned int chainStart = 0;


    while (true) {
        //(2) Create empty chain.
        Tasks chain;
        unsigned int chainDuration = 0;

        // NOW we at the START of the CHAIN
        chainStart = currentTime;
//        std::cout << "Chain start -> " << chainStart << std::endl;


        //(4) Check if schedule interval is exhausted.
        if (currentTime >= runTime_) {
            if (existPassedTasks(tasks, runTime_)) {
                std::cerr << "Schedule time was exhausted, but some tasks were passed" << std::endl;
//                printSchedule(finalSchedule);
                finalSchedule.clear();
                return finalSchedule;
            }
            else {
                if (checkAllTasksFinishedToCurrentTimeInPeriod(tasks, runTime_))
                    return finalSchedule;
                else {
                    std::cerr << "Schedule time was exhausted, but some didn't finished" << std::endl;
//                    printSchedule(finalSchedule);
                    finalSchedule.clear();
                    return finalSchedule;
                }
            }
        }

        while (true) {

            // Time is not exhausted.
            //(4.5) Check if tasks is passed after shift.
            // in shift time may be tasks must have been executed but wasn't executed
            if (existPassedTasks(tasks, currentTime)) {
                std::cerr << "Chain. existPassedTasks. In start while." << std::endl; // !!!!!!!!!
//                printSchedule(finalSchedule);
                finalSchedule.clear();
                return finalSchedule;
            }

            //(5,6,7) All task could be potential executed on time
            // Check it!
            if (existImpossibleTasks(tasks, currentTime)) {
                std::cerr << "Chain. existImpossibleTasks." << std::endl; // !!!!!!!!!!
//                printSchedule(finalSchedule);
                finalSchedule.clear();
                return finalSchedule;
            }


            // Now all tasks could be exactly executed on time
            //(8) Check current time in the middle of any task directive interval
            // return tasks that ready and not execute in their current period
            // this tasks must be executed
            Tasks readyTasks = getReadyTasks(tasks, currentTime);
            if (readyTasks.empty()) {
                if (!chain.empty()) {
                    finalSchedule.push_back(std::make_pair(chainStart,
                                                           chain));
                    break;// jump to 2 -> form new chain
                } else {
                    finalSchedule.push_back(std::make_pair(chainStart,
                                                           chain));
                    break;// jump to 3 -> form new chain
                }
            }


            // Check if tasks from readyTasks can
            // finished before runTime_ will be exhausted
            // in case when runTime is exhausted in the middle of subCircle
            bool flag = existNotFinishedBeforeRunTime(readyTasks, currentTime);
            if (flag) {
                std::cerr << "Chain. existNotFinishedBeforeRunTime." << std::endl;
//                printSchedule(finalSchedule);
                finalSchedule.clear();
                return finalSchedule;
            }


            // (9) check if tasks from readyTasks can be added to chain without excess R_rf
            // if cannot be added then continue
            Tasks tasksCanFinishedWithReserveLimitation =
                    getTasksCanFinishedWithReserveLimitation(readyTasks, chainDuration);

            if (tasksCanFinishedWithReserveLimitation.empty()) {
                if (chain.empty()) {
                    std::cerr << "Chain. tasksCanFinishedWithReserveLimitation.empty()." << std::endl; //!!!
//                    printSchedule(finalSchedule);
                    finalSchedule.clear();
                    return finalSchedule;
                } else {
                    finalSchedule.push_back(std::make_pair(chainStart,
                                                      chain));
                    break;//jump to 2 -> form new chain
                }
            }



            // (9.a) If such tasks exist
            // get one of them by CRITERIA LSF
            Task* task = getTaskByLsfCriteria(tasksCanFinishedWithReserveLimitation,
                                              currentTime);

            // (9.b) Add task to chain
            chain.push_back(task);
            chainDuration += task->getDuration();

            // (9.c) shift current time on task duration
            currentTime += task->getDuration();

            // (9.d) in current period task was executed
            // set end of last execution
            task->setLastExecutionTime(currentTime);


//            // Check if task passed when current task was processing
//            if (existPassedTasks(tasks, currentTime)) {
//                std::cerr << "Chain. existPassedTasks. During task was processing" << std::endl; //!!!
//                printSchedule(finalSchedule);
//                finalSchedule.clear();
//                return finalSchedule;
//            }


            // (9.e) Check R_mcc of chain
            if (chain.size() == maxTasksInSubCircle_) {
                finalSchedule.push_back(std::make_pair(chainStart,
                                                  chain));

//                // Check if task passed when current task was processing
//                if (existPassedTasks(tasks, currentTime)) {
//                    std::cerr << "Chain. Chain size was exhausted." << std::endl;
//                    printSchedule(finalSchedule);
//                    finalSchedule.clear();
//                    return finalSchedule;
//                }

                break; // jump to 2 -> form new chain
            } else {
                continue;// jump to 4 -> continue form current chain
            }

        }


        //(3) Shift to start time chain.
        unsigned int shiftFromStartTimeChain = currentTime%subCircleTime_;
        currentTime += subCircleTime_ - shiftFromStartTimeChain;

    }

}


void Algorithm::printSchedule(Schedule& schedule) {
    std::cout << "SCHEDULE:" << std::endl;

    if (schedule.empty()) {
        std::cout << "Schedule is empty" << std::endl;
        return;
    }

//    std::cout <<  "Schedule.size() -> " << schedule.size() << std::endl;

    for (unsigned int i=0; i<schedule.size(); i++) {
        unsigned int chainStart = std::get<0>(schedule[i]);
//        std::cout << "Chain start -> " << chainStart << std::endl;
        Tasks chain = std::get<1>(schedule[i]);
//        std::cout << "Chain was read. Chain size-> " << chain.size() << std::endl;
        std::cout << chainStart << ' ';

        for (unsigned int j=0; j<chain.size(); j++) {
            std::cout << chain[j]->getId() << ' ';
        }
        std::cout << std::endl;
    }
}


