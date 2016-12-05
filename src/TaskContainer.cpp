#include "TaskContainer.h"


TaskContainer::TaskContainer() {
    tasks_ = Tasks();
}


TaskContainer::~TaskContainer() {

    for (unsigned int i=0; i<tasks_.size(); i++)
        delete tasks_[i];
}


unsigned int TaskContainer::getRunTime() {
    // find schedule interval as lcm of the tasks period
	unsigned int taskCount = tasks_.size();
    
    if (taskCount == 0)
    	return 0;

    unsigned int globalLcm = 1;
    for (unsgined int i=0; i<taskCount; i++) {
        globalLcm = lcm(globalLcm, tasks_[i]->getPeriod());
    }

    return globalLcm;
}


unsigned int TaskContainer::getMaxTasksInSubCircle() {
    // find min task duration -> min_d
    // getMaxTasksInSubCircle == schedule interval / min_d
    if (task_.empty())
    	return 0;

    unsigned int minDuration = task_[0].getDuration();

    
    for (Task::iterator it=++task_.begin(); it!=task_.end(); it++) {
    	unsigned int duration = it->getDuration();
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


unsigned int TaskContainer::lcm(const unsigned int& first,
    							const unsigned int& second)
{
	return first*second/gcd(first, second);
}


unsigned int TaskContainer::gcd(const unsigned int& first,
                                const unsigned int& second)
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
        Tasks* task = *it;
        std::cout <<  task->getTaskId() << " " <<
                task->getDuration()<< " " <<
                task->getPeriod() << " " <<
                task->getLeftBorder() << " " <<
                task->getRightBorder() <<
                std::endl;
    }
}
