#include "../include/TaskReader.h"

#include <fstream>
#include <sstream>
#include "Task.h"

TaskReader::TaskReader(std::string inputFileName) {
    inputFileName = inputFileName;
    taskContainer_ = new TaskContainer();
}


TaskReader::~TaskReader() {
    delete taskContainer;
}

void TaskReader::readTasks() {
    ofstream inputFile;
    inputFile.open(inputFileName_, ios::in);

    if (!inputFile.is_open()) {
        std::cout << "Error while opening file: " <<
                inputFileName_ <<
                std::endl;
        return;
    }

    Tasks tasks;
    std::string line;
    while (std::getline(inpuFile, line)) {

        std::istringstream str(line);
        if (str[0] == '#')
            continue;

        unsigned int taskId, transData;
        unsigned int frequency;
        unsigned int leftBorder, rightBorder;
        if (!(  str >>
                taskId >>
                transData >>
                frequency >>
                leftBorder >>
                rightBorder))
        {
            std::cout << "Error while reading input file" << std::endl;
            inputFile.close();
            return;
        }

        Task* task = new Task(taskId, transData, frequency,
                              leftBorder, rightBorder);
        tasks.push_back(task);
    }

    taskContainer_.setTasks(tasks);

}


TaskReader::TaskContainer* getTaskContainer() {
    return taskContainer_;
}


//#NN     NWords  Freq,hz lphs,ms rphs,ms
//0       20      1       0       0
//             ...
//# There must be NO newline at the end of this file

