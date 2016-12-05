# pragma once

#include <iostream>
#include <string>
#include "Defs.h"
#include "TaskContainer.h"


class TaskReader {
public:
    TaskReader(std::string inputFileName);
    ~TaskReader();

    bool readTasks();

    TaskContainer* getTaskContainer();

private:
    std::string inputFileName_;
    TaskContainer* taskContainer_;
};
