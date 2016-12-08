#include "TaskContainer.h"

#include <algorithm>
#include <cmath>


#define MIN(a,b) (((a)>(b))?(b):(a))


TaskContainer::TaskContainer() {
    tasks_ = Tasks();
}


TaskContainer::~TaskContainer() {

    for (unsigned int i=0; i<tasks_.size(); i++)
        delete tasks_[i];
}



void TaskContainer::setTasksInStartCondition() {
    for (unsigned int i=0; i<tasks_.size(); i++)
        tasks_[i]->setLastExecutionTime(0);
}


unsigned long long TaskContainer::getRunTime() {
    // find schedule interval as lcm of the tasks period
	unsigned int taskCount = tasks_.size();
    
    if (taskCount == 0)
    	return 0;

    unsigned long long globalLcm = 1;
    for (unsigned int i=0; i<taskCount; i++) {
        globalLcm = lcm(globalLcm, tasks_[i]->getPeriod());
    }

    return globalLcm;
}


unsigned int TaskContainer::getMaxTasksInSubCircle() {
    // find min task duration -> min_d
    // getMaxTasksInSubCircle == schedule interval / min_d
    if (tasks_.empty())
    	return 0;

    unsigned int minDuration = tasks_[0]->getDuration();

    for (unsigned int i=1; i < tasks_.size(); i++) {
    	unsigned int duration = tasks_[i]->getDuration();
    	if (duration < minDuration)
    		minDuration = duration;
    }

    // TODO change to MAX. If runTime == subCircle then
    // in one subCircle will be executed all tasks
    return MIN(getRunTime() / minDuration, tasks_.size());

}


bool TaskContainer::taskCompare(Task* first, Task* second) {
    return first->getDuration() < second->getDuration();
}


void TaskContainer::setTasks(Tasks& tasks) {
    tasks_ = tasks;
    std::sort(tasks_.begin(), tasks_.end(), TaskContainer::taskCompare);
}


Tasks TaskContainer::getTasks() {
    return tasks_;
}


unsigned long long TaskContainer::lcm(const unsigned long long& first,
                                 const unsigned long long& second)
{
	return first*second/gcd(first, second);
}


unsigned long long TaskContainer::gcd(const unsigned long long& first,
                                      const unsigned long long& second)
{
    unsigned int a = first;
    unsigned int b = second;
    unsigned int c;

    if (b > a) {
        c = a;
        a = b;
        b = c;
    }

    while(b!=0) {
        c = b;
        b = a%b;
        a = c;
    }

    return a;
}


void TaskContainer::printTasks() {
    for (Tasks::iterator it=tasks_.begin(); it != tasks_.end(); it++) {
        Task* task = *it;
        std::cout <<  task->getId() << " " <<
                task->getDuration()<< " " <<
                task->getPeriod() << " " <<
                task->getLeftBorder() << " " <<
                task->getRightBorder() <<
                std::endl;
    }
}



unsigned int TaskContainer::getMaxTresholdTasksInSubCircle(const unsigned int& subCircleTime,
                                                           double& reserve)
{
    unsigned int realSubCircleTime = static_cast<double>(subCircleTime)*(1-reserve);
    unsigned int currentSubCircleTime = 0;
    unsigned maxCountInSubCircle = 0;

    for (unsigned int i=0; i<tasks_.size(); i++) {
        currentSubCircleTime += tasks_[i]->getDuration();
        maxCountInSubCircle += 1;
        if (currentSubCircleTime >= realSubCircleTime)
            break;
    }

    return maxCountInSubCircle;
}


unsigned int TaskContainer::getMinTresholdTasksInSubCircle(const unsigned int& subCircleTime) {
    unsigned int runTime = getRunTime();
    // Nearest integral value that is not less runTime/ subCircleTime
    unsigned int chainMaxCount = static_cast<unsigned int>(
            std::ceil(static_cast<double>(runTime)/subCircleTime));
    unsigned allTasksCount = 0;

    for (unsigned int i=0; i<tasks_.size(); i++) {
        allTasksCount += static_cast<unsigned int>(std::ceil(static_cast<double>(runTime)/tasks_[i]->getPeriod()));
    }

    return static_cast<unsigned int>(std::ceil(static_cast<double>(allTasksCount)/chainMaxCount));
}


unsigned int TaskContainer::getOverallTasksCount() {
    unsigned int runTime = getRunTime();
    unsigned int allTasksCount = 0;

    for (unsigned int i=0; i<tasks_.size(); i++) {
        allTasksCount += static_cast<unsigned int>(std::ceil(static_cast<double>(runTime)/tasks_[i]->getPeriod()));
    }

    return allTasksCount;
}