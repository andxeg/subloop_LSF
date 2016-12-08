#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include "Task.h"


// type for task sequence(chain)
typedef std::vector<Task*> Tasks;

// type for schedule
// first element -> start of task sequence
// second element -> task sequence(chain)
typedef std::vector< std::pair < unsigned int, Tasks>> Schedule;
