#include <string>
#include <iostream>

#include "Defs.h"
#include "TaskReader.h"
#include "Algorithm.h"
#include <iomanip>


unsigned int readSubCircleTime(const char* str) {
    // Subcircle time is given in milliseconds
    // Convert it to microseconds
    std::string subCircleTimeStr(str);
    unsigned int subCircleTime = std::stoi(subCircleTimeStr);
    subCircleTime *= 1000;
    return subCircleTime;
}


inline unsigned int getReservePrecision() {
    return 1;
}


void printSchedule(Schedule& schedule) {
    std::cout << "SCHEDULE:" << std::endl;
    if (schedule.empty()) {
        std::cout << "Schedule is empty" << std::endl;
        return;
    }

    for (unsigned int i=0; i<schedule.size(); i++) {
        unsigned int chainStart = std::get<0>(schedule[i]);
        Tasks chain = std::get<1>(schedule[i]);
        std::cout << chainStart << ' ';
        for (unsigned int j=0; j<chain.size(); j++) {
            std::cout << chain[j]->getId() << ' ';
        }
        std::cout << std::endl;
    }
}


bool verifySchedule(Schedule& schedule, TaskContainer* taskContainer) {
    unsigned int tasksInSchedule = 0;
    unsigned int overallTasksCount = taskContainer->getOverallTasksCount();



    for (unsigned int i=0; i<schedule.size(); i++) {
        Tasks chain = std::get<1>(schedule[i]);
        tasksInSchedule += chain.size();
    }

    std::cout << "Overall tasks count -> " << overallTasksCount << std::endl;
    std::cout << "Tasks in schedule  -> " << tasksInSchedule << std::endl;

    return tasksInSchedule == overallTasksCount;
}


bool findMaxReserveAndMinTasksThresholdInSubCircle(TaskContainer* taskContainer,
                                                   Algorithm& algorithm)
{
    Schedule schedule;

    int reserveProc=100-getReservePrecision();
    int minReserveProc = 0;
//    unsigned int maxTasksInSubCircle = taskContainer->getMaxTasksInSubCircle();

    unsigned int minThreshold = taskContainer->getMinTresholdTasksInSubCircle(algorithm.getSubCircleTime());
    unsigned int maxTasksInSubCircle;

    for (;reserveProc>=minReserveProc; reserveProc-=getReservePrecision()) {
        double reserve = static_cast<double>(reserveProc/100.0);
        algorithm.setReserve(reserve);
        unsigned int tasksInSubCircle = minThreshold;
        maxTasksInSubCircle = taskContainer->getMaxTresholdTasksInSubCircle(algorithm.getSubCircleTime(), reserve);

        for (;tasksInSubCircle<=maxTasksInSubCircle; tasksInSubCircle++) {
            algorithm.setMaxTasksInSubCircle(tasksInSubCircle);
            taskContainer->setTasksInStartCondition();
            schedule = algorithm.scheduleNew(taskContainer);
            if (!schedule.empty()) {
                std::cout << "SCHEDULE WAS FOUND" << std::endl;
//                std::cout << "Reserve-> " << reserve << "; Min tasks in subcircle-> " <<
//                        tasksInSubCircle << std::endl;
                algorithm.printParameters();

                printSchedule(schedule);
                if (verifySchedule(schedule, taskContainer)) {
                    std::cout << "Schedule is correct" << std::endl;
                    return true;
                } else {
                    std::cout << "Schedule is NOT correct" << std::endl;
                    return false;
                }

            }

        }
        
    }

    return false;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "[Error] Please Enter: " << argv[0] <<
                " <input_file.txt> <subcircle_length>" << std::endl;
        return 1;
    }

    std::string inputFile = std::string(argv[1]);
    unsigned int subCircleTime = readSubCircleTime(argv[2]);

    TaskReader taskReader(inputFile);
    if (!taskReader.readTasks())
        return 1;

    TaskContainer* taskContainer = taskReader.getTaskContainer();
    unsigned int runTime = taskContainer->getRunTime();

    Algorithm algorithm;

    // Set basic parameters
    algorithm.setRunTime(runTime);
    algorithm.setSubCircleTime(subCircleTime);


    if (!findMaxReserveAndMinTasksThresholdInSubCircle(taskContainer, algorithm)) {
        std::cerr << "Schedule was not created" << std::endl;
        return 1;
    }

    return 0;
}
