#include "TaskReader.h"

#include <fstream>
#include <sstream>
#include "Task.h"


TaskReader::TaskReader(std::string inputFileName) {
    inputFileName_ = inputFileName;
    taskContainer_ = new TaskContainer();
}


TaskReader::~TaskReader() {
    delete taskContainer_;
}


bool TaskReader::readTasks() {
    std::fstream inputFile;
    inputFile.open(inputFileName_, std::ios::in);

    if (!inputFile.is_open()) {
        std::cerr << "Error while opening file: " <<
                inputFileName_ <<
                std::endl;
        return false;
    }

    Tasks tasks;
    std::string line;
    while (std::getline(inputFile, line)) {

        std::istringstream str(line);
        if (str.peek() == '#')
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
            std::cerr << "Error while reading input file" << std::endl;
            inputFile.close();
            return false;
        }

        Task* task = new Task(taskId, transData, frequency,
                              leftBorder, rightBorder);
        tasks.push_back(task);
    }

    taskContainer_->setTasks(tasks);
    return true;

}


TaskContainer* TaskReader::getTaskContainer() {
    return taskContainer_;
}


//#NN     NWords  Freq,hz lphs,ms rphs,ms
//0       20      1       0       0
//             ...
//# There must be NO newline at the end of this file
