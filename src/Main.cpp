#include <string>
#include <iostream>

#include "Defs.h"
#include "TaskReader.h"
#include "Algorithm.h"


unsigned int readSubCircleTime(const char* str) {
    unsigned int subCircleTime;
    return subCircleTime;
}


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



//===============

bool findMaxReserveAndMinTasksThresholdInSubCircle(TaskContainer* taskContainer,
                                                   Algorithm& algorithm)
{
    Schedule schedule;

    double reserve=1.0-getReservePrecision();
    unsigned int maxTasksInSubCircle = taskContainer->getMaxTasksInSubCircle();

    for (;reserve>=0.0; reserve-=getReservePrecision()) {
        algorithm.setReserve(reserve);
        
        //optimize min and max TasksCountInSubCircle
        unsigned int minTasksInSubCircle = 1;
        for (;minTasksInSubCircle<=maxTasksInSubCircle; minTasksInSubCircle++) {
            algorithm.setMaxTasksInSubCircle(minTasksInSubCircle);
            schedule = algorithm.schedule(taskContainer);
            if (!schedule.empty()) {
                std::cout << "Reserve-> " << reserve <<
                    "; Min tasks in subcircle-> " << 
                    minTasksInSubCircle << 
                    std::endl;
                // print Schedule
                //
                return true;
            }
        }
        
    }

    return false;
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

    if (!taskReader.readTasks())
        return 1;

    TaskContainer* taskContainer = taskReader.getTaskContainer();
    unsigned int runTime = taskContainer->getRunTime();

    Algorithm algorithm;

    // Set basic parameters
    algorithm.setRunTime(runTime);
    algorithm.setSubCircleTime(subCircleTime);
    
    if (!findMaxReserveAndMinTasksThresholdInSubCircle(taskContainer, algorithm)) 
        return 1;
    
    return 0;
}
