#include "TaskContainer.h"


TaskContainer::TaskContainer() {
    tasks_ = Tasks();
}


TaskContainer::~TaskContainer() {

    for (unsigned int i=0; i<tasks_.size(); i++)
        delete tasks_[i];
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

    for (Tasks::iterator it=++tasks_.begin(); it!=tasks_.end(); it++) {
    	unsigned int duration = (*it)->getDuration();
    	if (duration < minDuration)
    		minDuration = duration;
    }

    return getRunTime() / minDuration;

}


void TaskContainer::setTasks(Tasks& tasks) {
    tasks_ = tasks;
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
        std::cout <<  task->getTaskId() << " " <<
                task->getDuration()<< " " <<
                task->getPeriod() << " " <<
                task->getLeftBorder() << " " <<
                task->getRightBorder() <<
                std::endl;
    }
}
