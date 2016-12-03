# pragma once

#include <iostream>
#include <string>
#include "Defs.h"


class TaskReader {
public:
    TaskReader(std::string inputFileName);
    ~TaskReader();

    void readTasks();

    TaskContainer* getTaskContainer();

private:
    std::string inputFileName_;
    TaskContainer* taskContainer_;
};
