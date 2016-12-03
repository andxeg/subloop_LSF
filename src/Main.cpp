#include <string>
#include <iostream>

#include "../include/Defs.h"
#include "../include/TaskReader.h"
#include "../include/Algorithm.h"


inline double getReservePrecision() {
    return 0.01;
}

double findMaxReserveInSubCircle(TaskContainer* taskContainer,
                                 Algorithm& algorithm)
{
    double reserve=1.0-getReservePrecision();
    unsigned int maxTasksInSubCircle = taskContainer->getMaxTasksInSubCircle();
    algorithm.setMaxTasksInSubCircle(maxTasksInSubCircle);

    for (;reserve>=0.0; reserve-=getReservePrecision()) {
        algorithm.setReserve(reserve);
        Schedule schedule = algorithm.schedule(taskContainer);
        if (!schedule.empty())
            return reserve;
    }

    return -1.0;
}


unsigned int findMinTasksThresholdInSubCircle(TaskContainer* taskContainer,
                                              const double& reserve,
                                              Algorithm& algorithm)
{
//     find Rmcc binSearch and print shedule(timetable)
//    bin search from Rmcc = 1 to Rmcc ==  maxTasksInSubCircle

    Schedule schedule;
    unsigned int maxTasksInSubCircle = taskContainer->getMaxTasksInSubCircle();
    unsigned int minTasksInSubCircle = 1;
    algorithm.setReserve(reserve);

    for (;minTasksInSubCircle<=maxTasksInSubCircle; minTasksInSubCircle++) {
        algorithm.setMaxTasksInSubCircle(minTasksInSubCircle);
        schedule = algorithm.schedule(taskContainer);
        if (!schedule.empty()) {
            // print Schedule
            //
            return minTasksInSubCircle;
        }
    }


    return -1;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {

        std::cout << "[Error] Please Enter: " <<
                argv[0] <<
                " <input_file.txt> <subcircle_length>" <<
                std::endl;
        return 1;
    }

    std::string inputFile = std::string(argv[1]);
    unsigned int subCircleTime = readSubCircleTime(argv[2]);

    TaskReader taskReader(inputFile);
    taskReader.readTasks();
    TaskContainer* taskContainer = taskReader.getTaskContainer();
    unsigned int runTime = taskContainer->getRunTime();

    Algorithm algorithm;
    algorithm.setSubCircleTime(subCircleTime);

    double maxReserve = findMaxReserveInSubCircle(taskContainer, algorithm);
    if (maxReserve < 0.0) {
        std::cout << "Can not max reserve for tasks" << std::endl;
        return 1;
    }

    std::cout <<  "MaxReserve -> " <<
            maxReserve <<
            std::endl;

    int minTasksInSubCircle = findMinTasksThresholdInSubCircle(taskContainer, maxReserve, algorithm);
    if (minTasksInSubCircle < 0) {
        std::cout << "Can not find mininal count of tasks in sub circle" << std::endl;
        return 1;
    }

    std::cout << " Minimal tasks in sub circle" <<
            minTasksInSubCircle <<
            std::endl;

    return 0;
}